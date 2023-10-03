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
	m_LevelCenter.x = levelBoundaries.left + levelBoundaries.width / 2;
	m_LevelCenter.y = levelBoundaries.bottom + levelBoundaries.height / 2;
}
void Camera::SetWidthHeight(float width, float height)
{
	m_Width = width;
	m_Height = height;
}
void Camera::Transform(float parallax) const
{
	Vector2f translation{ (1 - parallax) * (m_CurrCamBottomLeft.x + m_Width / 2 - m_LevelCenter.x),
						  (1 - parallax) * (m_CurrCamBottomLeft.y + m_Height / 2 - m_LevelCenter.y) };
	glTranslatef(-float(round((m_CurrCamBottomLeft.x - translation.x ))), -float(round((m_CurrCamBottomLeft.y - translation.y))) , 0);
}
void Camera::Update(const Rectf& target)
{
	m_CurrCamBottomLeft.x = target.left + target.width / 2 - m_Width / 2;
	m_CurrCamBottomLeft.y = target.bottom + target.height / 2 - m_Height / 2;
	Clamp(m_CurrCamBottomLeft);
}

Point2f Camera::Track(const Rectf& target) const
{
	return Point2f{ target.left + target.width / 2, target.bottom + target.height / 2 };
}
void Camera::Clamp(Point2f& bottomLeftPos) const
{
	bottomLeftPos.x = std::max(bottomLeftPos.x , m_LevelBoundaries.left);
	bottomLeftPos.y = std::max(bottomLeftPos.y , m_LevelBoundaries.bottom);
	bottomLeftPos.x = std::min(bottomLeftPos.x , m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width);
	bottomLeftPos.y = std::min(bottomLeftPos.y , m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height);
}