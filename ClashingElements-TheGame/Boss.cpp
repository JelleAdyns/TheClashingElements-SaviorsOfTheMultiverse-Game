#include "Boss.h"

int Boss::m_DefaultSpeed{ 0 };
Boss::Boss(const Point2Int& bottomCenter, int speed):
	Enemy{ bottomCenter,_T("Boss.png"), SpriteInfo{.nrOfCols{ 8 }, .nrOfFrames{32}, .frameTime{ 1.f / 15}} }
{
	m_DefaultSpeed = speed;

	Character::SetDefaultSpeed(m_DefaultSpeed);


}
