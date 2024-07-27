#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
class Player final: public Character
{
public:
	explicit Player(const Skin& skin);
	~Player() = default;

	Player(const Player& other) = delete;
	Player(Player&& other) noexcept = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) noexcept = delete;

	virtual void Update() override;
	virtual void Move(const PathGraph& graph) override;
	virtual void SetPos(const Point2Int& newPos) override;
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
	std::unique_ptr<Texture> m_pTexture;
};


#endif // !PLAYER_H