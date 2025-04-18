#include "AnimBackGround.h"

const int AnimBackGround::m_NrOfCols{ 1 };

AnimBackGround::AnimBackGround(const tstring& filePath) :
	AnimatedSprite{ Point2Int{}, filePath, SpriteInfo{.nrOfCols{m_NrOfCols}, .nrOfFrames{1}, .frameTime{1.f/8}}}
{
	m_BottomCenter.x = static_cast<int>(GetTexture().GetWidth() / m_NrOfCols / 2);
}
