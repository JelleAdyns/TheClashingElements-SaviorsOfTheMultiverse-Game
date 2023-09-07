#include "pch.h"
#include "SkinScreen.h"
#include "Character.h"
#include <iostream>
#include <utils.h>

SkinScreen::SkinScreen( const std::string& backGroundFilePath, const Rectf& window) :
	Screen{window},
	m_BackGround{ backGroundFilePath },
	m_IndexCurrSkin{ 0 }
{
	m_pSkins.push_back(new Character{ Skin::Finn });
	m_pSkins.push_back(new Character{ Skin::Wesley});
	
	for (int i = 0; i < m_pSkins.size(); i++)
	{
		m_pSkins[i]->SetPos(Point2f{ std::round(m_Window.width / (m_pSkins.size() + 1) * (i+1)), std::round(m_Window.height / 2) });
	}
	float rectWidth{40};
	float rectHeight{50};
	m_SelectionRect = Rectf{ m_pSkins[m_IndexCurrSkin]->GetHitBox().center.x - rectWidth / 2, m_pSkins[m_IndexCurrSkin]->DestRect().bottom - 10, rectWidth,rectHeight };
}
SkinScreen::~SkinScreen()
{
	for (int i = 0; i < m_pSkins.size(); ++i)
	{
		if (i != m_IndexCurrSkin)
		{
			delete m_pSkins[i];
			m_pSkins[i] = nullptr;
		}

	}
}

void SkinScreen::Draw() const
{
	m_BackGround.Draw();
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
}
Character* SkinScreen::GetCharacter() const
{
	return m_pSkins[m_IndexCurrSkin];
}


