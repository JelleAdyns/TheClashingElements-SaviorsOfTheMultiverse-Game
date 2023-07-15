#include "pch.h"
#include "Tile.h"
//#include "Collectable.h"

int Tile::Size{16};

Tile::Tile(const int id, const int centerX, const int centerY, const bool isIntersection)
	:Id{ id }
	, CenterX{ centerX }
	, CenterY{ centerY }
	, Area{ Rectf{centerX - float(Size / 2), centerY - float(Size / 2), float(Size), float(Size)} }
	, IsIntersection{ isIntersection }
{
	
}