#include "pch.h"
#include "HUD.h"
#include "GlobalFont.h"
#include "Collectable.h"
#include <utils.h>

const int HUD::m_HudHeight{ 32 };


HUD::HUD(float windowWidth, float windowHeight):
	m_HudArea{0.f, windowHeight-m_HudHeight, windowWidth, m_HudHeight},
	m_pCollectable{Point2f{m_HudArea.left+10, m_HudArea.bottom + 5}, false}
{
}
HUD::~HUD()
{
	delete m_pTextCollectables;
	m_pTextCollectables = nullptr;
}
void HUD::Draw() const
{
	utils::SetColor(Color4f{ 0.f,0.f,0.f,1.f });
	utils::FillRect(m_HudArea);
	m_pTextCollectables->Draw(Point2f{m_HudArea.left +20, m_HudArea.bottom + 5});
	m_pCollectable.Draw();
}

void HUD::SetNrCollectables(int nrOfCollectables)
{
	if(m_pTextCollectables != nullptr) delete m_pTextCollectables;
	m_pTextCollectables = new Texture{ std::to_string(nrOfCollectables), GlobalFont::Get().GetFont(), m_TextColor};
}

int HUD::GetHudHeight()
{
	return m_HudHeight;
}