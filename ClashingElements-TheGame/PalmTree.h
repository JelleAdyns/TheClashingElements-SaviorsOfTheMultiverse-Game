#pragma once
#include "AnimatedSprite.h"
class PalmTree final: public AnimatedSprite
{
public:
	explicit PalmTree(const Point2f& bottomCenter);
	~PalmTree();

	PalmTree(const PalmTree& other) = delete;
	PalmTree(PalmTree&& other) noexcept = delete;
	PalmTree& operator=(const PalmTree& other) = delete;
	PalmTree& operator=(PalmTree&& other) noexcept = delete;

private:

	const static Texture* m_pTexture;
	static int m_InstanceCounter;
};

