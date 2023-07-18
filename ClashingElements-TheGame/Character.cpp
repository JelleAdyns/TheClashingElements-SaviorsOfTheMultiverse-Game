#include "pch.h"
#include "Character.h"
#include "MyUtils.h"
#include "Tile.h"
#include <Texture.h>
#include <iostream>

Character::Character(const Point2f& bottomCenter, const int tileId) :
	AnimatedSprite{ bottomCenter, 8, 32, 1.f / 20 },
	m_Skin{Skin::Finn},
	m_Dir{Direction::Down},
	m_HitBox{ Circlef{bottomCenter, 6} },

	m_Speed{Tile::Size * 4},

	m_TargetXLocation{int(bottomCenter.x) },
	m_TargetYLocation{int(bottomCenter.y) },

	m_IsMoving{false}
{
	m_pTexture = new Texture{"Wesley.png"} ;
	AnimatedSprite::SetTexture(m_pTexture);
}
Character::~Character()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Character::Update(float elapsedSec)
{

	m_PassedTime += elapsedSec;
	if (m_PassedTime >= m_FrameTime)
	{
		if (m_IsMoving) ++m_CurrentCol %= m_NrOfCols;
		else m_CurrentCol = 0;
		m_PassedTime = 0.f;
	}

	if (m_TargetXLocation != m_BottomCenter.x )
	{
		if (m_TargetXLocation < m_BottomCenter.x) m_Dir = Direction::Left;
		else m_Dir = Direction::Right;
		m_BottomCenter.x += Lerp<float>(m_BottomCenter.x, float(m_TargetXLocation),m_Speed * elapsedSec);
		if (round(m_BottomCenter.x) == m_TargetXLocation)
		{
			m_BottomCenter.x = float(round(m_BottomCenter.x));
			m_IsMoving = false;
		}
	}

	if (m_TargetYLocation != m_BottomCenter.y)
	{
		if (m_TargetYLocation < m_BottomCenter.y) m_Dir = Direction::Down;
		else m_Dir = Direction::Up;
		m_BottomCenter.y += Lerp<float>(m_BottomCenter.y,float(m_TargetYLocation),m_Speed * elapsedSec);
		if (round(m_BottomCenter.y) == m_TargetYLocation)
		{
			m_BottomCenter.y = float(round(m_BottomCenter.y));
			m_IsMoving = false;
		}
	}

	m_HitBox.center = m_BottomCenter;

	m_CurrentRow = int(m_Dir);
}

Circlef Character::GetHitBox() const
{
	return m_HitBox;
}
bool Character::IsMoving() const
{
	return m_IsMoving;
}
void Character::SetIsMoving(bool isMoving)
{
	m_IsMoving = isMoving;
}
void Character::SetTargetLocation(int targetX, int targetY)
{
	if (targetX != 0) m_TargetXLocation = targetX;
	if (targetY != 0) m_TargetYLocation = targetY;
}