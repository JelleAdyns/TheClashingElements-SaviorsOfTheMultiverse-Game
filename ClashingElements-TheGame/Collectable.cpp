#include "Collectable.h"
#include <numbers>

const int Collectable::m_Amplitude{ 3 };

Collectable::Collectable(const Point2Int& BottomCenter, bool randomize):
	AnimatedSprite{ BottomCenter, _T("Collectable.png"), SpriteInfo{.nrOfCols{ 3},.nrOfFrames{ 9}, .frameTime{ 1.f / 20}}, false },
	m_HitBox{CircleInt{BottomCenter, 3}},
	m_Period{float(2*std::numbers::pi) *  (0.05f * (rand() % 8 + 5))},
	m_Time{0.f}
{
	if (randomize) m_CurrentRow = rand() % 3;
}

void Collectable::Draw() const
{
	ENGINE.PushTransform();
	ENGINE.Translate(0, int(round(m_Amplitude * sinf(m_Period * m_Time))) + m_Amplitude);
	AnimatedSprite::Draw();
	ENGINE.PopTransform();
}

void Collectable::Update()
{
	AnimatedSprite::Update();
	m_Time += ENGINE.GetDeltaTime();
	if (m_Time > 10.f) m_Time -= 10.f;
}

CircleInt Collectable::GetHitBox() const
{
	return m_HitBox;
}