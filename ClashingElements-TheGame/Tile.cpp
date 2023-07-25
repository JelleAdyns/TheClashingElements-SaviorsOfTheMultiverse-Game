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

const int Escalator::Speed{Tile::Size};

Escalator::Escalator(const Point2f& startCenter, const Point2f& endCenter, bool isDownwards) :
	Velocity{isDownwards ? -Speed : Speed},
	Area{Rectf{startCenter.x - Tile::Size/2, endCenter.y + Tile::Size/2, Tile::Size, (startCenter.y - endCenter.y) - Tile::Size} }
{

}