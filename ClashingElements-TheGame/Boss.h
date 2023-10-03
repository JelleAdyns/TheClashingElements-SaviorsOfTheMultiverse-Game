#pragma once
#include "Enemy.h"
class Boss final : public Enemy
{
public:
	explicit Boss(const Point2f& bottomCenter, int speed);
	~Boss();

	Boss(const Boss& other) = delete;
	Boss(Boss&& other) noexcept = delete;
	Boss& operator=(const Boss& other) = delete;
	Boss& operator=(Boss&& other) noexcept = delete;

	//virtual void Draw() const override;
	//virtual void Update(float elapsedSec) override;

private:
	const static Texture* m_pTexture;
	static int m_InstanceCounter;
	static int m_DefaultSpeed;
};

