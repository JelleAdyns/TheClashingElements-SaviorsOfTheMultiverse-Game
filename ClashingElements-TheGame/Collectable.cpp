#include "pch.h"
#include "Collectable.h"
#include "Texture.h"

const int Collectable::m_Value{100};

Collectable::Collectable(const Point2f& BottomCenter):
	AnimatedSprite{BottomCenter, 8, 32, 1.f /20},
	m_HitBox{Circlef{BottomCenter, 3}}
{
	Texture* tempTexture{ new Texture{"Wesley.png"} };
	AnimatedSprite::SetTexture(tempTexture);
}

void Collectable::Update(float elapsedSec)
{
	m_PassedTime += elapsedSec;
	if (m_PassedTime >= m_FrameTime)
	{
		++m_CurrentCol %= m_NrOfCols;
		m_PassedTime = 0.f;
	}
}

Circlef Collectable::GetHitBox() const
{
	return m_HitBox;
}