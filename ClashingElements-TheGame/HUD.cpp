#include "HUD.h"
#include "GlobalFont.h"
#include "Collectable.h"

const int HUD::m_HudHeight{ 32 };


HUD::HUD(int windowWidth, int windowHeight):
	m_HudArea{0, windowHeight-m_HudHeight, windowWidth, m_HudHeight},
	m_pCollectable{Point2Int{m_HudArea.left+10, m_HudArea.bottom + 5}, false}
{
}

void HUD::Draw() const
{
	ENGINE.SetColor(RGB(0,0,0));
	ENGINE.FillRectangle(m_HudArea);
	ENGINE.DrawString(m_pTextCollectables, GlobalFont::Get().GetFont(), Point2Int{m_HudArea.left +20, m_HudArea.bottom + 5}, 100);
	m_pCollectable.Draw();
}

void HUD::SetNrCollectables(int nrOfCollectables)
{
	m_pTextCollectables = to_tstring(nrOfCollectables);
}

int HUD::GetHudHeight()
{
	return m_HudHeight;
}