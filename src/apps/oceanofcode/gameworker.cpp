#include "gameworker.h"

#include <iostream>
#include <sstream>

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

	bool run = true;

	run = run && initializePlayer(0);
	run = run && initializePlayer(1);

	emit update();

	std::string player0Orders;
	std::string player1Orders;
	std::string player0OrdersPreviousTurn;
	std::string player1OrdersPreviousTurn;
	int turnCount = 0;
	while (++turnCount < 5 && run)
	{
		std::cout << "Turn n-" << turnCount << std::endl;
		run = run && play(turnCount, 0, player1OrdersPreviousTurn, player0Orders);
		run = run && play(turnCount, 1, player0OrdersPreviousTurn, player1Orders);

		QThread::msleep(250);
		player0OrdersPreviousTurn = player0Orders;
		player1OrdersPreviousTurn = player1Orders;
	}

	std::cout << "GameWorker::process finished" << std::endl;
	emit finished();
}

bool GameWorker::initializePlayer(int id)
{
	MessageManager* messageManager = (id == 0) ? messageManagerPlayer0 : messageManagerPlayer1;
	Player& currentPlayer = (id == 0) ? player0 : player1;

	bool run = true;

	run = run && messageManager->send(grid.width);
	run = run && messageManager->send(grid.height);
	run = run && messageManager->send(id);
	for (int i = 0; i < grid.height && run; i++)
	{
		run = run && messageManager->send(grid.toLine(i));
	}

	// Handle player position
	std::string position;
	run = run && messageManager->read(&position);
	std::cout << "position" << position << std::endl;

	std::string token;
	std::istringstream tokenStream(position);
	if (std::getline(tokenStream, token, ' '))
	{
		currentPlayer.x = std::atoi(token.c_str());
	}
	if (std::getline(tokenStream, token, ' '))
	{
		currentPlayer.x = std::atoi(token.c_str());
	}

	emit update();



	return run;
}

bool GameWorker::play(int turnCount, int id, const std::string& opponentOrders, std::string& playerOrders)
{
	MessageManager* messageManager = (id == 0) ? messageManagerPlayer0 : messageManagerPlayer1;
	Player& currentPlayer = (id == 0) ? player0 : player1;
	Player& opponentPlayer = (id == 1) ? player0 : player1;

	bool run = true;

	std::string sonarResult = "sonarResult";

	run = run && messageManager->send(currentPlayer.x);
	run = run && messageManager->send(currentPlayer.y);
	run = run && messageManager->send(currentPlayer.life);
	run = run && messageManager->send(opponentPlayer.life);
	run = run && messageManager->send(currentPlayer.torpedoCooldown);
	run = run && messageManager->send(currentPlayer.sonarCooldown);
	run = run && messageManager->send(currentPlayer.silenceCooldown);
	run = run && messageManager->send(currentPlayer.mineCooldown);

	run = run && messageManager->send(sonarResult);
	run = run && messageManager->send(opponentOrders);

	run = run && messageManager->read(&playerOrders);
	//messageManager->debug("playerOrders" + std::to_string(id) + ": " + playerOrders);

	const auto& snapshots = messageManagerPlayer0->getSnapshots();
	for (unsigned int i = 0; i < snapshots.size(); i++)
	{
		const auto& s = snapshots.at(i);
		emit snapshot(
			turnCount,
			QString::fromStdString(s.name),
			s.grid);
	}
	messageManagerPlayer0->clearSnapshots();

	return run;
}
