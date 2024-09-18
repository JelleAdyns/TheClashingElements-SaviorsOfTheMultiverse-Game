#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "Screen.h"
#include "Commands.h"
#include "Game.h"
#include "HUD.h"
#include "Button.h"

class GameOverScreen final : public Screen
{
public:
	explicit GameOverScreen(Game& game);
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
	static constexpr int m_Margin = 20;
	static constexpr int m_TextMargin = 5;
	const int m_AreaHeight = ENGINE.GetWindowRect().height - 100;
	const RectInt m_DestRect{ m_Margin, (ENGINE.GetWindowRect().height - m_AreaHeight) / 2, ENGINE.GetWindowRect().width - m_Margin * 2, m_AreaHeight };
	
	int m_SelectedButtonIndex;
	std::vector<std::unique_ptr<Button>> m_pVecButtons;
	std::vector<tstring> m_VecScoreDisplays{};

	int m_TextIndex{-1};
	bool m_ReadyToContinue{false};
};

#endif // !GAMEOVERSCREEN_H