#pragma once
#include <utils.h>
#include "AnimatedSprite.h"
#include "PathGraph.h"
#include "Level.h"
#include "GlobalEnumClasses.h"
class Character final : public AnimatedSprite
{
public:
	explicit Character(const Skin& skin);
	~Character();

	Character(const Character& other) = delete;
	Character(Character&& other) noexcept = delete;
	Character& operator=(const Character& other) = delete;
	Character& operator=(Character&& other) noexcept = delete;


	virtual void Update(float elapsedSec) override;
	void UpdatePos(const Vector2f& newVelocity, float elapsedSec);
	void Move(const PathGraph& graph, float elapsedSec);

	void ResetFrames();

	Circlef GetHitBox() const;
	bool IsMoving() const;
	void SetPos(const Point2f& newPos);
	void Play();

private:
	const static int m_PixelOffset;
	static int m_DefaultSpeed;

	enum class CharacterState
	{
		ChoosingSkin,
		Playing
	};
	CharacterState m_State;

	Direction m_Dir;

	const Texture* m_pTexture;

	Circlef m_HitBox;
	Point2f m_Pos;

	Vector2f m_Velocity;

	int m_TargetXLocation;
	int m_TargetYLocation;

	bool m_IsMoving;
};