#pragma once
class AnimBackGround;
class Texture;

class BackGround
{
public:
	explicit BackGround(const Point2f& bottomLeft, const std::string& filePath, float parallax = 1.f);
	explicit BackGround(const std::string& filePath, float parallax = 1.f);
	~BackGround();

	BackGround(const BackGround& other) = delete;
	BackGround(BackGround&& other) noexcept = delete;
	BackGround& operator=(const BackGround& other) = delete;
	BackGround& operator=(BackGround&& other) noexcept = delete;

	void Draw() const;
	float GetParallaxSpeed() const;

private:

	const Texture* m_pBackGround;
	const float m_ParallaxSpeed;

	Rectf DestRect() const;
	const Point2f m_BottemLeft;

};

