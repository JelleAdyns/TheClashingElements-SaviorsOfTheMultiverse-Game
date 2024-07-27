#ifndef CHARACTER_H
#define CHARACTER_H

#include "AnimatedSprite.h"
#include "PathGraph.h"
#include "GlobalEnumClasses.h"
class Character : public AnimatedSprite
{
public:
	explicit Character(const Point2Int& bottomCenter, int nrCols, int nrFrames, float frameTime);
	virtual ~Character() = default;

	Character(const Character& other) = delete;
	Character(Character&& other) noexcept = delete;
	Character& operator=(const Character& other) = delete;
	Character& operator=(Character&& other) noexcept = delete;


	virtual void Update() override;
	virtual void Move(const PathGraph& graph) = 0;
	virtual void SetPos(const Point2Int& newPos);

	CircleInt GetHitBox() const;
	bool IsMoving() const;


protected:
	Direction m_Dir;
	Vector2f m_Velocity;

	int m_TargetXLocation;
	int m_TargetYLocation;
	bool m_IsMoving;
	CircleInt m_HitBox;

	void UpdatePos(const Vector2f& newVelocity);
	void SetDefaultSpeed(int speed);
private:
	float m_ActualPosX;
	float m_ActualPosY;
	int m_DefaultSpeed;
};

#endif // !CHARACTER_H