/*************************************************************************
    > File Name: MainWindow.cpp
    > Author: aetheryang
    > Mail: aetheryang@gmail.com 
    > Created Time: Sun 05 Jan 2014 09:33:27 PM CST
 ************************************************************************/
#include "MainWindow.h"
#include <QAction>
#include <QIcon>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include<QSlider>
#include<QSpinBox>
#include<QPushButton>
#include<QGridLayout>
#include<iostream>
#include<QPainter>
using namespace std;
#include "rc.c"
int add_pro()
{
        progress_num+=1;
}
void MainWindow::pfresh ()
{
	cout << sec << endl;
    cout << rs <<  endl;
    int i=0;
    while(rs)
	{
        for(i=0;i<sec;i++)
        {
        take_pic();
    progress->setValue(1+(int)((double)progress_num*100/sec));
        progress->repaint();
		pwidget->repaint ();
        add_pro();
		qApp->processEvents ();
        }
        break;
	}
}

void MainWindow::qinit_yuan_yi ()
{
	rs = 0;
    dev_name = "/dev/video1";			 //摄像头设备名
    clearbuf();
    pwidget->repaint ();
}

void MainWindow::qinit_yuan ()
{
	rs = 0;
    clearbuf();
    init_pic();
    if(-1!=begin_pic())
    take_pic();
    end_pic();
	pwidget->repaint ();
}

void MainWindow::qinit_zhengfang_yi ()
{
	rs = 0;
    clearbuf();
}

void MainWindow::qinit_zhengfang ()
{
	rs = 0;
    clearbuf();
    dev_name = "/dev/video0";			 //摄像头设备名
	pwidget->repaint ();
}

void MainWindow::Quit ()
{
	rs = 0;
	qApp->quit ();
}

void MainWindow::Stop ()
{
	rs = 0;
    end_pic();
}

void MainWindow::Run ()
{
	rs = 1;
    progress_num=0;
    clearbuf();
    init_pic();
    if(-1!=begin_pic())
	pfresh ();
    end_pic();
}

void MainWindow::Step ()
{
    shc->show();
    shc->resize(800,800);
	pwidget->repaint ();
}

void MainWindow::setdelay (int a)
{
	sec = a;
	cout << sec << endl;
}

Canvas::Canvas ()
{
}

Canvas::~Canvas ()
{
}


MainWindow::~MainWindow ()
{
}
int setcount(int a)
{
    int i;
}
MainWindow::MainWindow ()
{
	pwidget = new Canvas ();
	QGridLayout *mainlayout = new QGridLayout ();
	setLayout (mainlayout);
	QPushButton *in_y = new QPushButton ("&takepic", this);
	QPushButton *in_y_1 = new QPushButton ("video&1", this);
	QPushButton *in_z = new QPushButton ("video&0", this);
	QPushButton *in_z_1 = new QPushButton ("&begin", this);
	QPushButton *run = new QPushButton ("&RUN", this);
	QPushButton *stop = new QPushButton ("&STOP", this);
	QPushButton *step = new QPushButton ("S&TEP", this);
	QPushButton *quit = new QPushButton ("&QUIT", this);
    shc=new showCanvas();
    progress=new QProgressBar;
    progress->setValue(0);
    //QSpinBox *spinbox=new QSpinBox();
    //spinbox->setSingleStep(200);
    //spinbox->setRange(0,1000);
    //spinbox->setValue(800);
	mainlayout->addWidget (in_y, 1, 0, 1, 1);
	mainlayout->addWidget (in_z, 1, 1, 1, 1);
	mainlayout->addWidget (in_y_1, 1, 2, 1, 1);
	mainlayout->addWidget (in_z_1, 1, 3, 1, 1);
	mainlayout->addWidget (run, 0, 0, 1, 1);
	mainlayout->addWidget (stop, 0, 1, 1, 1);
	mainlayout->addWidget (step, 0, 2, 1, 1);
	mainlayout->addWidget (quit, 0, 3, 1, 1);
	mainlayout->addWidget (pwidget, 2, 0, 4, 8);
	resize (1200, 1200);
    //mainlayout->addWidget (spinbox,0,4,1,1);
	QSlider *slider = new QSlider (Qt::Horizontal);
	slider->setRange (1, 1000);
	slider->setValue (100);
	mainlayout->addWidget (slider, 7, 0, 1, 4);
    mainlayout->addWidget(progress,7,4,1,1);
	QObject::connect (run, SIGNAL (clicked ()), this, SLOT (Run ()));
	QObject::connect (stop, SIGNAL (clicked ()), this, SLOT (Stop ()));
	QObject::connect (step, SIGNAL (clicked ()), this, SLOT (Step ()));
	QObject::connect (quit, SIGNAL (clicked ()), this, SLOT (Quit ()));
	QObject::connect (in_y, SIGNAL (clicked ()), this, SLOT (qinit_yuan ()));
	QObject::connect (in_z, SIGNAL (clicked ()), this, SLOT (qinit_zhengfang ()));
	QObject::connect (slider, SIGNAL (valueChanged (int)), this, SLOT (setdelay(int)));
	QObject::connect (in_y_1, SIGNAL (clicked ()), this, SLOT (qinit_yuan_yi ()));
	QObject::connect (in_z_1, SIGNAL (clicked ()), this, SLOT (qinit_zhengfang_yi()));
	pwidget->repaint ();
}
