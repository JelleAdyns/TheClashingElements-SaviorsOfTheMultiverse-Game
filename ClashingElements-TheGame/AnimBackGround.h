#pragma once
#include "AnimatedSprite.h"

class AnimBackGround final: public AnimatedSprite
{
public:
	explicit AnimBackGround(const std::string& filePath);
	~AnimBackGround();

	AnimBackGround(const AnimBackGround& other) = delete;
	AnimBackGround(AnimBackGround&& other) noexcept = delete;
	AnimBackGround& operator=(const AnimBackGround& other) = delete;
	AnimBackGround& operator=(AnimBackGround&& other) noexcept = delete;
private:
	const static int m_NrOfCols;
	const Texture* m_pTexture;
};

