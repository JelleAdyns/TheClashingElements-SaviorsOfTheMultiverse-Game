#ifndef TILE_H
#define TILE_H

#include "Collectable.h"
using TileID = int;

struct Tile
{
	explicit Tile(TileID id, int centerX, int centerY, bool isIntersection = false);
	explicit Tile(TileID id, Point2Int center, bool isIntersection = false);
	const static int Size;

	const TileID Id;
	const Point2Int Center;
	const RectInt Area;
	const bool IsIntersection;
	
	bool IsWalkable;

};


#endif // !TILE_H

