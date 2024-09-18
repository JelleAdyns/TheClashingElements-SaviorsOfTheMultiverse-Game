#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
class HUD;
class Player final: public Character
{
public:
	explicit Player(Skin skin, HUD* hudObserver = nullptr);
	virtual ~Player() = default;

	Player(const Player& other) = delete;
	Player(Player&& other) noexcept = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) noexcept = delete;

	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Move(const PathGraph& graph) override;
	//virtual void InteractWithMobilityItem(const MobilityItem& mobilityItem) override;

	void Play();
	void TakeDamage();
	void Respawn(const Point2Int& pos);
	static int GetDefaultSpeed() { return m_DefaultSpeed; }
private:

	static int m_DefaultSpeed;
	enum class PlayerState
	{
		ChoosingSkin,
		Playing
	};
	PlayerState m_State;


	std::unique_ptr<Subject<Player*>> m_pTookDamage;
	void UpdateInvincibility();

	bool m_IsInvincible{ false };
	bool m_NeedsToDraw{ true };
	float m_MaxInvincibleTime{ 3.f };
	float m_InvincibleTimer{ 0.f };
	float m_DrawTimeSteps{0.1f};
	float m_DrawTimer{ 0.f };
};


#endif // !PLAYER_H