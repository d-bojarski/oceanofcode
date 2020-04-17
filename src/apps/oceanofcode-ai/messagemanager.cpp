#include "messagemanager.h"

//---------------------------------------
//------- Constructors/Destructors ------
//---------------------------------------
MessageManager::MessageManager() :
#ifdef LIBRARY
	_mutex(),
	_waitCondition(),
	_receiverReady(false),
	_valueString(),
	_valueInt(0),
#endif
	_stop(false),
	_timeout(1000)
{
}

MessageManager::~MessageManager()
{
}

//---------------------------------------
//---- Public methods implementation ----
//---------------------------------------

bool MessageManager::send(const std::string& value)
{
#ifdef LIBRARY
	bool success = true;
	if (!senderWait())
	{
		debug("MessageManager::send string timeout");
		success = false;
	}
	else
	{
		_mutex.lock();
		_valueString = value;
		//qDebug() << "Send" << value;
		_mutex.unlock();
		_waitCondition.wakeAll();
	}
	return success;
#else
	std::cout << value << std::endl;
	return true;
#endif
}

bool MessageManager::send(const int value)
{
#ifdef LIBRARY
	bool success = true;
	if (!senderWait())
	{
		debug("MessageManager::send int timeout");
		success = false;
	}
	else
	{
		_mutex.lock();
		_valueInt = value;
		//qDebug() << "Send" << value;
		_mutex.unlock();
		_waitCondition.wakeAll();
	}
	return success;
#else
	std::cout << value << std::endl;
	return true;
#endif
}

bool MessageManager::read(std::string* value)
{
#ifdef LIBRARY
	//receiverReady();
	return receive(value);
#else
	std::getline(std::cin, *value);
	return true;
#endif
}

bool MessageManager::read(int* value)
{
#ifdef LIBRARY
	//receiverReady();
	return receive(value);
#else
	std::cin >> *value;
	return true;
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

void MessageManager::snapshot(const std::string& name, const Grid& grid)
{
	snapshots.push_back(Snapshot{ name, grid });
}

void MessageManager::clearSnapshots()
{
	snapshots.clear();
}

std::vector<Snapshot> MessageManager::getSnapshots()
{
	return snapshots;
}

bool MessageManager::senderWait()
{
#ifdef LIBRARY
	bool success = true;
	_mutex.lock();
	if (!_receiverReady)
	{
		success = _waitCondition.wait(&_mutex, _timeout);
	}
	_receiverReady = false;
	_mutex.unlock();

	return success;
#else
	return false;
#endif
}

//void MessageManager::receiverReady()
//{
//#ifdef LIBRARY
//	_mutex.lock();
//	_receiverReady = true;
//	_waitCondition.wakeAll();
//	_mutex.unlock();
//#endif
//}

bool MessageManager::receive(int* value)
{
#ifdef LIBRARY
	bool success = true;
	_mutex.lock();
	_receiverReady = true;
	_waitCondition.wakeAll();
	if (!_waitCondition.wait(&_mutex, _timeout))
	{
		debug("MessageManager::receive int timeout");
		success = false;
	}
	else
	{
		*value = _valueInt;
	}
	_mutex.unlock();
	return success;
#else
	return false;
#endif
}

bool MessageManager::receive(std::string* value)
{
#ifdef LIBRARY
	bool success = true;
	_mutex.lock();
	_receiverReady = true;
	_waitCondition.wakeAll();
	if (!_waitCondition.wait(&_mutex, _timeout))
	{
		debug("MessageManager::receive string timeout");
		success = false;
	}
	else
	{
		*value = _valueString;
	}
	_mutex.unlock();
	return success;
#else
	return false;
#endif
}
