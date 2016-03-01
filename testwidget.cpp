
#include "testwidget.h"
#include <QImage>  
#include <QPixmap> 
#include"cv.h"
#include"highgui.h"
#include<QtMultimedia>
#include <QVideoWidget>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>
#include <math.h>
#include <QString>
#define M_PI 3.14159
#define M_PI_2 1.57
using namespace cv;
using namespace std;

testWidget::testWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//线程返回值进行GUI上图片修改
	//QObject::connect(myThread, SIGNAL(changeVideoPicture(QString)), this, SLOT(changeVideo(QString)));
	//QObject::connect(myThread, SIGNAL(changeKmeansPicture(QString)), this, SLOT(changeKmeans(QString)));
	/*timer = new QTimer(this);
	timer->setInterval(40);*/
	myThread = new Thread(this);
	QObject::connect(myThread, &Thread::done, this, &testWidget::changePicture);
	
	//index = 0;*/
}

testWidget::~testWidget()
{

}

/*void testWidget::sShowInfo() {
	//QObject::connect(rawData, SIGNAL(clicked()), testWidgetClass, SLOT(sShowInfo()));
	
	VideoCapture cap;
	cap.open("E:/28-prp/vids/pos_005.avi");
	if (!cap.isOpened())
	{
		cout << "fail to open." << endl;
		//return -1;
		/*QPixmap pix;
		pix.load("C:/Users/zutianluo/Documents/Tencent Files/1249396963/FileRecv/MobileFile/pic_of862_lightflow.jpg");

		pix = pix.scaled(161, 161, Qt::KeepAspectRatio);
		//QImage *image = new QImage("C:/Users/zutianluo/Desktop/1.png");
		ui.kmeansImage->setPixmap(pix);
		ui.kmeansImage->show()
	}
	else {
		//初始化视频信息
		double totalFrameNumber = cap.get(CV_CAP_PROP_FRAME_COUNT);
		double videowidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
		double videoheight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
		double fps = cap.get(CV_CAP_PROP_FPS);

		QString newFrame;
		ui.frame->setText(newFrame.setNum(totalFrameNumber));
		ui.Width->setText(newFrame.setNum(videowidth));
		ui.Height->setText(newFrame.setNum(videoheight));
		ui.FPS->setText(newFrame.setNum(fps));
	}

};*/

void testWidget::sPlayVideo() {
	
	//myThread->start();
	VideoCapture cap;
	cap.open("E:/28-prp/vids/pos_003.avi");
	if (!cap.isOpened())
	{
		cout << "fail to open." << endl;
		//return -1;
		/*QPixmap pix;
		pix.load("C:/Users/zutianluo/Documents/Tencent Files/1249396963/FileRecv/MobileFile/pic_of862_lightflow.jpg");

		pix = pix.scaled(161, 161, Qt::KeepAspectRatio);
		//QImage *image = new QImage("C:/Users/zutianluo/Desktop/1.png");
		ui.kmeansImage->setPixmap(pix);
		ui.kmeansImage->show();*/
	}
	else {
		//初始化视频信息
		double totalFrameNumber = cap.get(CV_CAP_PROP_FRAME_COUNT);
		double videowidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
		double videoheight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
		double fps = cap.get(CV_CAP_PROP_FPS);

		QString newFrame;
		ui.frame->setText(newFrame.setNum(totalFrameNumber));
		ui.Width->setText(newFrame.setNum(videowidth));
		ui.Height->setText(newFrame.setNum(videoheight));
		ui.FPS->setText(newFrame.setNum(fps));

		cap.release();	

		myThread->start();
	}	
	//timer->start();
}

/*void testWidget::changeVideo(QString vidPicPath) {
	QPixmap pix;
	pix.load(vidPicPath);

	pix = pix.scaled(641, 361, Qt::KeepAspectRatio);
	ui.playVideo->setPixmap(pix);
	ui.playVideo->show();
}

void testWidget::changeKmeans(QString kPicPath) {
	QPixmap pix;
	pix.load(kPicPath);

	pix = pix.scaled(161, 161, Qt::KeepAspectRatio);
	ui.kmeansImage->setPixmap(pix);
	ui.kmeansImage->show();
}*/

double getangle(double x, double y)
{
	double angle;
	if (x*x + y*y<0.2) { angle = 0; }
	else if (fabs(x)<0.0001)
	{
		if (y>0) angle = M_PI_2;
		else angle = 3 * M_PI_2;
	}
	else if (x>0 && y > 0)
	{
		angle = atan(y / x);
	}
	else if (x<0) { angle = M_PI + atan(y / x); }
	else if (x>0 && y<0) { angle = 2 * M_PI + atan(y / x); }
	return angle;
}

void testWidget::changePicture(QString index) {	
	/*index++;
	
	QString newFrame;
	

	QString addressKmeans("D://pictures/pic_of");
	addressKmeans.append(QString::number(index)).append("_lightflow.jpg");

	//ui.frameNumber->setText(newFrame.setNum(index));
	ui.frameNumber->setText(QString::number(index));
	QString addressVideo("D://pictures/pic_of");
	addressVideo.append(QString::number(index)).append("_original.jpg");

	QPixmap pix;
	pix.load(addressVideo);

	pix = pix.scaled(641, 361, Qt::KeepAspectRatio);
	ui.playVideo->setPixmap(pix);
	ui.playVideo->show();

	pix.load(addressKmeans);

	pix = pix.scaled(161, 161, Qt::KeepAspectRatio);
	ui.kmeansImage->setPixmap(pix);
	ui.kmeansImage->show();*/
	QString addressKmeans("D://pictures/pic_of");
	addressKmeans.append(index).append("_lightflow.jpg");


	ui.frameNumber->setText(index);
	QString addressVideo("D://pictures/pic_of");
	addressVideo.append(index).append("_original.jpg");

	QPixmap pix;
	pix.load(addressVideo);

	pix = pix.scaled(641, 361, Qt::KeepAspectRatio);
	ui.playVideo->setPixmap(pix);
	ui.playVideo->show();

	pix.load(addressKmeans);

	pix = pix.scaled(161, 161, Qt::KeepAspectRatio);
	ui.kmeansImage->setPixmap(pix);
	ui.kmeansImage->show();

}