#include "pch.h"
#include "SkinScreen.h"
#include "Character.h"
#include <iostream>
#include <utils.h>

SkinScreen::SkinScreen(const Point2f& bottomCenter, const std::string& backGroundFilePath, const Rectf& window) :
	Screen{ bottomCenter, backGroundFilePath },
	m_IndexCurrSkin{ 0 },
	m_Window{window}

{
	m_pSkins.push_back(new Character{ Skin::Finn });
	m_pSkins.push_back(new Character{ Skin::Wesley});
	
	for (int i = 0; i < m_pSkins.size(); i++)
	{
		m_pSkins[i]->SetPos(Point2f{ m_Window.width / (m_pSkins.size() + 1) * (i+1), m_Window.height / 2 });
	}
	float rectWidth{40};
	float rectHeight{50};
	m_SelectionRect = Rectf{ m_pSkins[m_IndexCurrSkin]->GetHitBox().center.x - rectWidth / 2, m_pSkins[m_IndexCurrSkin]->DestRect().bottom - 10, rectWidth,rectHeight };
}
SkinScreen::~SkinScreen()
{
	for (auto& pSkin : m_pSkins)
	{
		delete pSkin;
		pSkin = nullptr;
	}
}

void SkinScreen::Draw() const
{
	for (const auto& pSkin : m_pSkins)
	{
		pSkin->Draw();
	}
	utils::DrawRect(Rectf{ m_SelectionRect });
}
void SkinScreen::Update(float elapsedSec)
{
	m_pSkins[m_IndexCurrSkin]->Update(elapsedSec);
}
void SkinScreen::KeyInput(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		m_pSkins[m_IndexCurrSkin]->ResetFrames();
		--m_IndexCurrSkin %= m_pSkins.size();
		m_SelectionRect.left = m_pSkins[m_IndexCurrSkin]->GetHitBox().center.x - m_SelectionRect.width / 2;
		break;
	case SDLK_RIGHT:
		m_pSkins[m_IndexCurrSkin]->ResetFrames();
		++m_IndexCurrSkin %= m_pSkins.size();
		m_SelectionRect.left = m_pSkins[m_IndexCurrSkin]->GetHitBox().center.x - m_SelectionRect.width / 2;
		break;
	}
	std::cout << m_IndexCurrSkin << std::endl;
}


