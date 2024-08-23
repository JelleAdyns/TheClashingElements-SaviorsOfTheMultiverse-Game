#include "Character.h"

Character::Character(const Point2Int& bottomCenter, int nrCols, int nrFrames, float frameTime, int pixelOffset) :
	AnimatedSprite{ bottomCenter, nrCols, nrFrames, frameTime, false },
	m_PixelOffset{ pixelOffset },

	m_Dir{ Direction::Down },
	m_HitBox{ CircleInt{Point2Int{bottomCenter}, 6} },

	m_Velocity{ },
	m_TargetLocation{},

	m_IsMoving{ false },

	m_DefaultSpeed{}
{
	SetPos(bottomCenter);
}

void Character::Draw() const
{
	ENGINE.PushTransform();
	ENGINE.Translate(0, -m_PixelOffset);
	AnimatedSprite::Draw();
	ENGINE.PopTransform();
}

void Character::Update()
{
	
	if (m_TargetLocation.x != m_BottomCenter.x && m_IsMoving)
	{
		bool decreasing{ m_TargetLocation.x < m_BottomCenter.x };

		if (decreasing) m_Velocity.x = float(-m_DefaultSpeed);
		else m_Velocity.x = float(m_DefaultSpeed);

		UpdatePos(m_Velocity);

		if ((not decreasing and m_BottomCenter.x >= m_TargetLocation.x) or
			(decreasing and m_BottomCenter.x <= m_TargetLocation.x))
		{
			SetPos(Point2Int{ m_TargetLocation.x, m_BottomCenter.y});
			m_Velocity.x = 0;
		}
	}

	if (m_TargetLocation.y != m_BottomCenter.y && m_IsMoving)
	{
		bool decreasing{ m_TargetLocation.y < m_BottomCenter.y };

		if (decreasing) m_Velocity.y = float(-m_DefaultSpeed);
		else m_Velocity.y = float(m_DefaultSpeed);

		UpdatePos(m_Velocity);

		if ((not decreasing and m_BottomCenter.y >= m_TargetLocation.y) or
			(decreasing and m_BottomCenter.y <= m_TargetLocation.y))
		{
			SetPos(Point2Int{ m_BottomCenter.x, m_TargetLocation.y });
			m_Velocity.y = 0;
		}
	}

} 

void Character::SetPos(const Point2Int& newPos)
{
	m_BottomCenter = newPos;
	m_HitBox.center = newPos;
	m_ActualPosX = static_cast<float>(newPos.x);
	m_ActualPosY = static_cast<float>(newPos.y);
	m_TargetLocation = newPos;
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