#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include "Screen.h"
#include "Commands.h"
#include "Game.h"

class PauseScreen final : public Screen
{
public:
	explicit PauseScreen(Game& game);
	~PauseScreen() = default;

	PauseScreen(const PauseScreen& other) = delete;
	PauseScreen(PauseScreen&& other) noexcept = delete;
	PauseScreen& operator=(const PauseScreen& other) = delete;
	PauseScreen& operator=(PauseScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Tick() override;
	virtual void KeyInput(int virtualKeyCode) override;

	virtual void OnEnter() override {};
	virtual void OnExit() override {};
	virtual void OnSuspend() override {};
	virtual void OnResume() override {};
private:

	std::unique_ptr<PopScreenCommand> m_pPopScreen;
};

#endif // !PAUSESCREEN_H