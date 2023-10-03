#include "pch.h"
#include "AnimBackGround.h"


const int AnimBackGround::m_NrOfCols{ 3 };

AnimBackGround::AnimBackGround(const std::string& filePath) :
	AnimatedSprite{ Point2f{},m_NrOfCols, 3, 1.f / 8}
{
	m_pTexture = new Texture{filePath} ;
	m_BottomCenter.x = m_pTexture->GetWidth()/ m_NrOfCols / 2;
	AnimatedSprite::SetTexture(m_pTexture);
}
AnimBackGround::~AnimBackGround()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

