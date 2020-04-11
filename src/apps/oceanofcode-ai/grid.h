#pragma once

#include <string>

class Grid
{
public:
	Grid();
	explicit Grid(const Grid &grid);
	~Grid();

	void initialize();

	void show() const;

	// Fill ground position.
	void fill(int lineNumber, const std::string& lineValue);
	std::string toLine(int lineNumber) const;


	void emptyCopy(const Grid& source);
	void reverse();
	void inverse();

	short* operator[](int index) const;
	void operator=(const Grid& grid);

public:
	int width;
	int height;

private:
	short** boxes;

};

