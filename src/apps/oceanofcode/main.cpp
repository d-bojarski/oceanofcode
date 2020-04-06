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

	//QThread* thread = new QThread;
	//AIWorker worker;
	//worker.moveToThread(thread);

	////QObject::connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
	//QObject::connect(thread, &QThread::started, &worker, &AIWorker::process);
	//QObject::connect(&worker, SIGNAL(finished()), thread, SLOT(quit()));
	////QObject::connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
	//QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	//thread->start();

	app.exec();
}