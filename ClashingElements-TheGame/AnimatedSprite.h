#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Engine.h"
#include <iostream>
class AnimatedSprite
{
public:

	struct SpriteInfo
	{
		const int nrOfCols{1};
		const int nrOfFrames{1};
		const int nrOfRows{nrOfFrames / nrOfCols};
		const float	frameTime{0.5f};
	};


	explicit AnimatedSprite(const Point2Int& bottomCenter, const tstring& textureFile, const SpriteInfo& spriteInfo, bool updateRows = true);
	virtual ~AnimatedSprite() = default;

	AnimatedSprite(const AnimatedSprite& other) = delete;
	AnimatedSprite(AnimatedSprite&& other) noexcept = delete;
	AnimatedSprite& operator=(const AnimatedSprite& other) = delete;
	AnimatedSprite& operator=(AnimatedSprite&& other) noexcept = delete;

	virtual void Draw() const;
	virtual void Update();

	RectInt DestRect() const;
	void ResetFrames();

protected:

	const Texture& GetTexture() const;

	Point2Int m_BottomCenter;

	int	m_CurrentCol;
	int	m_CurrentRow;

	SpriteInfo m_SpriteInfo;

	float m_PassedTime;


private:
	RectInt SrcRect() const;
	const Texture& m_rTexture;
	const bool m_UpdateRows;
	RectInt m_TextureArea;

};

#endif // !ANIMATEDSPRITE_H