#include "HighScoreScreen.h"
#include "GlobalFont.h"


HighScoreScreen::HighScoreScreen(Game& game):
	Screen{},
	m_BackGround{_T("Space.png")},
	m_pLoadStartScreenCommand{std::make_unique<PopScreenCommand>(game)}
{
	highScoreHandling::LoadHighScores(m_VecHighScoreList);
}

void HighScoreScreen::Draw() const
{
	m_BackGround.Draw();

	const auto& wndwRect = ENGINE.GetWindowRect();
	auto& font = globalFont::GetFont();
	
	constexpr static int maxScores{ 10 };
	constexpr static int border{ 6 };
	const int posHeightSteps{ (wndwRect.height - border * 2) / (maxScores + 2) };

	font.SetTextFormat(10, false, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Center);

	ENGINE.SetColor(RGB(255, 255, 255));

	ENGINE.DrawString(_T("HIGHSCORES"), globalFont::GetFont(), 0, wndwRect.height - posHeightSteps - border, wndwRect.width);

	for (int i = 0; i < (m_VecHighScoreList.size() < maxScores ? m_VecHighScoreList.size() : maxScores); i++)
	{
		if (i == 0) ENGINE.SetColor(RGB(255, 255, 0));
		else ENGINE.SetColor(RGB(255, 255, 255));

		highScoreHandling::DrawScoreLine(Point2Int{ 0, wndwRect.height - posHeightSteps * (i + 2) - border }, wndwRect.width, m_VecHighScoreList.at(i), (i + 1));
	}
	ENGINE.DrawString(_T("PRESS DELETE"), globalFont::GetFont(), 0, border, wndwRect.width);
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
