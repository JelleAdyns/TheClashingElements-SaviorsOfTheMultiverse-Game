#include "StartScreen.h"


StartScreen::StartScreen(const std::wstring& backGroundFilePath, const RectInt& window, 
	std::function<void()> startButton, std::function<void()> highscoreButton) :
	Screen{ window },
	m_BackGround{ backGroundFilePath },
	m_YTranslation{ 0 },
	m_DistanceBetweenBoys{ window.height / (FallingBoy::m_NrOfBoys / 2 - 1) },
	m_BackGroundSpeed{ 10 },
	m_SelectedButtonIndex{0},
	m_FallingBoys{ Point2Int{}, window }
{
	m_pVecButtons.push_back(std::make_unique<Button>(_T("Start"), Point2Int{window.width / 2,window.height / 3},startButton, true));
	m_pVecButtons.push_back(std::make_unique<Button>(_T("High Scores"), Point2Int{window.width / 2,window.height / 3 - 15}, highscoreButton ));
}

void StartScreen::Draw() const
{
	ENGINE.PushTransform();
	ENGINE.Translate(0, static_cast<int>(std::round(m_YTranslation)));
	m_BackGround.Draw();
	ENGINE.Translate(0, -m_Window.height);
	m_BackGround.Draw();
	ENGINE.PopTransform();

	m_FallingBoys.Draw();


	for (auto& button : m_pVecButtons)
	{
		button->Draw();
	}

}
void StartScreen::Tick()
{
	m_YTranslation += m_BackGroundSpeed * ENGINE.GetDeltaTime();
	if (m_YTranslation >= m_Window.height) m_YTranslation = 0;

	m_FallingBoys.UpdatePos();
	//for (auto& pBoy : m_FallingBoys)
	//{
	//	if (pBoy->DestRect().left<m_Window.height && pBoy->DestRect().left + pBoy->DestRect().height > m_Window.bottom) pBoy->Update(elapsedSec);
	//	pBoy->UpdatePos(elapsedSec);
	//	if (pBoy->DestRect().bottom > m_Window.height) pBoy->Reset(m_DistanceBetweenBoys);
	//}
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
		m_pVecButtons[m_SelectedButtonIndex]->ExecuteFunction();
		break;
	}
}