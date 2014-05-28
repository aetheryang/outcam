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
    return 1;
}
int addbuf(int x,int y,int ans)
{
    bufxy[x][y]+=ans;
    return ans;
}
int read_frame()
{
    int i,*head;
    struct v4l2_buffer buf;
    CLEAR (buf);
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    ioctl (fd, VIDIOC_DQBUF, &buf);				 //出列采集的帧缓冲
    head=(int*)buffers[buf.index].start;
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
    if(bl==1)
    {
        for(i=0;i<PIy;i+=1)
            for(j=0;j<PIx;j+=2)
            {
                int U,V,Y1,Y2,R,G,B;
                Y1=(*head>>0 )&0xff;
                U= (*head>>8 )&0xff;
                Y2=(*head>>16)&0xff;
                V= (*head>>24)&0xff;
                R=Y1+1.4075*(V-128);
                G=Y1-0.3455*(U-128)-0.7169*(V-128);
                B=Y1+1.779*(U-128);
                cal=Y1;
                pen.setColor(QColor(R,G,B));
                painter.setPen(pen);
                painter.drawPoint (j, i);
                addbuf(j,i,cal);

                R=Y2+1.4075*(V-128);
                G=Y2-0.3455*(U-128)-0.7169*(V-128);
                B=Y2+1.779*(U-128);
                cal=Y1;
                pen.setColor(QColor(R,G,B));
                painter.setPen(pen);
                painter.drawPoint (j+1, i);
                addbuf(j+1,i,cal);
                head++;
            }
    }
    else
    {
        for(i=0;i<PIy;i+=1)
            for(j=0;j<PIx;j+=2)
            {
                cal=(*head>>0 )&0xff;
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
    for(i=PIx/2-5,j=PIy/2;i<=PIx/2+5;i++)
    {
        pen.setColor(QColor(255,0,0));
        painter.setPen(pen);
        painter.drawPoint(i,j);
    }
    for(j=PIy/2-5,i=PIx/2;j<=PIy/2+5;j++)
    {
        pen.setColor(QColor(255,0,0));
        painter.setPen(pen);
        painter.drawPoint(i,j);
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
            cal=(int)((double)bufxy[i][j]/sec);
            pen.setColor(QColor(cal,cal,cal));
            painter.setPen(pen);
            painter.drawPoint(i,j);
        }
}
