#pragma once

#include <string>
#include "player.h"

class Grid
{
public:
	Grid();
	Grid(const Grid &grid);
	~Grid();

	void initialize();

	void show() const;

	void fill(int value);
	// Fill ground position.
	void fill(int lineNumber, const std::string& lineValue);
	std::string toLine(int lineNumber) const;

	void emptyCopy(const Grid& source);
	void reverse();
	void inverse();

	//bool canMove(const Player& player, int x, int y) const;


	short* operator[](int index) const;
	void operator=(const Grid& _grid);
	void operator=(Grid& _grid);

public:
	int width;
	int height;

private:
	short** boxes;

};

