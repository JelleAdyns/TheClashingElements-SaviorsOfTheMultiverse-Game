#include "Tile.h"

const int Tile::Size{16};

Tile::Tile(int id, int centerX, int centerY, bool isIntersection)
	:Id{ id }
	, CenterX{ centerX }
	, CenterY{ centerY }
	, Area{ RectInt{centerX - Size / 2, centerY - Size / 2, Size, Size} }
	, IsIntersection{ isIntersection }
{
	
}

