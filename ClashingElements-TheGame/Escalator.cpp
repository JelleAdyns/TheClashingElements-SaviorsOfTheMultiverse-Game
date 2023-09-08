#include "pch.h"
#include "Escalator.h"

//const int Escalator::Speed{ Tile::Size * 2 };
//
//Escalator::Escalator(const Point2f& startCenter, const Point2f& endCenter, bool isDownwards) :
//	Velocity{ isDownwards ? -Speed : Speed },
//	Area{ Rectf{startCenter.x - Tile::Size / 2, endCenter.y + Tile::Size / 2 , Tile::Size, (startCenter.y - endCenter.y) - Tile::Size} },
//	TargetRect{ isDownwards ? Rectf{endCenter.x - Tile::Size / 2, endCenter.y , Tile::Size, Tile::Size / 2} :
//							  Rectf{startCenter.x - Tile::Size / 2, startCenter.y - Tile::Size / 2 , Tile::Size, Tile::Size / 2} }
//{
//
//}