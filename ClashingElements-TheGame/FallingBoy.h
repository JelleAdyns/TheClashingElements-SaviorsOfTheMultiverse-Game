#ifndef FALLINGBOY_H
#define FALLINGBOY_H

#include "AnimatedSprite.h"
#include "Engine.h"
#include <vector>
class FallingBoy final : public AnimatedSprite
{
public:
	explicit FallingBoy(const Point2Int& bottomCenter);
	virtual ~FallingBoy() = default;

	FallingBoy(const FallingBoy& other) = delete;
	FallingBoy(FallingBoy&& other) noexcept = delete;
	FallingBoy& operator=(const FallingBoy& other) = delete;
	FallingBoy& operator=(FallingBoy&& other) noexcept = delete;

	void UpdatePos();
	virtual void Draw() const override;

	//void Reset(float yDist);

	const static int m_NrOfBoys;
private:
	const static int m_FallingSpeed;

	std::vector<Vector2f> m_VecPositions;
};

#endif // !FALLINGBOY_H