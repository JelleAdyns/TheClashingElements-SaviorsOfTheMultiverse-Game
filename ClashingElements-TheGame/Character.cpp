#include "pch.h"
#include "Character.h"

Character::Character(const Point2f& bottomCenter, int nrCols, int nrFrames, float frameTime) :
	AnimatedSprite{ bottomCenter, nrCols, nrFrames, frameTime, false },

	m_Dir{ Direction::Down },
	m_HitBox{ Circlef{Point2f{bottomCenter}, 6} },

	m_Velocity{ Vector2f{} },
	m_TargetXLocation{},
	m_TargetYLocation{},

	m_IsMoving{ false },

	m_Pos{},
	m_DefaultSpeed{}
{
	SetPos(bottomCenter);
}

void Character::Update(float elapsedSec)
{
	if (m_TargetXLocation != m_BottomCenter.x && m_IsMoving)
	{
		if (m_TargetXLocation < m_BottomCenter.x) m_Velocity.x = float(-m_DefaultSpeed);
		else m_Velocity.x = float(m_DefaultSpeed);

		UpdatePos(m_Velocity, elapsedSec);

		if (m_BottomCenter.x == m_TargetXLocation) m_IsMoving = false;
	}
	else m_Velocity.x = 0;

	if (m_TargetYLocation != m_BottomCenter.y && m_IsMoving)
	{
		if (m_TargetYLocation < m_BottomCenter.y) m_Velocity.y = float(-m_DefaultSpeed);
		else m_Velocity.y = float(m_DefaultSpeed);

		UpdatePos(m_Velocity, elapsedSec);

		if (m_BottomCenter.y == m_TargetYLocation) m_IsMoving = false;
	}
	else m_Velocity.y = 0;
}

void Character::SetPos(const Point2f& newPos)
{
	//Point2f pos{ newPos.x, newPos.y}
	m_BottomCenter = newPos;
	m_HitBox.center = newPos;
	m_Pos = newPos;
	m_TargetXLocation = int(newPos.x);
	m_TargetYLocation = int(newPos.y);
	m_IsMoving = false;
}

void Character::UpdatePos(const Vector2f& newVeloctiy, float elapsedSec)
{
	m_Pos.x += newVeloctiy.x * elapsedSec;
	m_BottomCenter.x = round(m_Pos.x);
	m_Pos.y += newVeloctiy.y * elapsedSec;
	m_BottomCenter.y = round(m_Pos.y);
	m_HitBox.center = m_BottomCenter;
}

void Character::SetDefaultSpeed(int speed)
{
	m_DefaultSpeed = speed;
}

Circlef Character::GetHitBox()const
{
	return m_HitBox;
}

bool Character::IsMoving() const
{
	return m_IsMoving;
}