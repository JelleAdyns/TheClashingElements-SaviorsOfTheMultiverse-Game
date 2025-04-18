#include "StartScreen.h"


StartScreen::StartScreen(std::unique_ptr<Command>&& startButton, std::unique_ptr<Command>&& highscoreButton) :
	Screen{ },
	m_BackGround{ _T("Space.png")},
	m_YTranslation{ 0 },
	m_DistanceBetweenBoys{ ENGINE.GetWindowRect().height / (FallingBoy::m_NrOfBoys / 2 - 1)},
	m_BackGroundSpeed{ 10 },
	m_SelectedButtonIndex{0},
	m_FallingBoys{ Point2Int{} }
{
	const auto& window = ENGINE.GetWindowRect();
	m_pVecButtons.push_back(std::make_unique<Button>(_T("Start"), Point2Int{window.width / 2,window.height / 3}, std::move(startButton), true));
	m_pVecButtons.back()->SetColor(RGB(255, 255, 255));
	m_pVecButtons.back()->SetWidth(100);
	m_pVecButtons.back()->SetHeight(8);

	m_pVecButtons.push_back(std::make_unique<Button>(_T("High Scores"), Point2Int{window.width / 2,window.height / 3 - 15}, std::move(highscoreButton) ));
	m_pVecButtons.back()->SetColor(RGB(255, 255, 255));
	m_pVecButtons.back()->SetWidth(100);
	m_pVecButtons.back()->SetHeight(8);
}

void StartScreen::Draw() const
{
	ENGINE.PushTransform();
	ENGINE.Translate(0, static_cast<int>(std::round(m_YTranslation)));
	m_BackGround.Draw();
	ENGINE.Translate(0, -ENGINE.GetWindowRect().height);
	m_BackGround.Draw();
	ENGINE.PopTransform();

	m_FallingBoys.Draw();

	auto& font = gameFont::GetFont();

	font.SetTextFormat(8, false, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Center);

	for (auto& button : m_pVecButtons)
	{
		button->Draw();
	}

	font.SetTextFormat(14, false, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Center);

	int border = 60;
	ENGINE.SetColor(RGB(255, 255, 0));
	ENGINE.DrawString(_T("The Clashing Elements\n\nThe Game"), font, border, ENGINE.GetWindowRect().height / 2, ENGINE.GetWindowRect().width - 2 * border, ENGINE.GetWindowRect().height/2);


	font.SetTextFormat(6, false, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Left);
	font.SetVerticalAllignment(Font::VertAllignment::Center);

	ENGINE.SetColor(RGB(255, 255, 255));
	ENGINE.DrawString(_T("DEMO VERSION"), font, 2, 2, ENGINE.GetWindowRect().width);

}
void StartScreen::Tick()
{
	m_YTranslation += m_BackGroundSpeed * ENGINE.GetDeltaTime();
	if (m_YTranslation >= ENGINE.GetWindowRect().height) m_YTranslation = 0;

	m_FallingBoys.UpdatePos();

}
void StartScreen::KeyInput(int virtualKeyCode)
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

void StartScreen::HandleControllerInput()
{

	if (ENGINE.ButtonDownThisFrame(Controller::Button::DpadUp, 0))
	{
		m_pVecButtons[m_SelectedButtonIndex]->ToggleSelection();
		++m_SelectedButtonIndex %= m_pVecButtons.size();
		m_pVecButtons[m_SelectedButtonIndex]->ToggleSelection();	
	}

	if (ENGINE.ButtonDownThisFrame(Controller::Button::DpadDown, 0))
	{
		m_pVecButtons[m_SelectedButtonIndex]->ToggleSelection();
		--m_SelectedButtonIndex %= m_pVecButtons.size();
		m_pVecButtons[m_SelectedButtonIndex]->ToggleSelection();
	}

	if (ENGINE.ButtonDownThisFrame(Controller::Button::A, 0))
	{
		m_pVecButtons[m_SelectedButtonIndex]->ExecuteCommand();
	}

}
