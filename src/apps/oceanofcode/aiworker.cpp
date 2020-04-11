#include "aiworker.h"

#include <qdebug.h>

AIWorker::AIWorker(QObject* parent) :
    QObject(parent),
    messageManager(),
    ai(&messageManager)
{
}

AIWorker::~AIWorker()
{
}

void AIWorker::process()
{
    qDebug() << "AIWorker::process";
    ai.start();
    qDebug() << "finished";
    emit finished();
}
