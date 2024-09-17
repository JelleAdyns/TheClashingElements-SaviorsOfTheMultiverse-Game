#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const Point2Int& bottomCenter, const tstring& textureFile, const SpriteInfo& spriteInfo, bool updateRows):
	m_BottomCenter{bottomCenter},

	m_CurrentCol{0},
	m_CurrentRow{0},
	
	m_SpriteInfo{ spriteInfo },
	
	m_PassedTime{0.f},

	m_rTexture{ResourceManager::GetInstance().GetTexture(textureFile)},
	m_UpdateRows{updateRows}
{
	m_TextureArea.left = 0;
	m_TextureArea.bottom = 0;
	m_TextureArea.width = static_cast<int>(m_rTexture.GetWidth());
	m_TextureArea.height = static_cast<int>(m_rTexture.GetHeight());
}

void AnimatedSprite::Draw() const
{
	ENGINE.DrawTexture(m_rTexture, DestRect(), SrcRect());
}

void AnimatedSprite::Update()
{
	m_PassedTime += ENGINE.GetDeltaTime();
	if (m_PassedTime >= m_SpriteInfo.frameTime)
	{
		if (m_UpdateRows)
		{
			if (m_CurrentCol == m_SpriteInfo.nrOfCols - 1) ++m_CurrentRow %= m_SpriteInfo.nrOfRows;
		}
		++m_CurrentCol %= m_SpriteInfo.nrOfCols;
		m_PassedTime -= m_SpriteInfo.frameTime;
	}
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

const Texture& AnimatedSprite::GetTexture() const
{
	return m_rTexture;
}

RectInt AnimatedSprite::SrcRect() const
{
	RectInt srcRect{};
	srcRect.width = m_TextureArea.width / m_SpriteInfo.nrOfCols;
	srcRect.height = m_TextureArea.height / m_SpriteInfo.nrOfRows;
	srcRect.left = m_TextureArea.left + srcRect.width * m_CurrentCol;
	srcRect.bottom = m_TextureArea.bottom + srcRect.height * m_CurrentRow;
	return srcRect;
}