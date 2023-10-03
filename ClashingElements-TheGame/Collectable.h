#pragma once
#include "AnimatedSprite.h"
class Collectable final : public AnimatedSprite
{
public:
	explicit Collectable(const Point2f& BottomCenter, bool randomize = true);
	~Collectable();

	Collectable(const Collectable& other) = delete;
	Collectable(Collectable&& other) noexcept = delete;
	Collectable& operator=(const Collectable& other) = delete;
	Collectable& operator=(Collectable&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

	Circlef GetHitBox() const;

private:
	const static Texture* m_pTexture;
	static int m_InstanceCounter;
	const static int m_Value;

	Circlef m_HitBox;

	const static int m_Amplitude;
	const float m_Period;
	float m_Time;
};

