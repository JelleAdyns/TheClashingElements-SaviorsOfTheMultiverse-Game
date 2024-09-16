#ifndef LEVEL_H
#define LEVEL_H


#include <vector>
#include <memory>
#include "AnimBackGround.h"
#include "BackGround.h"
#include "Collectable.h"
#include "PathGraph.h"
#include "Camera.h"
#include "HUD.h"
#include "Screen.h"
#include "Enemy.h"
#include "Commands.h"
#include "Game.h"


class AnimatedSprite;
class Player;

class Level final : public Screen, public Observer<HUD::Counters>
{
public:
	explicit Level(Game& game, Skin playerSkin);
	virtual ~Level() = default;

	Level(const Level& other) = delete;
	Level(Level&& other) noexcept = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) noexcept = delete;

	virtual void Tick() override;
	virtual void Draw() const override;
	virtual void KeyInput(int virtualKeyCode) override;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void OnSuspend() override{};
	virtual void OnResume() override{};

	virtual void Notify(HUD::Counters counters) override;
	virtual void OnSubjectDestroy() override;

	HUD::Counters GetCounters() const;

private:
	const std::vector<std::pair<tstring, std::pair<tstring, Point2Int>>> m_VecBackGrounds;
	const std::vector<tstring> m_VecMusic;

	uint8_t m_MaxStages;
	uint8_t m_StageNumber;
	int m_LoopNumber;

	bool m_StageCompleted;

	HUD m_Hud;
	Camera m_Camera;

	std::unique_ptr < AnimBackGround > m_pAnimBackGround;
	std::unique_ptr < BackGround > m_pBackGround;

	std::vector< std::unique_ptr < Collectable > > m_pVecCollectables;
	std::vector< std::unique_ptr < AnimatedSprite > > m_pVecSprites;
	std::vector< std::unique_ptr < Enemy > > m_pVecEnemies;

	std::vector< AnimatedSprite* > m_pDrawBuffer;

	std::shared_ptr<Player> m_pPlayer;

	PathGraph m_Graph;

	std::unique_ptr<Subject<int>> m_pPickedUp;

	std::unique_ptr<PushScreenCommand> m_pPushCommand;

	Game& m_GameReference;

	void HitCollectable();
	void LoadStage();
	void Reset();
	void SetUpDrawBuffer();

};
#endif // !LEVEL_H
