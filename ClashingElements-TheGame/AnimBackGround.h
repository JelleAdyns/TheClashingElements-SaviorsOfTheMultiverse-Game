#pragma once
#include "AnimatedSprite.h"

class AnimBackGround final: public AnimatedSprite
{
public:
	explicit AnimBackGround(const Point2f& bottomCenter, const std::string& filePath);
	~AnimBackGround();

	AnimBackGround(const AnimBackGround& other) = delete;
	AnimBackGround(AnimBackGround&& other) noexcept = delete;
	AnimBackGround& operator=(const AnimBackGround& other) = delete;
	AnimBackGround& operator=(AnimBackGround&& other) noexcept = delete;

	//virtual void Update(float elapsedSec) override;
private:

	const Texture* m_pTexture;
};

