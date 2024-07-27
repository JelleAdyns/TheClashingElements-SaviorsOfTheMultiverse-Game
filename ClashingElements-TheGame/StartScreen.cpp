#include "pch.h"
#include "StartScreen.h"


StartScreen::StartScreen(const std::string& backGroundFilePath, const Rectf& window, 
	std::function<void()> startButton, std::function<void()> highscoreButton) :
	Screen{ window },
	m_BackGround{ backGroundFilePath },
	m_YTranslation{ 0.f },
	m_DistanceBetweenBoys{ window.height / (FallingBoy::m_NrOfBoys / 2 - 1) },
	m_BackGroundSpeed{ 10 },
	m_SelectedButtonIndex{0},
	m_FallingBoys{ Point2f{}, window }
{
	m_pVecButtons.push_back(std::make_unique<Button>("Start", Point2f{window.width / 2,window.height / 3},startButton, true));
	m_pVecButtons.push_back(std::make_unique<Button>("High Scores", Point2f{window.width / 2,window.height / 3 - 15}, highscoreButton ));
}
StartScreen::~StartScreen()
{

}

void StartScreen::Draw() const
{
	glPushMatrix();
	glTranslatef(0, m_YTranslation, 0);
	m_BackGround.Draw();
	glTranslatef(0, -m_Window.height, 0);
	m_BackGround.Draw();
	glPopMatrix();

	m_FallingBoys.Draw();


	for (auto& button : m_pVecButtons)
	{
		button->Draw();
	}

}
void StartScreen::Update(float elapsedSec)
{
	m_YTranslation += m_BackGroundSpeed * elapsedSec;
	if (m_YTranslation >= m_Window.height) m_YTranslation = 0.f;

	m_FallingBoys.UpdatePos(elapsedSec);
	//for (auto& pBoy : m_FallingBoys)
	//{
	//	if (pBoy->DestRect().left<m_Window.height && pBoy->DestRect().left + pBoy->DestRect().height > m_Window.bottom) pBoy->Update(elapsedSec);
	//	pBoy->UpdatePos(elapsedSec);
	//	if (pBoy->DestRect().bottom > m_Window.height) pBoy->Reset(m_DistanceBetweenBoys);
	//}
}
void StartScreen::KeyInput(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		m_pVecButtons[m_SelectedButtonIndex]->ToggleSelection();
		++m_SelectedButtonIndex %= m_pVecButtons.size();
		m_pVecButtons[m_SelectedButtonIndex]->ToggleSelection();
		break;
	case SDLK_DOWN:
		m_pVecButtons[m_SelectedButtonIndex]->ToggleSelection();
		--m_SelectedButtonIndex %= m_pVecButtons.size();
		m_pVecButtons[m_SelectedButtonIndex]->ToggleSelection();
		break;
	case SDLK_SPACE:
		m_pVecButtons[m_SelectedButtonIndex]->ExecuteFunction();
		break;
	}
}