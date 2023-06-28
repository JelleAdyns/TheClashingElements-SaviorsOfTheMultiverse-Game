#include "pch.h"
#include "Character.h"
#include "Texture.h"


Character::Character(const Point2f& center) :
	AnimatedSprite{ center, 8, 32, 1.f / 20 }
{
	Texture* characterTexture{ new Texture{"Wesley.png"} };
	AnimatedSprite::SetTexture(characterTexture);
}

void Character::Update(float elapsedSec)
{
	m_PassedTime += elapsedSec;
	if (m_PassedTime >= m_FrameTime)
	{
		//if (m_CurrentCol == m_NrOfCols - 1) ++m_CurrentRow %= m_NrOfRows;
		++m_CurrentCol %= m_NrOfCols;
		m_PassedTime = 0.f;
	}
}
