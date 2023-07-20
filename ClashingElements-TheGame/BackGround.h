#pragma once
#include "AnimatedSprite.h"

class BackGround final: public AnimatedSprite
{
public:
	explicit BackGround(const Point2f& bottomCenter, const std::string& filePath);
	~BackGround();

	BackGround(const BackGround& other) = delete;
	BackGround(BackGround&& other) noexcept = delete;
	BackGround& operator=(const BackGround& other) = delete;
	BackGround& operator=(BackGround&& other) noexcept = delete;
private:

	const Texture* m_pTexture;
};

