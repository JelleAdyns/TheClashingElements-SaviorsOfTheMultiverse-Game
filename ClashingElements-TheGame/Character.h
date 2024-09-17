#ifndef CHARACTER_H
#define CHARACTER_H

#include "AnimatedSprite.h"
#include "PathGraph.h"
#include "GlobalEnumClasses.h"
class Character : public AnimatedSprite
{
public:
	explicit Character(const Point2Int& bottomCenter, const tstring& textureFile, SpriteInfo spriteInfo, int pixelOffset = 0);
	virtual ~Character() = default;

	Character(const Character& other) = delete;
	Character(Character&& other) noexcept = delete;
	Character& operator=(const Character& other) = delete;
	Character& operator=(Character&& other) noexcept = delete;


	virtual void Draw() const override;
	virtual void Update() override;
	virtual void Move(const PathGraph& graph) = 0;
	void SetPos(const Point2Int& newPos);

	CircleInt GetHitBox() const;
	bool IsMoving() const;


protected:
	Direction m_Dir;
	Vector2f m_Velocity;

	Point2Int m_TargetLocation;
	bool m_IsMoving;

	void UpdatePos(const Vector2f& newVelocity);
	void SetDefaultSpeed(int speed);
private:
	const int m_PixelOffset;
	float m_ActualPosX;
	float m_ActualPosY;
	int m_DefaultSpeed;
	CircleInt m_HitBox;
};

#endif // !CHARACTER_H