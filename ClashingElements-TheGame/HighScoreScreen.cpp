#include "HighScoreScreen.h"
#include "GlobalFont.h"


HighScoreScreen::HighScoreScreen(Game& game, GameState nextState):
	Screen{},
	m_BackGround{L"Space.png"},
	m_pLoadStartScreenCommand{std::make_unique<LoadScreenCommand>(game, nextState)}
{
	highScoreHandling::LoadHighScores(m_VecHighScoreList);
}

void HighScoreScreen::Draw() const
{
	m_BackGround.Draw();

	const auto& wndwRect = ENGINE.GetWindowRect();
	auto& font = globalFont::GetFont();
	
	constexpr static int maxScores{ 10 };
	const int posHeightSteps{ wndwRect.height / (maxScores + 1)};

	font.SetTextFormat(10, false, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Center);

	ENGINE.SetColor(RGB(255, 255, 255));

	ENGINE.DrawString(_T("HIGHSCORES"), globalFont::GetFont(), 0, wndwRect.height - posHeightSteps, wndwRect.width);

	for (int i = 0; i < (m_VecHighScoreList.size() < maxScores ? m_VecHighScoreList.size() : maxScores); i++)
	{
		tstringstream highScoreText{};

		highScoreText << m_VecHighScoreList.at(i).name << _T('\t') 
			<< std::setfill(_T('0')) << std::setw(6) << to_tstring(m_VecHighScoreList.at(i).score);
		
		if (i == 0) ENGINE.SetColor(RGB(255, 255, 0));
		else ENGINE.SetColor(RGB(255, 255, 255));

		ENGINE.DrawString(highScoreText.str(), globalFont::GetFont(), 0, wndwRect.height - posHeightSteps * (i + 2), wndwRect.width);

	}
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
