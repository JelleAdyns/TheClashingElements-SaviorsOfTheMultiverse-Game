#include "pch.h"
#include "Camera.h"
#include <utils.h>


Camera::Camera(float width, float height):
	m_Width{width},
	m_Height{height},
	m_LevelBoundaries{}
{

}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}
void Camera::Transform(const Rectf& target) const
{
	utils::SetColor(Color4f{ 0.f,0.f,1.f,1.f });
	Point2f cameraLeftBottom{ Track(target) };
	Clamp(cameraLeftBottom);
	utils::DrawRect(Rectf{ cameraLeftBottom.x, cameraLeftBottom.y, m_Width, m_Height });
	glTranslatef(-cameraLeftBottom.x, -cameraLeftBottom.y, 0);
}

Point2f Camera::Track(const Rectf& target) const
{
	return Point2f{ target.left + target.width / 2 - m_Width / 2, target.bottom + target.height / 2 - m_Height / 2 };
}
void Camera::Clamp(Point2f& bottomLeftPos) const
{
	bottomLeftPos.x = std::max(bottomLeftPos.x, m_LevelBoundaries.left);
	bottomLeftPos.y = std::max(bottomLeftPos.y, m_LevelBoundaries.bottom);
	bottomLeftPos.x = std::min(bottomLeftPos.x, m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width);
	bottomLeftPos.y = std::min(bottomLeftPos.y, m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height);
}