#pragma once

#include "Character.h"
class Player final: public Character
{
public:
	explicit Player(const Skin& skin);
	~Player();

	Player(const Player& other) = delete;
	Player(Player&& other) noexcept = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) noexcept = delete;

	virtual void Update(float elapsedSec) override;
	virtual void Move(const PathGraph& graph, float elapsedSec) override;
	virtual void SetPos(const Point2f& newPos) override;
	//virtual void InteractWithMobilityItem(const MobilityItem& mobilityItem) override;

	void ResetFrames();
	void Play();

	static int m_DefaultSpeed;
private:
	const static int m_PixelOffset;
	enum class PlayerState
	{
		ChoosingSkin,
		Playing
	};
	PlayerState m_State;
	const Texture* m_pTexture;
};

