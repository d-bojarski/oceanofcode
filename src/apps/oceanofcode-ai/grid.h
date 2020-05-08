#pragma once

#include <string>
#include "player.h"
#include "path.h"

class Grid
{
public:
	Grid();
	Grid(const Grid &grid);
	~Grid();

	void initialize();

	void show() const;

	void fill(int value);
	void fill(const Path& path);
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

