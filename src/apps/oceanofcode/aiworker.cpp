#include "aiworker.h"

#include <iostream>

AIWorker::AIWorker(QObject* parent) :
    QObject(parent),
	ai()
{
}

AIWorker::~AIWorker()
{
}

void AIWorker::process()
{
    ai.start();
    std::cout << "finished" << std::endl;
    //emit finished();
}
