#include "AnimBackGround.h"

const int AnimBackGround::m_NrOfCols{ 3 };

AnimBackGround::AnimBackGround(const tstring& filePath) :
	AnimatedSprite{ Point2Int{}, filePath, SpriteInfo{.nrOfCols{m_NrOfCols}, .nrOfFrames{3}, .frameTime{1.f/8}}}
{
	m_BottomCenter.x = static_cast<int>(GetTexture().GetWidth() / m_NrOfCols / 2);
}
