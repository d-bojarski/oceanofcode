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

	qRegisterMetaType<Grid>("Grid");

	GridGenerator generator(15);
	generator.seed = 999;
	generator.generate();

	View view;
	view.fillGround(generator.grid, generator.tiles);
	view.show();

	QThread threadPlayer0;
	AIWorker workerPlayer0;
	workerPlayer0.moveToThread(&threadPlayer0);
	QObject::connect(&threadPlayer0, &QThread::started, &workerPlayer0, &AIWorker::process);
	QObject::connect(&workerPlayer0, &AIWorker::finished, &threadPlayer0, &QThread::quit);

	QThread threadPlayer1;
	AIWorker workerPlayer1;
	workerPlayer1.moveToThread(&threadPlayer1);
	QObject::connect(&threadPlayer1, &QThread::started, &workerPlayer1, &AIWorker::process);
	QObject::connect(&workerPlayer1, &AIWorker::finished, &threadPlayer1, &QThread::quit);

	QThread gameWorkerThread;
	GameWorker gameWorker(&workerPlayer0.messageManager, &workerPlayer1.messageManager, generator.grid);
	gameWorker.moveToThread(&gameWorkerThread);
	QObject::connect(&gameWorkerThread, &QThread::started, &gameWorker, &GameWorker::process);
	QObject::connect(&gameWorker, &GameWorker::update, &view, &View::updateView);
	QObject::connect(&gameWorker, &GameWorker::snapshot, &view, &View::snapshot);
	QObject::connect(&gameWorker, &GameWorker::finished, &gameWorkerThread, &QThread::quit);
	QObject::connect(&gameWorker, &GameWorker::finished, [&]
	{
		workerPlayer0.ai.stop();
		workerPlayer1.ai.stop();
	});



	view.player0 = &gameWorker.player0;
	view.player1 = &gameWorker.player1;

	threadPlayer0.start();
	threadPlayer1.start();
	gameWorkerThread.start();

	app.exec();
}