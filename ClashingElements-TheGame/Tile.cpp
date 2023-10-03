#include "pch.h"
#include "Tile.h"

const int Tile::Size{16};

Tile::Tile(int id, int centerX, int centerY, bool isIntersection)
	:Id{ id }
	, CenterX{ centerX }
	, CenterY{ centerY }
	, Area{ Rectf{centerX - float(Size / 2), centerY - float(Size / 2), float(Size), float(Size)} }
	, IsIntersection{ isIntersection }
{
	
}

