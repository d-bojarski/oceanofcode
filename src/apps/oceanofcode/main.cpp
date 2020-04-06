#include "gridgenerator.h"
#include "view.h"
#include "aiworker.h"

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

	QThread* thread = new QThread;
	AIWorker worker;
	worker.moveToThread(thread);

	QObject::connect(thread, &QThread::started, &worker, &AIWorker::process);
	QObject::connect(&worker, SIGNAL(finished()), thread, SLOT(quit()));
	QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();

	QThread::msleep(100);
	worker.messageManager.send(40);

	app.exec();
}