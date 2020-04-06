#pragma once

#include "player.h"
#include "grid.h"

class AI
{
public:
	AI();
	~AI();

	void start();

	// Fill ground position.
	void fill(short* line, const std::string& lineValue);
	void calculateGridAccess();

	void calculateOptimalPath();

private:
	Player me;
	Player opponent;

	// Grid with sea=0 and earth=1.
	Grid grid;

	// Grid with access number.
	Grid gridAccess;

	// Grid with path already used
	Grid gridUsedPath;

};

