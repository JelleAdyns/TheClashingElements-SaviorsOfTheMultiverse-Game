#pragma once
#include "AnimatedSprite.h"
#include <vector>
class FallingBoy final : public AnimatedSprite
{
public:
	explicit FallingBoy(const Point2f& bottomCenter,const Rectf& window);
	~FallingBoy();

	FallingBoy(const FallingBoy& other) = delete;
	FallingBoy(FallingBoy&& other) noexcept = delete;
	FallingBoy& operator=(const FallingBoy& other) = delete;
	FallingBoy& operator=(FallingBoy&& other) noexcept = delete;

	void UpdatePos(float elapsedSec);
	virtual void Draw() const override;

	void Reset(float yDist);

	const static int m_NrOfBoys;
private:

	const static Texture* m_pTexture;
	static int m_InstanceCounter;
	const static int m_FallingSpeed;

	const Rectf m_Window;

	std::vector<Point2f> m_VecPositions;
};

