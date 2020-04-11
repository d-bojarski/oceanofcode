#include "grid.h"

#include <iostream>

//---------------------------------------
//------- Constructors/Destructors ------
//---------------------------------------
Grid::Grid() :
	width(0),
	height(0),
	boxes(nullptr)
{
}

Grid::Grid(const Grid& grid)
{
	operator=(grid);
}

Grid::~Grid()
{
	if (boxes != nullptr)
	{
		for (size_t i = 0; i < height; i++)
		{
			delete boxes[i];
		}
		delete boxes;
	}
}

//---------------------------------------
//---- Public methods implementation ----
//---------------------------------------
void Grid::initialize()
{
	boxes = new short* [height];
	for (int i = 0; i < height; i++)
	{
		boxes[i] = new short[width] { 0 };
	}
}

void Grid::show()
{
	std::string output;
	output.append("GRID:\n");
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			output.append(std::to_string(boxes[h][w]));
		}
		output.append("\n");
	}
	std::cerr << output;
}

void Grid::fill(int lineNumber, const std::string& lineValue)
{
	for (int w = 0; w < lineValue.size(); w++)
	{
		boxes[lineNumber][w] = (lineValue.at(w) == 'x') ? 1 : 0;
	}
}

std::string Grid::toLine(int lineNumber) const
{
	std::string line;
	for (int w = 0; w < width; w++)
	{
		line.append((boxes[lineNumber][w] == 1) ? "x" : ".");
	}
	return line;
}

void Grid::emptyCopy(const Grid& source)
{
	width = source.width;
	height = source.height;
	initialize();
}

void Grid::reverse()
{
	// Works on binary grid.
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			boxes[h][w] = (boxes[h][w] == 1 ? 0 : 1);
		}
	}
}

short* Grid::operator[](int index) const
{
	return boxes[index];
}

void Grid::operator=(const Grid& grid)
{
	emptyCopy(grid);

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			boxes[h][w] = grid[h][w];
		}
	}
}
