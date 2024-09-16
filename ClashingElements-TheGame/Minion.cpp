#include "Minion.h"

std::unique_ptr<Texture> Minion::m_pTexture{ nullptr };
int Minion::m_InstanceCounter{0};
int Minion::m_DefaultSpeed{Tile::Size * 3};

Minion::Minion(const Point2Int& bottomCenter) :
	Enemy{ bottomCenter, 3, 12, 1.f / 8 }
{
	Character::SetDefaultSpeed(m_DefaultSpeed);
	++m_InstanceCounter;

	if (m_pTexture == nullptr)
	{
		m_pTexture = std::make_unique<Texture>( _T("Minion.png") );
	}
	AnimatedSprite::SetTexture(m_pTexture.get());
}

Minion::~Minion()
{
	--m_InstanceCounter;
	if (m_InstanceCounter == 0)
	{
		m_pTexture = nullptr;
	}
}