#include "AnimBackGround.h"

const int AnimBackGround::m_NrOfCols{ 3 };

AnimBackGround::AnimBackGround(const std::wstring& filePath) :
	AnimatedSprite{ Point2Int{},m_NrOfCols, 3, 1.f / 8}
{
	m_pTexture = std::make_unique<Texture>(filePath);
	m_BottomCenter.x = static_cast<int>(m_pTexture->GetWidth() / m_NrOfCols / 2);
	AnimatedSprite::SetTexture(m_pTexture.get());
}
