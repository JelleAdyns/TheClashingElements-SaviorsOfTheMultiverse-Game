#include "pch.h"
#include "BackGround.h"
#include "Texture.h"

BackGround::BackGround(const Point2f& bottomLeft, const std::string& filePath, float parallax ):
	m_BottemLeft{ bottomLeft },
	m_ParallaxSpeed{parallax}
{
	m_pBackGround = new Texture{ filePath };
}
BackGround::BackGround(const std::string& filePath, float parallax) :
	BackGround{Point2f{},filePath, parallax}
{
}

BackGround::~BackGround()
{
	delete m_pBackGround;
	m_pBackGround = nullptr;
}
void BackGround::Draw() const
{
	m_pBackGround->Draw(DestRect());
}
float BackGround::GetParallaxSpeed() const
{
	return m_ParallaxSpeed;
}

Rectf BackGround::DestRect() const
{
	return Rectf{ m_BottemLeft.x , m_BottemLeft.y, m_pBackGround->GetWidth(), m_pBackGround->GetHeight() };
}