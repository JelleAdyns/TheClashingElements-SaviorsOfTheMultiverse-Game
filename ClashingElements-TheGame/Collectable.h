#pragma once
#include "AnimatedSprite.h"
class Collectable final : public AnimatedSprite
{
public:
	explicit Collectable(const Point2f& BottomCenter);
	~Collectable() = default;

	Collectable(const Collectable& other) = delete;
	Collectable(Collectable&& other) noexcept = delete;
	Collectable& operator=(const Collectable& other) = delete;
	Collectable& operator=(Collectable&& other) noexcept = delete;

	virtual void Update(float elapsedSec) override;

	Circlef GetHitBox() const;

private:
	const static int m_Value;

	Circlef m_HitBox;
};

