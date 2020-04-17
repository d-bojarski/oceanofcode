#pragma once

#include "aiworker.h"
#include "messagemanager.h"
#include "grid.h"
#include "player.h"

#include <qobject.h>

class GameWorker : public QObject
{
	Q_OBJECT
public:
	GameWorker(
		MessageManager* messageManagerPlayer0,
		MessageManager* messageManagerPlayer1,
		const Grid& grid,
		QObject *parent = nullptr);
	~GameWorker();

public slots:
	void process();

signals:
	void update();
	void finished();
	void snapshot(int turnCount, const QString& name, const Grid& grid);

private:
	bool initializePlayer(int id);
	bool play(int turnCount, int id, const std::string& opponentOrders, std::string& playerOrders);

public:
	MessageManager* messageManagerPlayer0;
	MessageManager* messageManagerPlayer1;
	const Grid& grid;

	Player player0;
	Player player1;
};