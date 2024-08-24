#include "Escalator.h"

const int Escalator::m_Speed{ Tile::Size * 2 };

Escalator::Escalator(const Point2Int& startCenter, const Point2Int& endCenter, bool isDownwards) :
	m_Velocity{ isDownwards ? -m_Speed : m_Speed },

	m_Area{ RectInt{startCenter.x - Tile::Size / 2, endCenter.y + Tile::Size / 2 , Tile::Size, (startCenter.y - endCenter.y) - Tile::Size} },

	m_TargetRect{ isDownwards ? RectInt{endCenter.x - Tile::Size / 2, endCenter.y , Tile::Size, Tile::Size / 2} :
							    RectInt{startCenter.x - Tile::Size / 2, startCenter.y - Tile::Size / 2 , Tile::Size, Tile::Size / 2} }
{

}

int Escalator::GetVelocity(const Point2Int& bottomCenter) const
{
	if (utils::IsPointInRect(bottomCenter, m_Area)) return m_Velocity;

	return 0;
}