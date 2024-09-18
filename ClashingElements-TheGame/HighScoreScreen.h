#ifndef HIGHSCORESCREEN_H
#define HIGHSCORESCREEN_H

#include "Screen.h"
#include "BackGround.h"
#include "HighScoreHandling.h"
#include <vector>
#include "Commands.h"

class HighScoreScreen final : public Screen
{
public:
	explicit HighScoreScreen(Game& game);
	virtual ~HighScoreScreen() = default;

	HighScoreScreen(const HighScoreScreen& other) = delete;
	HighScoreScreen(HighScoreScreen&& other) noexcept = delete;
	HighScoreScreen& operator=(const HighScoreScreen& other) = delete;
	HighScoreScreen& operator=(HighScoreScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Tick() override;
	virtual void KeyInput(int virtualKey) override;

	virtual void OnEnter() override;
	virtual void OnExit() override{};
	virtual void OnSuspend() override{};
	virtual void OnResume() override{};

private:
	BackGround m_BackGround;
	std::unique_ptr<Command> m_pLoadStartScreenCommand;
};


#endif // !HIGHSCORESCREEN_H
