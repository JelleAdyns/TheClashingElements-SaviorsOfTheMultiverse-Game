#include "pch.h"
#include "AnimatedSprite.h"
#include "Texture.h"

AnimatedSprite::AnimatedSprite(const Point2f& bottomCenter, int nrCols, int nrFrames, float frameTime):
	m_BottomCenter{bottomCenter},

	m_CurrentCol{0},
	m_CurrentRow{0},
	
	m_NrOfCols{nrCols},
	m_NrOfFrames{nrFrames},
	m_NrOfRows{nrFrames/nrCols},
	m_FrameTime{frameTime},
	
	m_PassedTime{0.f},

	m_pTexture{nullptr}
{

}

AnimatedSprite::~AnimatedSprite()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void AnimatedSprite::Draw() const
{
	m_pTexture->Draw(DestRect(), SrcRect());
}

void AnimatedSprite::Update(float elapsedSec)
{
	m_PassedTime += elapsedSec;
	if (m_PassedTime >= m_FrameTime)
	{
		if (m_CurrentCol == m_NrOfCols - 1) ++m_CurrentRow %= m_NrOfRows;
		++m_CurrentCol %= m_NrOfCols;
		m_PassedTime = 0.f;
	}
}

void AnimatedSprite::SetTexture(const Texture* texturePtr)
{
	m_pTexture = texturePtr;
}

Rectf AnimatedSprite::DestRect() const
{
	return Rectf{ m_BottomCenter.x - SrcRect().width / 2, m_BottomCenter.y, SrcRect().width , SrcRect().height };
}

Rectf AnimatedSprite::SrcRect() const
{
	Rectf srcRect{};
	srcRect.width = m_pTexture->GetWidth() / m_NrOfCols;
	srcRect.height = m_pTexture->GetHeight() / m_NrOfRows;
	srcRect.left = srcRect.width * m_CurrentCol;
	srcRect.bottom = srcRect.height * (m_CurrentRow + 1);
	return srcRect;
}