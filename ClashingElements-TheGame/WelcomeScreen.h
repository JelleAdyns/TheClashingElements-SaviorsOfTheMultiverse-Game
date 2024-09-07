#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include "Screen.h"
#include "Commands.h"
#include "Game.h"

class WelcomeScreen final : public Screen
{
public:
	explicit WelcomeScreen(Game& game);
	~WelcomeScreen() = default;

	WelcomeScreen(const WelcomeScreen& other) = delete;
	WelcomeScreen(WelcomeScreen&& other) noexcept = delete;
	WelcomeScreen& operator=(const WelcomeScreen& other) = delete;
	WelcomeScreen& operator=(WelcomeScreen&& other) noexcept = delete;

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

#endif // !WELCOMESCREEN_H