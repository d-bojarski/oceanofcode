#pragma once

#include <string>

#ifdef LIBRARY
#include <qdebug.h>
#include <qstring.h>
#include <qmutex.h>
#include <qwaitcondition.h>
#else
#include <iostream>
#endif

class MessageManager
{
public:
	MessageManager();
	~MessageManager();

	void send(const std::string& message);
	void send(const int message);

	void read(std::string* value);
	void read(int* value);
	void readIgnore();

	void write(const std::string& message);
	void debug(const std::string& message);

#ifdef LIBRARY
protected:
	QMutex _mutex;
	QWaitCondition _waitCondition;

	bool _clientReady;

	std::string _valueString;
	int _valueInt;
#endif
};

