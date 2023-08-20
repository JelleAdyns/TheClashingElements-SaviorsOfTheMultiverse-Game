#include "pch.h"
#include "AnimBackGround.h"


AnimBackGround::AnimBackGround(const Point2f& bottomCenter, const std::string& filePath) :
	AnimatedSprite{ bottomCenter, 3, 3, 1.f / 8 }
{
	m_pTexture = new Texture{filePath} ;
	AnimatedSprite::SetTexture(m_pTexture);
}
AnimBackGround::~AnimBackGround()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

//void AnimBackGround::Update(float elapsedSec)
//{
//	m_PassedTime += elapsedSec;
//	if (m_PassedTime >= m_FrameTime)
//	{
//		++m_CurrentCol %= m_NrOfCols;
//		m_PassedTime = 0.f;
//	}
//}