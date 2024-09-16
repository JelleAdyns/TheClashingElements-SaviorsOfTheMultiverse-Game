#ifndef ANIMBACKGROUND_H
#define ANIMBACKGROUND_H

#include "AnimatedSprite.h"

class AnimBackGround final: public AnimatedSprite
{
public:
	explicit AnimBackGround(const tstring& filePath);
	~AnimBackGround() = default;

	AnimBackGround(const AnimBackGround& other) = delete;
	AnimBackGround(AnimBackGround&& other) noexcept = delete;
	AnimBackGround& operator=(const AnimBackGround& other) = delete;
	AnimBackGround& operator=(AnimBackGround&& other) noexcept = delete;
private:
	const static int m_NrOfCols;
	std::unique_ptr<Texture> m_pTexture;
};


#endif // !ANIMBACKGROUND_H
