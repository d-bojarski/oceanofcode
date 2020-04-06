#include "tile.h"


Tile::Tile() :
	Tile(0, 0, "")
{
}

Tile::Tile(int x, int y, const QString& imageName) :
	x(x),
	y(y),
	imageName(imageName)
{
}
