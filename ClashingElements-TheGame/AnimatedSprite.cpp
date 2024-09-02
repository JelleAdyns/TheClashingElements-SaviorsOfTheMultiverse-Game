#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const Point2Int& bottomCenter, int nrCols, int nrFrames, float frameTime, bool updateRows):
	m_BottomCenter{bottomCenter},

	m_CurrentCol{0},
	m_CurrentRow{0},
	
	m_NrOfCols{nrCols},
	m_NrOfFrames{nrFrames},
	m_NrOfRows{nrFrames/nrCols},
	m_FrameTime{frameTime},
	
	m_PassedTime{0.f},

	m_pTexture{nullptr},
	m_UpdateRows{updateRows}
{

}

AnimatedSprite::~AnimatedSprite()
{
	m_pTexture = nullptr;
}

void AnimatedSprite::Draw() const
{
	ENGINE.DrawTexture(*m_pTexture, DestRect(), SrcRect());
}

void AnimatedSprite::Update()
{
	m_PassedTime += ENGINE.GetDeltaTime();
	if (m_PassedTime >= m_FrameTime)
	{
		if (m_UpdateRows)
		{
			if (m_CurrentCol == m_NrOfCols - 1) ++m_CurrentRow %= m_NrOfRows;
		}
		++m_CurrentCol %= m_NrOfCols;
		m_PassedTime = 0.f;
	}
}

void AnimatedSprite::SetTexture(const Texture* texturePtr, const RectInt& textureArea)
{
	m_pTexture = texturePtr;
	if (textureArea.width == 0 && textureArea.height == 0)
		m_TextureArea = RectInt{ 0,0, static_cast<int>(m_pTexture->GetWidth()), static_cast<int>(m_pTexture->GetHeight()) };
	else m_TextureArea = textureArea;

}

RectInt AnimatedSprite::DestRect() const
{
	return RectInt{ m_BottomCenter.x - SrcRect().width / 2, m_BottomCenter.y, SrcRect().width , SrcRect().height };
}

void AnimatedSprite::ResetFrames()
{
	m_CurrentCol = 0;
	m_PassedTime = 0.f;
}

RectInt AnimatedSprite::SrcRect() const
{
	RectInt srcRect{};
	srcRect.width = m_TextureArea.width / m_NrOfCols;
	srcRect.height = m_TextureArea.height / m_NrOfRows;
	srcRect.left = m_TextureArea.left + srcRect.width * m_CurrentCol;
	srcRect.bottom = m_TextureArea.bottom + srcRect.height * m_CurrentRow;
	return srcRect;
}