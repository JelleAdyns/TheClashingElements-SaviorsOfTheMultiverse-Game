#include "Collectable.h"
#include <numbers>
std::unique_ptr<Texture> Collectable::m_pTexture{nullptr};
int Collectable::m_InstanceCounter{0};
const int Collectable::m_Value{100};
const int Collectable::m_Amplitude{ 3 };

Collectable::Collectable(const Point2Int& BottomCenter, bool randomize):
	AnimatedSprite{ BottomCenter, 3, 9, 1.f / 20, false },
	m_HitBox{CircleInt{BottomCenter, 3}},
	m_Period{float(2*std::numbers::pi) *  (0.05f * (rand() % 8 + 5))},
	m_Time{0.f}
{
	++m_InstanceCounter;
	
	if (m_pTexture == nullptr)
	{
		m_pTexture = std::make_unique<Texture>( L"Collectable.png" );
	}
	AnimatedSprite::SetTexture(m_pTexture.get());
	if (randomize) m_CurrentRow = rand() % 3;
}

Collectable::~Collectable()
{
	--m_InstanceCounter;
	if (m_InstanceCounter == 0)
	{
		m_pTexture = nullptr;
	}
}
void Collectable::Draw() const
{
	ENGINE.Translate(0, int(round(m_Amplitude * sinf(m_Period * m_Time))) + m_Amplitude);
	AnimatedSprite::Draw();
	ENGINE.EndTransform();
}

void Collectable::Update()
{
	m_PassedTime += ENGINE.GetDeltaTime();
	if (m_PassedTime >= m_FrameTime)
	{
		++m_CurrentCol %= m_NrOfCols;
		m_PassedTime = 0.f;
	}
	m_Time += ENGINE.GetDeltaTime();
}

CircleInt Collectable::GetHitBox() const
{
	return m_HitBox;
}