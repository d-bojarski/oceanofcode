#include "aiworker.h"

#include <iostream>

AIWorker::AIWorker(QObject* parent) :
    QObject(parent),
    messageManager(),
    ai(messageManager)
{
}

AIWorker::~AIWorker()
{
}

void AIWorker::process()
{
    std::cout << "AIWorker::process" << std::endl;
    ai.start();
    std::cout << "finished" << std::endl;
    emit finished();
}
