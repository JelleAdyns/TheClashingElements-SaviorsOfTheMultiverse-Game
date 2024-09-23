#include "ResultsScreen.h"
#include "HighScoreHandling.h"
#include "GameFont.h"
#include "HUD.h"

ResultsScreen::ResultsScreen(Game& game):
	Screen{},
	m_pLoadScreen{ std::make_unique<LoadScreenCommand>(game, GameState::Start) },
	m_pPushScreen{ std::make_unique<PushScreenCommand>(game,GameState::GameOver) }, // Are you sure?-screen
	m_BackGround{ _T("Space.png") }
{}

void ResultsScreen::Draw() const
{
	m_BackGround.Draw();

	const auto& wndwRect = ENGINE.GetWindowRect();
	auto& font = gameFont::GetFont();

	font.SetTextFormat(10, true, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Bottom);

	const int nameScoreBottom{ wndwRect.height - 80 };
	ENGINE.SetColor(RGB(255, 255, 255));
	ENGINE.DrawString(_T("ENTER YOUR NAME"), font, 0, wndwRect.height - 30, wndwRect.width);
	ENGINE.DrawString(m_Name + (m_NameEntered ? _T(' ') : m_CurrentCharacter), font, RectInt{ 0,nameScoreBottom, wndwRect.width / 2, 80 });
	ENGINE.DrawString(m_Score, font, RectInt{ wndwRect.width / 2,nameScoreBottom, wndwRect.width/2, 80 });

	highScoreHandling::DrawScoreList(5, RectInt{ 0, 20, wndwRect.width, wndwRect.height / 2 }, m_NameEntered ? GetInitials() : highScoreHandling::placeholderName);

	font.SetTextFormat(6, false, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Bottom);
	
	if(m_NameEntered) ENGINE.DrawString(m_ContinueText.GetActiveString(), font, 0, font.GetFontSize(), wndwRect.width);
	else ENGINE.DrawString(m_CycleText.GetActiveString(), font, 0, nameScoreBottom - font.GetFontSize() * 3, wndwRect.width / 2);
}

void ResultsScreen::Tick()
{
}

void ResultsScreen::KeyInput(int virtualKeyCode)
{
	
	if (not m_NameEntered)
	{
		CycleName(virtualKeyCode);
	}
	else
	{
		switch (virtualKeyCode)
		{
		case VK_SPACE:
			m_pLoadScreen->Execute();
			break;
		}
	}
}

void ResultsScreen::HandleControllerInput()
{
	if (not m_NameEntered)
	{
		CycleNameController();
	}
	else
	{
		if (ENGINE.ButtonDownThisFrame(Controller::Button::A, 0))
		{
			m_pLoadScreen->Execute();
		}
	}
}

void ResultsScreen::OnEnter()
{
	highScoreHandling::WriteHighScores(highScoreHandling::placeholderName, HUD::GetCounters().totalScore);

	m_Name = _T("NAME\n");
	m_Score = (tstringstream{} <<_T("SCORE\n") << std::setfill(_T('0')) << std::setw(6) << HUD::GetCounters().totalScore).str();
}


void ResultsScreen::CycleName(int virtualKeyCode)
{


	switch (virtualKeyCode)
	{
	case VK_UP:

		if (m_CurrentCharacter == _T('.')) m_CurrentCharacter = _T('A');
		else if (m_CurrentCharacter == _T('Z')) m_CurrentCharacter = _T('.');
		else ++m_CurrentCharacter;

		break;
	case VK_DOWN:

		if (m_CurrentCharacter == _T('.')) m_CurrentCharacter = _T('Z');
		else if (m_CurrentCharacter == _T('A')) m_CurrentCharacter = _T('.');
		else --m_CurrentCharacter;

		break;
	case VK_RETURN:
	{
		++m_NrOfEnters;
		m_Name += m_CurrentCharacter;
		m_CurrentCharacter = _T('.');
		if (m_NrOfEnters == highScoreHandling::maxCharacters)
		{
			m_NameEntered = true;
			highScoreHandling::RemoveHighScores(highScoreHandling::placeholderName, false);
			highScoreHandling::WriteHighScores(GetInitials(), HUD::GetCounters().totalScore, false);
		}
	}
	break;
	case VK_BACK:
	{
		if (m_NrOfEnters > 0 and not m_NameEntered)
		{
			--m_NrOfEnters;
			m_Name.erase(m_Name.size() - 1);
			m_CurrentCharacter = _T('.');
		}
	}
	break;
	}

}

void ResultsScreen::CycleNameController()
{
	if (ENGINE.ButtonDownThisFrame(Controller::Button::DpadUp, 0))
	{
		if (m_CurrentCharacter == _T('.')) m_CurrentCharacter = _T('A');
		else if (m_CurrentCharacter == _T('Z')) m_CurrentCharacter = _T('.');
		else ++m_CurrentCharacter;
	}

	if (ENGINE.ButtonDownThisFrame(Controller::Button::DpadDown, 0))
	{
		if (m_CurrentCharacter == _T('.')) m_CurrentCharacter = _T('Z');
		else if (m_CurrentCharacter == _T('A')) m_CurrentCharacter = _T('.');
		else --m_CurrentCharacter;
	}

	if (ENGINE.ButtonDownThisFrame(Controller::Button::A, 0))
	{
		++m_NrOfEnters;
		m_Name += m_CurrentCharacter;
		m_CurrentCharacter = _T('.');
		if (m_NrOfEnters == highScoreHandling::maxCharacters)
		{
			m_NameEntered = true;
			highScoreHandling::RemoveHighScores(highScoreHandling::placeholderName, false);
			highScoreHandling::WriteHighScores(GetInitials(), HUD::GetCounters().totalScore, false);
		}
	}

	if (ENGINE.ButtonDownThisFrame(Controller::Button::B, 0))
	{
		if (m_NrOfEnters > 0 and not m_NameEntered)
		{
			--m_NrOfEnters;
			m_Name.erase(m_Name.size() - 1);
			m_CurrentCharacter = _T('.');
		}
	}
}

tstring ResultsScreen::GetInitials() const
{
	const int maxChars{ highScoreHandling::maxCharacters };
	return m_Name.substr(m_Name.size() - maxChars, maxChars);
}
