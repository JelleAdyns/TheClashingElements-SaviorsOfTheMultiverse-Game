#include "pch.h"
#include "Minion.h"

const Texture* Minion::m_pTexture{ nullptr };
int Minion::m_InstanceCounter{0};
int Minion::m_DefaultSpeed{Tile::Size * 3};

Minion::Minion(const Point2f& bottomCenter) :
	Enemy{ bottomCenter, 3, 3, 1.f / 8 }
{
	Character::SetDefaultSpeed(m_DefaultSpeed);
	++m_InstanceCounter;

	if (m_pTexture == nullptr)
	{
		m_pTexture = new Texture{ "Minion.png" };
	}
	AnimatedSprite::SetTexture(m_pTexture);
}

Minion::~Minion()
{
	--m_InstanceCounter;
	if (m_InstanceCounter == 0)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}