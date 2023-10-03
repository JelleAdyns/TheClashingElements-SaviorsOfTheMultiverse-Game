#pragma once
#include "AnimatedSprite.h"
#include "PathGraph.h"
#include "GlobalEnumClasses.h"
class Character : public AnimatedSprite
{
public:
	explicit Character(const Point2f& bottomCenter, int nrCols, int nrFrames, float frameTime);
	virtual ~Character() = default;

	Character(const Character& other) = delete;
	Character(Character&& other) noexcept = delete;
	Character& operator=(const Character& other) = delete;
	Character& operator=(Character&& other) noexcept = delete;


	virtual void Update(float elapsedSec) override;
	virtual void Move(const PathGraph& graph, float elapsedSec) = 0;
	virtual void SetPos(const Point2f& newPos);

	Circlef GetHitBox() const;
	bool IsMoving() const;


protected:
	Direction m_Dir;
	Vector2f m_Velocity;

	int m_TargetXLocation;
	int m_TargetYLocation;
	bool m_IsMoving;
	Circlef m_HitBox;

	void UpdatePos(const Vector2f& newVelocity, float elapsedSec);
	void SetDefaultSpeed(int speed);
private:
	Point2f m_Pos;
	int m_DefaultSpeed;
};

