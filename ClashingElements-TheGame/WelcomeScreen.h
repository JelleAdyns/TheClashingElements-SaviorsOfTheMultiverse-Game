#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include "Screen.h"
#include "Commands.h"
#include "Game.h"

class WelcomeScreen final : public Screen
{
public:
	explicit WelcomeScreen(Game& game);
	virtual ~WelcomeScreen() = default;

	WelcomeScreen(const WelcomeScreen& other) = delete;
	WelcomeScreen(WelcomeScreen&& other) noexcept = delete;
	WelcomeScreen& operator=(const WelcomeScreen& other) = delete;
	WelcomeScreen& operator=(WelcomeScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Tick() override;
	virtual void KeyInput(int virtualKeyCode) override;
	virtual void HandleControllerInput() override;

	virtual void OnEnter() override {};
	virtual void OnExit() override {};
	virtual void OnSuspend() override {};
	virtual void OnResume() override {};
private:

	std::unique_ptr<PopScreenCommand> m_pPopScreen;

	KeybindString m_ButtonsText{ _T("Press ESC while playing to view the controls.\n\nPress SPACE to start.\n\n"), 
								_T("Press START while playing to view the controls.\n\nPress A to start.\n\n") };
};

#endif // !WELCOMESCREEN_H