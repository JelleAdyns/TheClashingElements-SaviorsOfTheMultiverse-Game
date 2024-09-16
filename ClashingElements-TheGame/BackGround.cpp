#include "BackGround.h"



BackGround::BackGround(const tstring& filePath, const Point2Int& bottomLeft, float parallax ):
	m_BottemLeft{ bottomLeft },
	m_ParallaxSpeed{parallax},
	m_pBackGround{ std::make_unique<Texture>(filePath )}
{
}
BackGround::BackGround(const tstring& filePath, float parallax) :
	BackGround{filePath, Point2Int{}, parallax}
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