#ifndef TESTWIDGET_H
#define TESTWIDGET_H
#include <QtWidgets/QWidget>
#include "ui_testwidget.h"
#include <QImage>  
#include <QPixmap> 
#include "Thread.h"
class testWidget : public QWidget
{
	Q_OBJECT

public:
	testWidget(QWidget *parent = 0);
	~testWidget();
	//播放视频线程
	Thread *myThread;
	//int index;
	//QTimer *timer;
	
	

public slots:
	//void sShowInfo();
	void sPlayVideo();
	//void changeVideo(QString);
	//void changeKmeans(QString);
	void changePicture(QString index);
	
private:
	Ui::testWidgetClass ui;
};

#endif // TESTWIDGET_H
