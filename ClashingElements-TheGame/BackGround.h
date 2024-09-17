#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Structs.h"
#include "Engine.h"

class AnimBackGround;
class BackGround
{
public:
	explicit BackGround(const tstring& filePath, const Point2Int& bottomLeft, float parallax = 1.f);
	explicit BackGround(const tstring& filePath, float parallax = 1.f);
	~BackGround() = default;

	BackGround(const BackGround& other) = delete;
	BackGround(BackGround&& other) noexcept = delete;
	BackGround& operator=(const BackGround& other) = delete;
	BackGround& operator=(BackGround&& other) noexcept = delete;

	void Draw() const;
	float GetParallaxSpeed() const;

	RectInt DestRect() const;
	
private:

	const Texture& m_rBackGround;
	const float m_ParallaxSpeed;

	const Point2Int m_BottemLeft;

};


#endif // !BACKGROUND_H

