#include "BackGround.h"



BackGround::BackGround(const tstring& filePath, const Point2Int& bottomLeft, float parallax ):
	m_BottemLeft{ bottomLeft },
	m_ParallaxSpeed{parallax},
	m_rBackGround{ ResourceManager::GetInstance().GetTexture(filePath) }
{
}
BackGround::BackGround(const tstring& filePath, float parallax) :
	BackGround{filePath, Point2Int{}, parallax}
{
}

void BackGround::Draw() const
{
	ENGINE.DrawTexture(m_rBackGround, DestRect());
}
float BackGround::GetParallaxSpeed() const
{
	return m_ParallaxSpeed;
}

RectInt BackGround::DestRect() const
{
	return RectInt{ m_BottemLeft.x , m_BottemLeft.y, int(m_rBackGround.GetWidth()), int(m_rBackGround.GetHeight()) };
}