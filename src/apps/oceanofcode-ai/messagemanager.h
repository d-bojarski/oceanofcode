#pragma once

#include <string>

class MessageManager
{
public:
	MessageManager();
	~MessageManager();

#ifdef LIBRARY
	void send(const std::string& message);
	void send(const int message);
#endif

	void read(std::string* value);
	void read(int* value);

	void write(const std::string& message);
	void debug(const std::string& message);
};

