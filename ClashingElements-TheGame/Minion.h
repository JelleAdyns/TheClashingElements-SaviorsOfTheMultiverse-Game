#pragma once
#include "Enemy.h"
class Minion final : public Enemy
{
public:
	explicit Minion(const Point2f& bottomCenter);
	~Minion();

	Minion(const Minion& other) = delete;
	Minion(Minion&& other) noexcept = delete;
	Minion& operator=(const Minion& other) = delete;
	Minion& operator=(Minion&& other) noexcept = delete;

	//virtual void Draw() const override;
	//virtual void Update(float elapsedSec) override;
private:
	const static Texture* m_pTexture;
	static int m_InstanceCounter;
	static int m_DefaultSpeed;
}; 

