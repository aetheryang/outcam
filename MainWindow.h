/*************************************************************************
    > File Name: MainWindow.h
    > Author: aetheryang
    > Mail: aetheryang@gmail.com 
    > Created Time: Sun 05 Jan 2014 09:26:15 PM CST
 ************************************************************************/
#include<QProgressBar>
#include<QWidget>
#include<qmainwindow.h>
#include<QObject>
class Canvas:public QWidget
{
  public:
	Canvas ();
	~Canvas ();
	void paintEvent (QPaintEvent *);
};
class showCanvas:public QWidget
{
  public:
	showCanvas ();
	~showCanvas ();
	void paintEvent (QPaintEvent *);
};
class MainWindow:public QWidget
{
  Q_OBJECT public:
	  MainWindow ();
	 ~MainWindow ();
	void pfresh ();
  public:
	  Canvas * pwidget;
      showCanvas *shc;
      QProgressBar *progress;
	int debug;
	int *debb;
	public slots:void Step ();
	void Run ();
	void Stop ();
	void qinit_zhengfang ();
	void qinit_yuan ();
	void qinit_yuan_yi ();
	void qinit_zhengfang_yi ();
	void Quit ();
	void setdelay (int a);
};
