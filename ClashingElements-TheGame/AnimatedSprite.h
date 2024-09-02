#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Engine.h"
#include <iostream>
class AnimatedSprite
{
public:
	explicit AnimatedSprite(const Point2Int& bottomCenter, int nrCols, int nrFrames, float frameTime, bool updateRows = true);
	virtual ~AnimatedSprite();

	AnimatedSprite(const AnimatedSprite& other) = delete;
	AnimatedSprite(AnimatedSprite&& other) noexcept = delete;
	AnimatedSprite& operator=(const AnimatedSprite& other) = delete;
	AnimatedSprite& operator=(AnimatedSprite&& other) noexcept = delete;

	virtual void Draw() const;
	virtual void Update();

	RectInt DestRect() const;
	void ResetFrames();
protected:
	void SetTexture(const Texture* pTexture, const RectInt& textureArea = RectInt{});

	Point2Int m_BottomCenter;

	int	m_CurrentCol;
	int	m_CurrentRow;

	const int m_NrOfCols;
	const int m_NrOfFrames;
	const int m_NrOfRows;
	const float	m_FrameTime;

	float m_PassedTime;


private:
	RectInt SrcRect() const;
	const Texture* m_pTexture;
	const bool m_UpdateRows;
	RectInt m_TextureArea;

};

#endif // !ANIMATEDSPRITE_H