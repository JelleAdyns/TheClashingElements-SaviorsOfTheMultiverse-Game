#include "Boss.h"

Boss::Boss(const Point2Int& bottomCenter, int speed):
	Enemy{ bottomCenter,_T("Boss.png"), SpriteInfo{.nrOfCols{ 8 }, .nrOfFrames{32}, .frameTime{ 1.f / 15}} }
{

	Character::SetDefaultSpeed(speed);

}
