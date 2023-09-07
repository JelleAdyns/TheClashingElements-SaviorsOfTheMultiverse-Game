#include "pch.h"
#include "StartScreen.h"


StartScreen::StartScreen(const std::string& backGroundFilePath, const Rectf& window):
	Screen{window},
	m_BackGround{backGroundFilePath},
	m_YTranslation{0.f},
	m_DistanceBetweenBoys{ window.height / (FallingBoy::m_NrOfBoys / 2 - 1) },
	m_BackGroundSpeed{10},
	m_FallingBoys{Point2f{}, window}
{
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
}
void StartScreen::Update(float elapsedSec)
{
	m_YTranslation += m_BackGroundSpeed * elapsedSec;
	if (m_YTranslation >= m_Window.height) m_YTranslation = 0.f;

	m_FallingBoys.Update(elapsedSec);
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

}