#pragma once
#include <utils.h>
#include "AnimatedSprite.h"
class Character final: public AnimatedSprite
{
public:
	explicit Character(const Point2f& BottomCenter, const int tileId);
	~Character();

	Character(const Character& other) = delete;
	Character(Character&& other) noexcept = delete;
	Character& operator=(const Character& other) = delete;
	Character& operator=(Character&& other) noexcept = delete;

	enum class Skin
	{
		Finn,
		Wesley
	};

	virtual void Update(float elapsedSec) override;

	Circlef GetHitBox() const;
	bool IsMoving() const;

	void SetIsMoving(bool isMoving);
	void SetTargetLocation(int targetX, int targetY) ;

private:

	const Skin m_Skin;

	enum class Direction
	{
		Down,
		Left,
		Up,
		Right
	};
	Direction m_Dir;

	const Texture* m_pTexture;

	Circlef m_HitBox;

	int m_Speed;

	int m_TargetXLocation;
	int m_TargetYLocation;

	bool m_IsMoving;
};

