#include "pch.h"
#include "Collectable.h"
#include <Texture.h>

const Texture* Collectable::m_pTexture{nullptr};
int Collectable::m_InstanceCouner{0};
const int Collectable::m_Value{100};
const int Collectable::m_Amplitude{ 3 };

Collectable::Collectable(const Point2f& BottomCenter):
	AnimatedSprite{ BottomCenter, 3, 9, 1.f / 20 },
	m_HitBox{Circlef{BottomCenter, 3}},
	m_Period{float(2*M_PI) *  (0.05f * (rand() % 8 + 5))},
	m_YPos{int(BottomCenter.y + float(m_Amplitude)/2)},
	m_Time{0.f}
{
	++m_InstanceCouner;
	//Texture* tempTexture{ new Texture{"Collectable.png"} };
	if (m_pTexture == nullptr)
	{
		m_pTexture = new Texture{ "Collectable.png" };
	}
	AnimatedSprite::SetTexture(m_pTexture);
	m_CurrentRow = rand() % 3;
}

Collectable::~Collectable()
{
	--m_InstanceCouner;
	if (m_InstanceCouner == 0)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void Collectable::Update(float elapsedSec)
{
	m_PassedTime += elapsedSec;
	if (m_PassedTime >= m_FrameTime)
	{
		++m_CurrentCol %= m_NrOfCols;
		m_PassedTime = 0.f;
	}
	m_Time += elapsedSec;
	m_BottomCenter.y = int(m_Amplitude * sinf(m_Period * m_Time) + m_YPos);
}

Circlef Collectable::GetHitBox() const
{
	return m_HitBox;
}