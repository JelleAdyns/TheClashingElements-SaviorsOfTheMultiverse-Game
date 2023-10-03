#pragma once
#include <Texture.h>
#include <utils.h>
#include <iostream>
class AnimatedSprite
{
public:
	explicit AnimatedSprite(const Point2f& bottomCenter, int nrCols, int nrFrames, float frameTime, bool updateRows = true);
	virtual ~AnimatedSprite();

	AnimatedSprite(const AnimatedSprite& other) = delete;
	AnimatedSprite(AnimatedSprite&& other) noexcept = delete;
	AnimatedSprite& operator=(const AnimatedSprite& other) = delete;
	AnimatedSprite& operator=(AnimatedSprite&& other) noexcept = delete;

	virtual void Draw() const;
	virtual void Update(float elapsedSec);

	Rectf DestRect() const;
protected:
	void SetTexture(const Texture* pTexture, const Rectf& textureArea = Rectf{});

	Point2f m_BottomCenter;

	int	m_CurrentCol;
	int	m_CurrentRow;

	const int m_NrOfCols;
	const int m_NrOfFrames;
	const int m_NrOfRows;
	const float	m_FrameTime;

	float m_PassedTime;


private:
	Rectf SrcRect() const;
	const Texture* m_pTexture;
	const bool m_UpdateRows;
	Rectf m_TextureArea;

};

