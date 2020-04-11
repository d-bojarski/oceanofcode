#pragma once

#include "aiworker.h"
#include "messagemanager.h"
#include "grid.h"

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
	void finished();

private:
	void initializePlayer(int id);

public:
	MessageManager* messageManagerPlayer0;
	MessageManager* messageManagerPlayer1;
	const Grid& grid;
};