#pragma once

#include "grid.h"

#include <string>
#include <vector>

#ifdef LIBRARY
#include <qdebug.h>
#include <qstring.h>
#include <qmutex.h>
#include <qwaitcondition.h>
#else
#include <iostream>
#endif

struct Snapshot
{
	std::string name;
	const Grid grid;
};

class MessageManager
{
public:
	MessageManager();
	~MessageManager();

	bool send(const std::string& message);
	bool send(const int message);

	bool read(std::string* value);
	bool read(int* value);
	void readIgnore();

	void debug(const std::string& message);
	void snapshot(const std::string& name, const Grid& grid);

	void clearSnapshots();
	std::vector<Snapshot> getSnapshots();

private:
	bool senderWait();

	//void receiverReady();
	bool receive(int* value);
	bool receive(std::string* value);

protected:
#ifdef LIBRARY
	QMutex _mutex;
	QWaitCondition _waitCondition;

	bool _receiverReady;

	std::string _valueString;
	int _valueInt;
#endif
	bool _stop;
	const int _timeout;
	std::vector<Snapshot> snapshots;
};
