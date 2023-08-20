#pragma once
class Camera
{
public:
	explicit Camera(float width, float height);
	~Camera() = default;

	Camera(const Camera& other) = delete;
	Camera(Camera&& other) noexcept = delete;
	Camera& operator=(const Camera& other) = delete;
	Camera& operator=(Camera&& other) noexcept = delete;

	void SetLevelBoundaries(const Rectf& levelBoundaries);
	void SetWidthHeight(float width, float height);
	void Transform(float parallax = 1.f) const;
	void Update(const Rectf& target);
private:
	float m_Width;
	float m_Height;
	Rectf m_LevelBoundaries;
	Point2f m_LevelCenter;
	Point2f m_CurrCamBottomLeft;

	Point2f Track(const Rectf& target) const;
	void Clamp(Point2f& bottomLeftPos) const;
};

