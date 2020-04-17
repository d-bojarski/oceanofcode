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
    ai.stop();
}

void AIWorker::process()
{
    qDebug() << "AIWorker::process";
    ai.start();
    qDebug() << "AIWorker::finished";
    emit finished();
}
