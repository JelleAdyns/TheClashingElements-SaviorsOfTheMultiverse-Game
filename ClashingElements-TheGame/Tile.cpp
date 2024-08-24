#include "Tile.h"

const int Tile::Size{16};

Tile::Tile(TileID id, int centerX, int centerY, bool isIntersection) :
	Tile{ id, Point2Int{centerX, centerY}, isIntersection }
{}

Tile::Tile(TileID id, Point2Int center, bool isIntersection)
	:Id{ id }
	, Center{ center }
	, Area{ RectInt{center.x - Size / 2, center.y - Size / 2, Size, Size} }
	, IsIntersection{ isIntersection }
	, IsWalkable{true}

{
	
}

