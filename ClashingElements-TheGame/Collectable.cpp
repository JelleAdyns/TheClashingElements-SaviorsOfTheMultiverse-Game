#include "pch.h"
#include "Collectable.h"

const Texture* Collectable::m_pTexture{nullptr};
int Collectable::m_InstanceCounter{0};
const int Collectable::m_Value{100};
const int Collectable::m_Amplitude{ 3 };

Collectable::Collectable(const Point2f& BottomCenter):
	AnimatedSprite{ BottomCenter, 3, 9, 1.f / 20 },
	m_HitBox{Circlef{BottomCenter, 3}},
	m_Period{float(2*M_PI) *  (0.05f * (rand() % 8 + 5))},
	m_Time{0.f}
{
	++m_InstanceCounter;
	
	if (m_pTexture == nullptr)
	{
		m_pTexture = new Texture{ "Collectable.png" };
	}
	AnimatedSprite::SetTexture(m_pTexture);
	m_CurrentRow = rand() % 3;
}

Collectable::~Collectable()
{
	--m_InstanceCounter;
	if (m_InstanceCounter == 0)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}
void Collectable::Draw() const
{
	glPushMatrix();
	glTranslatef(0, float(round(m_Amplitude * sinf(m_Period * m_Time))) + m_Amplitude, 0);
	AnimatedSprite::Draw();
	glPopMatrix();
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
}

Circlef Collectable::GetHitBox() const
{
	return m_HitBox;
}