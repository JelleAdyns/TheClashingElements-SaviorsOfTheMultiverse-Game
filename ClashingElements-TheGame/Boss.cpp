#include "Boss.h"

std::unique_ptr<Texture> Boss::m_pTexture{ nullptr };
int Boss::m_InstanceCounter{ 0 };
int Boss::m_DefaultSpeed{ 0 };

Boss::Boss(const Point2Int& bottomCenter, int speed):
	Enemy{bottomCenter, 3, 3, 1.f / 8 }
{
	m_DefaultSpeed = speed;

	Character::SetDefaultSpeed(m_DefaultSpeed);

	++m_InstanceCounter;

	if (m_pTexture == nullptr)
	{
		m_pTexture = std::make_unique<Texture>( L"Boss.png" );
	}
	AnimatedSprite::SetTexture(m_pTexture.get());
}

Boss::~Boss()
{
	--m_InstanceCounter;
	if (m_InstanceCounter == 0)
	{
		m_pTexture = nullptr;
	}
}