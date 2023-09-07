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

struct Escalator
{
	explicit Escalator(const Point2f& startCenter, const Point2f& endCenter, bool isDownwards);
	const static int Speed;

	const int Velocity;
	const Rectf Area;
	const Rectf TargetRect;
};