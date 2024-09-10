#include "GameOverScreen.h"
#include "GlobalFont.h"

GameOverScreen::GameOverScreen(Game& game, HUD::Counters counters) :
	Screen{},
	m_pLoadScreen{ std::make_unique<LoadScreenCommand>(game, GameState::Start) },
	m_Counters{ counters }
{

}

void GameOverScreen::Draw() const
{
	const auto& wndwRect = ENGINE.GetWindowRect();
	static constexpr int margin = 20;
	static constexpr int textMargin = 5;
	static const int height = wndwRect.height - 100;
	static const RectInt destRect{ margin, (wndwRect.height - height) / 2, wndwRect.width - margin * 2, height };

	ENGINE.SetColor(RGB(0, 0, 0), 0.3f);
	ENGINE.FillRectangle(wndwRect);
	ENGINE.SetColor(RGB(0, 0, 0), 0.5f);
	ENGINE.FillRectangle(destRect);

	auto& font = globalFont::GetFont();
	font.SetTextFormat(9, true, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Top);

	ENGINE.SetColor(RGB(0, 0, 0));
	ENGINE.DrawRectangle(destRect);
	ENGINE.SetColor(RGB(255, 255, 255));
	ENGINE.DrawString(
		_T("GAME OVER"),
		font,
		destRect.left + textMargin,
		destRect.bottom + textMargin,
		destRect.width - textMargin * 2,
		destRect.height - textMargin * 2);

	font.SetTextFormat(9, false, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Left);
	font.SetVerticalAllignment(Font::VertAllignment::Center);

	const RectInt resultsDestRect{ destRect.left + textMargin, destRect.bottom + 20, destRect.width - textMargin * 2, destRect.height - 40 };
	int lineHeight{ resultsDestRect.height / static_cast<int>(m_VecScoreDisplays.size()) };

	for (int i = 0; i <= m_TextIndex; i++)
	{
		if (i == m_VecScoreDisplays.size() - 1)
		{
			font.SetHorizontalAllignment(Font::HorAllignment::Center);
		}
		ENGINE.DrawString(
			m_VecScoreDisplays.at(i),
			font,
			resultsDestRect.left,
			resultsDestRect.bottom + resultsDestRect.height - lineHeight* (i+1),
			resultsDestRect.width,
			lineHeight);
	}

	font.SetTextFormat(7, true, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Center);

	ENGINE.DrawString(
		_T("Press SPACE to continue."),
		font,
		destRect.left + textMargin,
		destRect.bottom + textMargin,
		destRect.width - textMargin * 2);
}

void GameOverScreen::Tick()
{
	if (m_TextIndex < static_cast<int>(m_VecScoreDisplays.size()) - 1)
	{
		static float time{};
		static constexpr float maxTime{ 1.f };
		time += ENGINE.GetDeltaTime();
		if (time >= maxTime)
		{
			++m_TextIndex;
			time = 0.f;
		}
	}
}

void GameOverScreen::KeyInput(int virtualKeyCode)
{
	switch (virtualKeyCode)
	{
	case VK_SPACE:
		if (m_TextIndex < static_cast<int>(m_VecScoreDisplays.size()) - 1) 
			m_TextIndex = static_cast<int>(m_VecScoreDisplays.size()) - 1;
		else m_pLoadScreen->Execute();
		break;
	}
}

void GameOverScreen::OnEnter()
{
	int partialScore{};
	tstringstream textStream{};

	partialScore = m_Counters.nrOfCollectables * HUD::Counters::scorePerCollectable;
	textStream << std::setfill(_T('0')) << std::setw(3) << m_Counters.nrOfCollectables << _T("\tCollectables:  ") << std::setw(6) << partialScore;
	m_VecScoreDisplays.push_back(textStream.str());

	partialScore = m_Counters.nrOfSecondsLeft * HUD::Counters::scorePerSecond;
	textStream = tstringstream{} << std::setfill(_T('0')) << std::setw(3) << m_Counters.nrOfSecondsLeft << _T("\tSeconds Left:  ") << std::setw(6) << partialScore;
	m_VecScoreDisplays.push_back(textStream.str());
	
	partialScore = m_Counters.nrOfEnemiesKilled * HUD::Counters::scorePerEnemyKilled;
	textStream = tstringstream{} << std::setfill(_T('0')) << std::setw(3) << m_Counters.nrOfEnemiesKilled << _T("\tEnemies Killed:") << std::setw(6) << partialScore;
	m_VecScoreDisplays.push_back(textStream.str());
	
	partialScore = m_Counters.nrOfLivesLost * HUD::Counters::scorePerLifeLost;
	textStream = tstringstream{} << std::setfill(_T('0')) << std::setw(3) << m_Counters.nrOfLivesLost << _T("\tLives Lost:    ") << std::setw(6) << partialScore;
	m_VecScoreDisplays.push_back(textStream.str());
	
	textStream = tstringstream{} << _T("Total: ")<< std::setfill(_T('0')) << std::setw(6) << m_Counters.totalScore;
	m_VecScoreDisplays.push_back(textStream.str());
}
