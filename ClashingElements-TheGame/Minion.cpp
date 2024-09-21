#include "Minion.h"

int Minion::m_DefaultSpeed{Tile::Size * 3};

Minion::Minion(const Point2Int& bottomCenter) :
	Enemy{ bottomCenter,_T("Minion.png"), SpriteInfo{.nrOfCols{3}, .nrOfFrames{ 12 }, .frameTime{ 1.f / 8}}, 40 }
{
	Character::SetDefaultSpeed(m_DefaultSpeed);
}