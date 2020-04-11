#include "messagemanager.h"

//---------------------------------------
//------- Constructors/Destructors ------
//---------------------------------------
MessageManager::MessageManager()
#ifdef LIBRARY
	: _mutex(),
	_waitCondition(),
	_clientReady(false),
	_valueString(std::string()),
	_valueInt(0)
#endif
{
}

MessageManager::~MessageManager()
{
}

//---------------------------------------
//---- Public methods implementation ----
//---------------------------------------

void MessageManager::send(const std::string& value)
{
#ifdef LIBRARY
	_mutex.lock();
	if (!_clientReady)
	{
		_waitCondition.wait(&_mutex);
	}
	_clientReady = false;
	_mutex.unlock();

	_mutex.lock();
	_valueString = value;
	//qDebug() << "Send" << value;
	_mutex.unlock();
	_waitCondition.wakeAll();
#else
	std::cout << value << std::endl;
#endif
}

void MessageManager::send(const int value)
{
#ifdef LIBRARY
	_mutex.lock();
	if (!_clientReady)
	{
		//qDebug() << "Client not ready";
		_waitCondition.wait(&_mutex);
	}
	_clientReady = false;
	_mutex.unlock();

	_mutex.lock();
	_valueInt = value;
	//qDebug() << "Send" << value;
	_mutex.unlock();
	_waitCondition.wakeAll();
#endif
}

void MessageManager::read(std::string* value)
{
#ifdef LIBRARY
	_mutex.lock();
	_clientReady = true;
	_mutex.unlock();
	_waitCondition.wakeAll();

	_mutex.lock();
	_waitCondition.wait(&_mutex);
	*value = _valueString;
	//qDebug() << "Read" << QString::fromStdString(*value);
	_mutex.unlock();
#else
	std::getline(std::cin, *value);
#endif
}

void MessageManager::read(int* value)
{
#ifdef LIBRARY
	_mutex.lock();
	//qDebug() << "Client ready";
	_clientReady = true;
	_mutex.unlock();
	_waitCondition.wakeAll();


	_mutex.lock();
	//qDebug() << "Client wait";
	_waitCondition.wait(&_mutex);
	*value = _valueInt;
	//qDebug() << "Read" << *value;
	_mutex.unlock();
#else
	std::cin >> *value;
#endif
}

void MessageManager::readIgnore()
{
#ifdef LIBRARY
#else
	std::cin.ignore();
#endif
}

void MessageManager::debug(const std::string& message)
{
#ifdef LIBRARY
	qDebug().noquote() << QString::fromStdString(message);
#else
	std::cerr << message << std::endl;
#endif
}