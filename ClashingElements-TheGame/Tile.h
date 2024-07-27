#ifndef TILE_H
#define TILE_H

#include "Collectable.h"

struct Tile
{
	explicit Tile(int id, int centerX, int centerY, bool isIntersection = false);
	const static int Size;

	const int Id;
	const int CenterX;
	const int CenterY;
	const RectInt Area;
	const bool IsIntersection;

};


#endif // !TILE_H

