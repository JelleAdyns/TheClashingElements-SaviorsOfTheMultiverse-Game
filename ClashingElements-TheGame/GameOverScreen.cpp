#include "GameOverScreen.h"
#include "GameFont.h"

GameOverScreen::GameOverScreen(Game& game) :
	Screen{}
{

	m_pVecButtons.push_back(std::make_unique<Button>(
		_T("ENTER SCORE"),
		Point2Int{ENGINE.GetWindowRect().width / 2,m_DestRect.bottom + m_TextMargin*2 + 20},
		std::make_unique<LoadScreenCommand>(game, GameState::Results),
		true ));

	m_pVecButtons.push_back(std::make_unique<Button>( 
		_T("TITLE SCREEN"),
		Point2Int{ENGINE.GetWindowRect().width / 2,m_DestRect.bottom + m_TextMargin*2},
		std::make_unique<LoadScreenCommand>(game, GameState::Start)
		));

	const COLORREF color{ RGB(255, 255, 255) };
	const int width{ 120 };
	const int height{ 10 };

	for (auto& button : m_pVecButtons)
	{
		button->SetColor(color);
		button->SetWidth(width);
		button->SetHeight(height);
	}
}

void GameOverScreen::Draw() const
{
	const auto& wndwRect = ENGINE.GetWindowRect();

	ENGINE.SetColor(RGB(0, 0, 0), 0.3f);
	ENGINE.FillRectangle(wndwRect);
	ENGINE.SetColor(RGB(0, 0, 0), 0.5f);
	ENGINE.FillRectangle(m_DestRect);
	ENGINE.SetColor(RGB(0, 0, 0));
	ENGINE.DrawRectangle(m_DestRect);

	auto& font = gameFont::GetFont();
	font.SetTextFormat(9, true, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Top);

	
	ENGINE.SetColor(RGB(255, 255, 255));
	ENGINE.DrawString(
		_T("GAME OVER"),
		font,
		m_DestRect.left + m_TextMargin,
		m_DestRect.bottom + m_TextMargin,
		m_DestRect.width - m_TextMargin * 2,
		m_DestRect.height - m_TextMargin * 2);

	font.SetTextFormat(9, false, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Left);
	font.SetVerticalAllignment(Font::VertAllignment::Center);
	ENGINE.SetColor(RGB(255, 255, 240));

	const RectInt resultsDestRect{ m_DestRect.left + m_TextMargin, m_DestRect.bottom + 40, m_DestRect.width - m_TextMargin * 2, m_DestRect.height - 60 };
	int lineHeight{ resultsDestRect.height / static_cast<int>(m_VecScoreDisplays.size()) };

	for (int i = 0; i <= m_TextIndex; i++)
	{
		if (i == m_VecScoreDisplays.size() - 1)
		{
			font.SetHorizontalAllignment(Font::HorAllignment::Center);
			ENGINE.SetColor(RGB(255, 255, 0));
		}
		ENGINE.DrawString(
			m_VecScoreDisplays.at(i),
			font,
			resultsDestRect.left,
			resultsDestRect.bottom + resultsDestRect.height - lineHeight* (i+1),
			resultsDestRect.width,
			lineHeight);
	}


	if(m_ReadyToContinue)
	{
		font.SetTextFormat(9, true, false);
		font.SetHorizontalAllignment(Font::HorAllignment::Center);
		font.SetVerticalAllignment(Font::VertAllignment::Center);
		for (const auto& button : m_pVecButtons)
		{
			button->Draw();
		}
	}
	else
	{
		font.SetTextFormat(7, true, false);
		font.SetHorizontalAllignment(Font::HorAllignment::Center);
		font.SetVerticalAllignment(Font::VertAllignment::Center);
		ENGINE.SetColor(RGB(255, 255, 255));
		ENGINE.DrawString(
			_T("Press SPACE to continue."),
			font,
			m_DestRect.left + m_TextMargin,
			m_DestRect.bottom + m_TextMargin,
			m_DestRect.width - m_TextMargin * 2);
	}
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
	else m_ReadyToContinue = true;
	
}

void GameOverScreen::KeyInput(int virtualKeyCode)
{
	if (m_ReadyToContinue)
	{
		switch (virtualKeyCode)
		{
		case VK_UP:
			m_pVecButtons[m_SelectedButtonIndex]->ToggleSelection();
			++m_SelectedButtonIndex %= m_pVecButtons.size();
			m_pVecButtons[m_SelectedButtonIndex]->ToggleSelection();
			break;
		case VK_DOWN:
			m_pVecButtons[m_SelectedButtonIndex]->ToggleSelection();
			--m_SelectedButtonIndex %= m_pVecButtons.size();
			m_pVecButtons[m_SelectedButtonIndex]->ToggleSelection();
			break;
		case VK_SPACE:
			m_pVecButtons[m_SelectedButtonIndex]->ExecuteCommand();
			break;
		}
	}
	else
	{
		switch (virtualKeyCode)
		{
		case VK_SPACE:
			if (m_TextIndex < static_cast<int>(m_VecScoreDisplays.size()) - 1)
			{
				m_TextIndex = static_cast<int>(m_VecScoreDisplays.size()) - 1;
				m_ReadyToContinue = true;
			};
			break;
		}
	}
}

void GameOverScreen::OnEnter()
{
	int partialScore{};
	tstringstream textStream{};

	const auto& counters = HUD::GetCounters();
	
	partialScore = counters.nrOfCollectables * HUD::Counters::scorePerCollectable;
	textStream << std::setfill(_T('0')) << std::setw(3) << counters.nrOfCollectables << _T("\tCollectables:  ") << std::setw(6) << partialScore;
	m_VecScoreDisplays.push_back(textStream.str());

	partialScore = counters.nrOfSecondsLeft * HUD::Counters::scorePerSecond;
	textStream = tstringstream{} << std::setfill(_T('0')) << std::setw(3) << counters.nrOfSecondsLeft << _T("\tSeconds Left:  ") << std::setw(6) << partialScore;
	m_VecScoreDisplays.push_back(textStream.str());
	
	partialScore = counters.nrOfEnemiesKilled * HUD::Counters::scorePerEnemyKilled;
	textStream = tstringstream{} << std::setfill(_T('0')) << std::setw(3) << counters.nrOfEnemiesKilled << _T("\tEnemies Killed:") << std::setw(6) << partialScore;
	m_VecScoreDisplays.push_back(textStream.str());
	
	partialScore = counters.nrOfLivesLost * HUD::Counters::scorePerLifeLost;
	textStream = tstringstream{} << std::setfill(_T('0')) << std::setw(3) << counters.nrOfLivesLost << _T("\tLives Lost:    ") << std::setw(6) << partialScore;
	m_VecScoreDisplays.push_back(textStream.str());
	
	textStream = tstringstream{} << _T("Total: ")<< std::setfill(_T('0')) << std::setw(6) << counters.totalScore;
	m_VecScoreDisplays.push_back(textStream.str());
}
