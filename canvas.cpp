/*
 * =====================================================================================
 *
 *       Filename:  canvas.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/21/2014 02:08:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aetheryang (China), aetheryang@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
int buhead[2*PIx*PIy];
int bufxy[PIx][PIy];
int clearbuf()
{
    int i,j;
    for(i=0;i<PIx;i++)
        for(j=0;j<PIy;j++)
            bufxy[i][j]=0;
}
int addbuf(int x,int y,int ans)
{
    bufxy[x][y]+=ans;
}
int read_frame()
{
    int i,*head;
    struct v4l2_buffer buf;
    CLEAR (buf);
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    ioctl (fd, VIDIOC_DQBUF, &buf);				 //出列采集的帧缓冲
    assert (buf.index < n_buffers);
    //printf ("buf.index dq is %d,\n", buf.index);
    head=(int*)buffers[buf.index].start;
    //printf("head=%d\n",head);
    //fwrite (buffers[buf.index].start, buffers[buf.index].length, 1, file_fd);	//将其写入文件中
    //printf ("start at :%d,length :%d\n", buffers[buf.index].start, buffers[buf.index].length);
    for(i=0;i<2*PIx*PIy;i++)
    {
        buhead[i]=*head;
        head++;
    }

    ioctl (fd, VIDIOC_QBUF, &buf);				 //再将其入列
    return 1;
}
void Canvas::paintEvent (QPaintEvent * event)
{
	int i, j,*head,cal;
	QPainter painter (this);
    QPen pen;
    if(fd==-1)
    {
        cal=255;
        pen.setColor(QColor(cal,cal,cal));
        painter.setPen(pen);
        for(i=0;i<PIx;i++)
            for(j=0;j<PIx;j+=1)
            {
                painter.drawPoint (i, j);
            }
        return ;
    }
    head=buhead;
    for(i=0;i<PIy;i+=1)
        for(j=0;j<PIx;j+=2)
        {
            cal=(*head>>0)&0xff;
            pen.setColor(QColor(cal,cal,cal));
            painter.setPen(pen);
            painter.drawPoint (j, i);
            addbuf(j,i,cal);
            cal=(*head>>16)&0xff;
            pen.setColor(QColor(cal,cal,cal));
            painter.setPen(pen);
            painter.drawPoint (j+1, i);
            addbuf(j+1,i,cal);
            head++;
        }
}
showCanvas::showCanvas(){}
showCanvas::~showCanvas(){}
void showCanvas::paintEvent (QPaintEvent * event)
{
    int i,j,cal;
	QPainter painter (this);
    QPen pen;
    for(i=0;i<PIx;i++)
        for(j=0;j<PIy;j++)
        {
     //       cout<<i<<"+"<<j<<endl;
            cal=(int)((double)bufxy[i][j]/sec);
            pen.setColor(QColor(cal,cal,cal));
            painter.setPen(pen);
            painter.drawPoint(i,j);
        }
}
