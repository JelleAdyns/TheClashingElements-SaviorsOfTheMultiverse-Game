#include "pch.h"
#include "BackGround.h"
#include "Texture.h"

BackGround::BackGround(const Point2f& center, const std::string& filePath) :
	AnimatedSprite{ center, 3, 3, 1.f / 8 }
{
	Texture* characterTexture{ new Texture{filePath} };
	AnimatedSprite::SetTexture(characterTexture);
}