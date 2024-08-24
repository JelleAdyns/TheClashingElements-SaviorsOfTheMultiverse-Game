#include "BackGround.h"



BackGround::BackGround(const Point2Int& bottomLeft, const std::wstring& filePath, float parallax ):
	m_BottemLeft{ bottomLeft },
	m_ParallaxSpeed{parallax},
	m_pBackGround{ std::make_unique<Texture>(filePath )}
{
}
BackGround::BackGround(const std::wstring& filePath, float parallax) :
	BackGround{Point2Int{},filePath, parallax}
{
}

void BackGround::Draw() const
{
	ENGINE.DrawTexture(*m_pBackGround, DestRect());
}
float BackGround::GetParallaxSpeed() const
{
	return m_ParallaxSpeed;
}

RectInt BackGround::DestRect() const
{
	return RectInt{ m_BottemLeft.x , m_BottemLeft.y, int(m_pBackGround->GetWidth()), int(m_pBackGround->GetHeight()) };
}