#include "messagemanager.h"

#ifdef LIBRARY
#include <qdebug.h>
#include <qstring.h>
#include <qmutex.h>
#include <qwaitcondition.h>
#else
#include <iostream>
#endif

#ifdef LIBRARY
QMutex _mutex;
QWaitCondition _waitCondition;

std::string _valueString;
int _valueInt;
#endif

//---------------------------------------
//------- Constructors/Destructors ------
//---------------------------------------
MessageManager::MessageManager()
{
}

MessageManager::~MessageManager()
{
}

//---------------------------------------
//---- Public methods implementation ----
//---------------------------------------
#ifdef LIBRARY
void MessageManager::send(const std::string& value)
{
	_valueString = value;
	_waitCondition.wakeAll();
}

void MessageManager::send(const int value)
{
	_valueInt = value;
	_waitCondition.wakeAll();
}
#endif

void MessageManager::read(std::string* value)
{
#ifdef LIBRARY
	_mutex.lock();
	_waitCondition.wait(&_mutex);
	*value = _valueString;
	_mutex.unlock();
#else
	std::cin >> *value;
#endif
}

void MessageManager::read(int* value)
{
#ifdef LIBRARY
	_mutex.lock();
	_waitCondition.wait(&_mutex);
	*value = _valueInt;
	_mutex.unlock();
#else
	std::cin >> *value;
#endif
}

void MessageManager::write(const std::string& message)
{
#ifdef LIBRARY
	qDebug() << QString::fromStdString(message);
#else
	std::cout << message << std::endl;
#endif
}

void MessageManager::debug(const std::string& message)
{
#ifdef LIBRARY
	qDebug() << QString::fromStdString(message);
#else
	std::cerr << message << std::endl;
#endif
}
