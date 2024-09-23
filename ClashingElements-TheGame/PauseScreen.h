#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include "Screen.h"
#include "Commands.h"
#include "Game.h"

class PauseScreen final : public Screen
{
public:
	explicit PauseScreen(Game& game);
	virtual ~PauseScreen() = default;

	PauseScreen(const PauseScreen& other) = delete;
	PauseScreen(PauseScreen&& other) noexcept = delete;
	PauseScreen& operator=(const PauseScreen& other) = delete;
	PauseScreen& operator=(PauseScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Tick() override;
	virtual void KeyInput(int virtualKeyCode) override;
	virtual void HandleControllerInput() override;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void OnSuspend() override {};
	virtual void OnResume() override {};
private:

	std::unique_ptr<Command> m_pPopScreen;
	std::unique_ptr<Command> m_pLoadTitleScreen;

	KeybindString m_ControlsText{ _T("Walking:\tARROWS\nTitle screen:\tBACKSPACE"),_T("Walking:\tDPAD\nTitle screen:\tY") };
	KeybindString m_ContinueText{ _T("Press ESC to continue."), _T("Press START to continue.") };
};

#endif // !PAUSESCREEN_H