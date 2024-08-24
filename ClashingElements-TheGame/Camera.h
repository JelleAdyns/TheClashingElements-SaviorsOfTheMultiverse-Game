#ifndef CAMERA_H
#define CAMERA_H

#include "Engine.h"

class Camera
{
public:
	explicit Camera(int width, int height);
	~Camera() = default;

	Camera(const Camera& other) = delete;
	Camera(Camera&& other) noexcept = delete;
	Camera& operator=(const Camera& other) = delete;
	Camera& operator=(Camera&& other) noexcept = delete;

	void SetLevelBoundaries(const RectInt& levelBoundaries);
	void SetWidthHeight(int width, int height);
	void Transform(float parallax = 1.f) const;
	void Update(const RectInt& target);
private:
	int m_Width;
	int m_Height;
	RectInt m_LevelBoundaries;
	Point2Int m_LevelCenter;
	Point2Int m_CurrCamBottomLeft;

	Point2Int Track(const RectInt& target) const;
	void Clamp(Point2Int& bottomLeftPos) const;
};

#endif // !CAMERA_H