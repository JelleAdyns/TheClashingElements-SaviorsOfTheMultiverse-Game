#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "Screen.h"
#include "BackGround.h"
#include "FallingBoy.h"
#include "Button.h"
#include "Commands.h"


class StartScreen final: public Screen
{
public:
	explicit StartScreen(std::unique_ptr<Command>&& startButton, std::unique_ptr<Command>&& highscoreButton);
	~StartScreen() = default;

	StartScreen(const StartScreen& other) = delete;
	StartScreen(StartScreen&& other) noexcept = delete;
	StartScreen& operator=(const StartScreen& other) = delete;
	StartScreen& operator=(StartScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Tick() override;
	virtual void KeyInput(int virtualKeyCode) override;

	virtual void OnEnter() override {};
	virtual void OnExit() override{};
	virtual void OnSuspend() override{};
	virtual void OnResume() override{};
private:

	BackGround m_BackGround;
	float m_YTranslation;
	int m_DistanceBetweenBoys;
	int m_BackGroundSpeed;
	int m_SelectedButtonIndex;
	FallingBoy m_FallingBoys;

	std::vector<std::unique_ptr<Button>> m_pVecButtons;
};

#endif // !STARTSCREEN_H
