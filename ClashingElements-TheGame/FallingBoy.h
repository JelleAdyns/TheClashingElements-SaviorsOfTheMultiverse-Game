#ifndef FALLINGBOY_H
#define FALLINGBOY_H

#include "AnimatedSprite.h"
#include "Engine.h"
#include <vector>
class FallingBoy final : public AnimatedSprite
{
public:
	explicit FallingBoy(const Point2Int& bottomCenter,const RectInt& window);
	~FallingBoy();

	FallingBoy(const FallingBoy& other) = delete;
	FallingBoy(FallingBoy&& other) noexcept = delete;
	FallingBoy& operator=(const FallingBoy& other) = delete;
	FallingBoy& operator=(FallingBoy&& other) noexcept = delete;

	void UpdatePos();
	virtual void Draw() const override;

	//void Reset(float yDist);

	const static int m_NrOfBoys;
private:

	static std::unique_ptr<Texture> m_pTexture;
	static int m_InstanceCounter;
	const static int m_FallingSpeed;

	const RectInt m_Window;

	std::vector<Point2Int> m_VecPositions;
};

#endif // !FALLINGBOY_H