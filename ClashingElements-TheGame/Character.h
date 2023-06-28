#pragma once

#include "AnimatedSprite.h"
class Character final: public AnimatedSprite
{
public:
	explicit Character(const Point2f& center);
	~Character() = default;

	Character(const Character& other) = delete;
	Character(Character&& other) noexcept = delete;
	Character& operator=(const Character& other) = delete;
	Character& operator=(Character&& other) noexcept = delete;

	virtual void Update(float elapsedSec) override;
};

