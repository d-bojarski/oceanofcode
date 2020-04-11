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
	grid(grid),
	player0(0, 6, 0, 0, 0, 0),
	player1(1, 6, 0, 0, 0, 0)
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

	std::string player0Orders;
	std::string player1Orders;
	std::string player0OrdersPreviousTurn;
	std::string player1OrdersPreviousTurn;
	while (1)
	{
		play(0, player1OrdersPreviousTurn, player0Orders);
		play(1, player0OrdersPreviousTurn, player1Orders);
		player0OrdersPreviousTurn = player0Orders;
		player1OrdersPreviousTurn = player1Orders;
	}

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

	std::string position;
	messageManager->read(&position);
	messageManager->debug("position:" + position);
}

void GameWorker::play(int id, const std::string& opponentOrders, std::string& playerOrders)
{
	MessageManager* messageManager = (id == 0) ? messageManagerPlayer0 : messageManagerPlayer1;
	Player& currentPlayer = (id == 0) ? player0 : player1;
	Player& opponentPlayer = (id == 1) ? player0 : player1;

	std::string sonarResult = "sonarResult";

	messageManager->send(currentPlayer.x);
	messageManager->send(currentPlayer.y);
	messageManager->send(currentPlayer.life);
	messageManager->send(opponentPlayer.life);
	messageManager->send(currentPlayer.torpedoCooldown);
	messageManager->send(currentPlayer.sonarCooldown);
	messageManager->send(currentPlayer.silenceCooldown);
	messageManager->send(currentPlayer.mineCooldown);

	messageManager->send(sonarResult);
	messageManager->send(opponentOrders);

	messageManager->read(&playerOrders);
	messageManager->debug("playerOrders:" + playerOrders);
}
