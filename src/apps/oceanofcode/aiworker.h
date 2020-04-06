#pragma once

#include "ai.h"

#include <qobject.h>

class AIWorker : public QObject
{
	Q_OBJECT
public:
	AIWorker(QObject *parent = nullptr);
	~AIWorker();


//public slots:
	void process();
//signals:
//	void finished();


public:
	AI ai;
};