#ifndef MINION_H
#define MINION_H

#include "Enemy.h"
class Minion final : public Enemy
{
public:
	explicit Minion(const Point2Int& bottomCenter);
	virtual ~Minion() = default;

	Minion(const Minion& other) = delete;
	Minion(Minion&& other) noexcept = delete;
	Minion& operator=(const Minion& other) = delete;
	Minion& operator=(Minion&& other) noexcept = delete;

	//virtual void Draw() const override;
	//virtual void Update(float elapsedSec) override;
private:
	static int m_DefaultSpeed;
}; 

#endif // !MINION_H
