#pragma once
#include "qthread.h"
class Thread :
	public QThread
{
	Q_OBJECT
public:
	Thread(QObject *parent = 0) :QThread(parent) {

	}
	~Thread();
	signals:void done(QString index);
protected:void run();
};

