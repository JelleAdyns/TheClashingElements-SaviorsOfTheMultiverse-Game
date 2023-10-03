#pragma once
#include "Collectable.h"

struct Tile
{
	explicit Tile(int id, int centerX, int centerY, bool isIntersection = false);
	const static int Size;

	const int Id;
	const int CenterX;
	const int CenterY;
	const Rectf Area;
	const bool IsIntersection;

};

