#include "gridgenerator.h"
#include "view.h"
#include "aiworker.h"
#include "gameworker.h"

#include <iostream>

#include <qthread.h>
#include <qapplication.h>

int main(int argc, char* argv[])
{
	QApplication  app(argc, argv);

	GridGenerator generator(15);
	generator.generate();

	View view;
	view.fillGround(generator.grid, generator.tiles);
	view.show();

	QThread* threadPlayer0 = new QThread;
	AIWorker workerPlayer0;
	workerPlayer0.moveToThread(threadPlayer0);
	QObject::connect(threadPlayer0, &QThread::started, &workerPlayer0, &AIWorker::process);
	QObject::connect(&workerPlayer0, SIGNAL(finished()), threadPlayer0, SLOT(quit()));
	QObject::connect(threadPlayer0, SIGNAL(finished()), threadPlayer0, SLOT(deleteLater()));

	QThread* threadPlayer1 = new QThread;
	AIWorker workerPlayer1;
	workerPlayer1.moveToThread(threadPlayer1);
	QObject::connect(threadPlayer1, &QThread::started, &workerPlayer1, &AIWorker::process);
	QObject::connect(&workerPlayer1, SIGNAL(finished()), threadPlayer1, SLOT(quit()));
	QObject::connect(threadPlayer1, SIGNAL(finished()), threadPlayer1, SLOT(deleteLater()));

	QThread* gameWorkerThread = new QThread;
	GameWorker gameWorker(&workerPlayer0.messageManager, &workerPlayer1.messageManager, generator.grid);
	gameWorker.moveToThread(gameWorkerThread);
	QObject::connect(gameWorkerThread, &QThread::started, &gameWorker, &GameWorker::process);
	QObject::connect(&gameWorker, SIGNAL(finished()), gameWorkerThread, SLOT(quit()));
	QObject::connect(gameWorkerThread, SIGNAL(finished()), gameWorkerThread, SLOT(deleteLater()));

	threadPlayer0->start();
	threadPlayer1->start();
	gameWorkerThread->start();

	app.exec();
}