#include "HighScoreScreen.h"
#include "GlobalFont.h"


HighScoreScreen::HighScoreScreen(Game& game):
	Screen{},
	m_BackGround{_T("Space.png")},
	m_pLoadStartScreenCommand{std::make_unique<PopScreenCommand>(game)}
{}

void HighScoreScreen::Draw() const
{
	m_BackGround.Draw();


	const auto& wndwRect = ENGINE.GetWindowRect();
	highScoreHandling::DrawScoreList(10, RectInt{ 0, 10, wndwRect.width, wndwRect.height - 10 }, highScoreHandling::GetFirstScore(false).name);
	
	constexpr static int maxScores{ 10 };
	constexpr static int border{ 6 };

	ENGINE.DrawString(_T("PRESS DELETE"), font, 0, border, wndwRect.width);
}

void HighScoreScreen::Tick()
{
}

void HighScoreScreen::KeyInput(int virtualKey)
{
	switch (virtualKey)
	{
	case VK_SPACE:
		m_pLoadStartScreenCommand->Execute();
		break;
	}
}

void HighScoreScreen::OnEnter()
{
	highScoreHandling::LoadHighScores();
}
