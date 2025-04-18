#include "Camera.h"
#include <algorithm>


Camera::Camera(int width, int height):
	m_Width{width},
	m_Height{height},
	m_LevelBoundaries{},
	m_CurrCamBottomLeft{},
	m_LevelCenter{}
{

}

void Camera::SetLevelBoundaries(const RectInt& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
	m_LevelCenter.x = levelBoundaries.left + levelBoundaries.width / 2;
	m_LevelCenter.y = levelBoundaries.bottom + levelBoundaries.height / 2;
}
void Camera::SetWidthHeight(int width, int height)
{
	m_Width = width;
	m_Height = height;
}
void Camera::Transform(float parallax) const
{
	Vector2f translation{ (1 - parallax) * (m_CurrCamBottomLeft.x + m_Width / 2 - m_LevelCenter.x),
						  (1 - parallax) * (m_CurrCamBottomLeft.y + m_Height / 2 - m_LevelCenter.y) };
	ENGINE.Translate(-int(round(m_CurrCamBottomLeft.x - translation.x)), -int(round(m_CurrCamBottomLeft.y - translation.y)));
}
void Camera::Update(const RectInt& target)
{
	m_CurrCamBottomLeft.x = target.left + target.width / 2 - m_Width / 2;
	m_CurrCamBottomLeft.y = target.bottom/* + target.height / 2*/ - m_Height / 2;
	Clamp(m_CurrCamBottomLeft);
}

void Camera::Clamp(Point2Int& bottomLeftPos) const
{
	bottomLeftPos.x = std::max<int>(bottomLeftPos.x , m_LevelBoundaries.left);
	bottomLeftPos.y = std::max<int>(bottomLeftPos.y , m_LevelBoundaries.bottom);
	bottomLeftPos.x = std::min<int>(bottomLeftPos.x , m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width);
	bottomLeftPos.y = std::min<int>(bottomLeftPos.y , m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height);
}