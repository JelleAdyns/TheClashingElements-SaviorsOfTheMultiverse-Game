#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "Screen.h"
#include "Commands.h"
#include "Game.h"
#include "HUD.h"

class GameOverScreen final : public Screen
{
public:
	explicit GameOverScreen(Game& game, HUD::Counters counters);
	virtual ~GameOverScreen() = default;

	GameOverScreen(const GameOverScreen& other) = delete;
	GameOverScreen(GameOverScreen&& other) noexcept = delete;
	GameOverScreen& operator=(const GameOverScreen& other) = delete;
	GameOverScreen& operator=(GameOverScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Tick() override;
	virtual void KeyInput(int virtualKeyCode) override;

	virtual void OnEnter() override;
	virtual void OnExit() override {};
	virtual void OnSuspend() override {};
	virtual void OnResume() override {};
private:

	std::unique_ptr<LoadScreenCommand> m_pLoadScreen;
	HUD::Counters m_Counters{};
	std::vector<tstring> m_VecScoreDisplays{};
	int m_TextIndex{-1};
};

#endif // !GAMEOVERSCREEN_H