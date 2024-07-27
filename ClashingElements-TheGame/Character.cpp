#include "Character.h"

Character::Character(const Point2Int& bottomCenter, int nrCols, int nrFrames, float frameTime) :
	AnimatedSprite{ bottomCenter, nrCols, nrFrames, frameTime, false },

	m_Dir{ Direction::Down },
	m_HitBox{ CircleInt{Point2Int{bottomCenter}, 6} },

	m_Velocity{ },
	m_TargetXLocation{},
	m_TargetYLocation{},

	m_IsMoving{ false },

	m_DefaultSpeed{}
{
	SetPos(bottomCenter);
}

void Character::Update()
{
	if (m_TargetXLocation != m_BottomCenter.x && m_IsMoving)
	{
		if (m_TargetXLocation < m_BottomCenter.x) m_Velocity.x = float(-m_DefaultSpeed);
		else m_Velocity.x = float(m_DefaultSpeed);

		UpdatePos(m_Velocity);

		if (m_BottomCenter.x == m_TargetXLocation) m_IsMoving = false;
	}
	else m_Velocity.x = 0;

	if (m_TargetYLocation != m_BottomCenter.y && m_IsMoving)
	{
		if (m_TargetYLocation < m_BottomCenter.y) m_Velocity.y = float(-m_DefaultSpeed);
		else m_Velocity.y = float(m_DefaultSpeed);

		UpdatePos(m_Velocity);

		if (m_BottomCenter.y == m_TargetYLocation) m_IsMoving = false;
	}
	else m_Velocity.y = 0;
}

void Character::SetPos(const Point2Int& newPos)
{
	//Point2Int pos{ newPos.x, newPos.y}
	m_BottomCenter = newPos;
	m_HitBox.center = newPos;
	m_ActualPosX = static_cast<float>(newPos.x);
	m_ActualPosY = static_cast<float>(newPos.y);
	m_TargetXLocation = int(newPos.x);
	m_TargetYLocation = int(newPos.y);
	m_IsMoving = false;
}

void Character::UpdatePos(const Vector2f& newVeloctiy)
{
	m_ActualPosX += newVeloctiy.x * ENGINE.GetDeltaTime();
	m_BottomCenter.x = static_cast<int>(round(m_ActualPosX));
	m_ActualPosY += newVeloctiy.y * ENGINE.GetDeltaTime();
	m_BottomCenter.y = static_cast<int>(round(m_ActualPosY));
	m_HitBox.center = m_BottomCenter;
}

void Character::SetDefaultSpeed(int speed)
{
	m_DefaultSpeed = speed;
}

CircleInt Character::GetHitBox()const
{
	return m_HitBox;
}

bool Character::IsMoving() const
{
	return m_IsMoving;
}