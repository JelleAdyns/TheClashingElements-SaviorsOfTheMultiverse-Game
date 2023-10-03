#include "pch.h"
#include "Escalator.h"

const int Escalator::m_Speed{ Tile::Size * 2 };

Escalator::Escalator(const Point2f& startCenter, const Point2f& endCenter, bool isDownwards) :
	m_Velocity{ isDownwards ? -m_Speed : m_Speed },

	m_Area{ Rectf{startCenter.x - Tile::Size / 2, endCenter.y + Tile::Size / 2 , float(Tile::Size), (startCenter.y - endCenter.y) - Tile::Size} },

	m_TargetRect{ isDownwards ? Rectf{endCenter.x - Tile::Size / 2, endCenter.y , float(Tile::Size), float(Tile::Size / 2)} :
							    Rectf{startCenter.x - Tile::Size / 2, startCenter.y - Tile::Size / 2 , float(Tile::Size), float(Tile::Size / 2)} }
{

}

int Escalator::GetVelocity(const Point2f& bottomCenter) const
{
	if (utils::IsPointInRect(bottomCenter, m_Area)) return m_Velocity;

	return 0;
}