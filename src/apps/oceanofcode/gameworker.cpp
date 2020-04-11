#include "gameworker.h"

#include <iostream>

#include <qthread.h>

GameWorker::GameWorker(
	MessageManager* messageManagerPlayer0,
	MessageManager* messageManagerPlayer1,
	const Grid& grid,
	QObject* parent) :
	QObject(parent),
	messageManagerPlayer0(messageManagerPlayer0),
	messageManagerPlayer1(messageManagerPlayer1),
	grid(grid)
{
}

GameWorker::~GameWorker()
{
}

void GameWorker::process()
{
	std::cout << "GameWorker::process" << std::endl;

	initializePlayer(0);
	initializePlayer(1);

	std::cout << "finished" << std::endl;
	emit finished();
}

void GameWorker::initializePlayer(int id)
{
	MessageManager* messageManager = (id == 0) ? messageManagerPlayer0 : messageManagerPlayer1;

	messageManager->send(grid.width);
	messageManager->send(grid.height);
	messageManager->send(id);
	for (int i = 0; i < grid.height; i++)
	{
		messageManager->send(grid.toLine(i));
	}


}
