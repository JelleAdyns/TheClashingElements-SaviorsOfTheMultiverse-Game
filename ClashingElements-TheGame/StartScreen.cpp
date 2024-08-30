#include "StartScreen.h"


StartScreen::StartScreen(const std::wstring& backGroundFilePath, 
	std::unique_ptr<Command>&& startButton, std::unique_ptr<Command>&& highscoreButton) :
	Screen{ },
	m_BackGround{ backGroundFilePath },
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

	auto& font = globalFont::GetFont();

	font.SetTextFormat(8, false, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Center);

	for (auto& button : m_pVecButtons)
	{
		button->Draw();
	}

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