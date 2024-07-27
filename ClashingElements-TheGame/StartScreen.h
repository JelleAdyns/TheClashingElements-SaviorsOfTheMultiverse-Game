#pragma once
#include "Screen.h"
#include "BackGround.h"
#include "FallingBoy.h"
#include "Button.h"


class StartScreen final: public Screen
{
public:
	explicit StartScreen(const std::string& backGroundFilePath, const Rectf& window,
		std::function<void()> startButton, std::function<void()> highscoreButton);
	~StartScreen();

	StartScreen(const StartScreen& other) = delete;
	StartScreen(StartScreen&& other) noexcept = delete;
	StartScreen& operator=(const StartScreen& other) = delete;
	StartScreen& operator=(StartScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;
	virtual void KeyInput(const SDL_KeyboardEvent& e) override;

private:

	BackGround m_BackGround;
	float m_YTranslation;
	float m_DistanceBetweenBoys;
	int m_BackGroundSpeed;
	int m_SelectedButtonIndex;
	FallingBoy m_FallingBoys;

	std::vector<std::unique_ptr<Button>> m_pVecButtons;
};

