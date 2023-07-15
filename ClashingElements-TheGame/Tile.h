#pragma once
#include "Collectable.h"

struct Tile
{
	explicit Tile(const int id, const int centerX, const int centerY, const bool isIntersection = false);
	static int Size;

	int Id;
	int CenterX;
	int CenterY;
	Rectf Area;
	bool IsIntersection;

};

