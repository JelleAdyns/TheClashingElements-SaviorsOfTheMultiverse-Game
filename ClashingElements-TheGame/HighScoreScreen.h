#ifndef HIGHSCORESCREEN_H
#define HIGHSCORESCREEN_H

#include "Screen.h"
#include "BackGround.h"
#include "HighScoreHandling.h"
#include <vector>

class HighScoreScreen final : public Screen
{
public:
	explicit HighScoreScreen();
	~HighScoreScreen() = default;

	HighScoreScreen(const HighScoreScreen& other) = delete;
	HighScoreScreen(HighScoreScreen&& other) noexcept = delete;
	HighScoreScreen& operator=(const HighScoreScreen& other) = delete;
	HighScoreScreen& operator=(HighScoreScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Tick() override;
	virtual void KeyInput(int virtualKey) override;

private:
	BackGround m_BackGround;

	std::vector<highScoreHandling::PlayerScore> m_VecHighScoreList;
};


#endif // !HIGHSCORESCREEN_H
