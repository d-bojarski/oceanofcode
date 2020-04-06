#pragma once

#include <string>

class Grid
{
public:
	Grid();
	explicit Grid(const Grid &grid);
	~Grid();

	void initialize();

	void show();

	void emptyCopy(const Grid& source);
	void reverse();

	short* operator[](int index) const;
	void operator=(const Grid& grid);

public:
	int width;
	int height;

private:
	short** boxes;

};

