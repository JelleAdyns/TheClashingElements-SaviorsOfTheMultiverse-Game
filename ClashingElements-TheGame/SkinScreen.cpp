#include "SkinScreen.h"
#include "Player.h"
#include "Button.h"


SkinScreen::SkinScreen(Game& game, GameState nextState) :
	Screen{},
	m_BackGround{ L"Space.png" },
	m_IndexCurrSkin{ 0 },
	m_pLoadLevelCommand{std::make_unique<LoadScreenCommand>(game, nextState)}
{
	m_pVecSkins.emplace(Skin::Finn, std::make_unique<Player>(Skin::Finn) );
	m_pVecSkins.emplace(Skin::Wesley, std::make_unique<Player>(Skin::Wesley));

	const auto& windowRect = ENGINE.GetWindowRect();

	std::vector<Point2Int> positions(m_pVecSkins.size());

	for (int i = 0; i < m_pVecSkins.size(); i++)
	{
		positions.at(i) = Point2Int{windowRect.width / (static_cast<int>(m_pVecSkins.size()) + 1) * (i + 1), windowRect.height / 2};
		m_pVecSkins.at(static_cast<Skin>(i))->SetPos(positions.at(i));
	}	
	
	static int rectWidth{40};
	static int rectHeight{50};

	m_SelectionRect = RectInt{ 
		m_pVecSkins[static_cast<Skin>(m_IndexCurrSkin)]->GetHitBox().center.x - rectWidth / 2,
		m_pVecSkins[static_cast<Skin>(m_IndexCurrSkin)]->DestRect().bottom - 10,
		rectWidth,
		rectHeight 
	};
}

void SkinScreen::Draw() const
{
	m_BackGround.Draw();
	for (const auto& [key, pPlayer] : m_pVecSkins)
	{
		pPlayer->Draw();
	}
	ENGINE.SetColor(RGB(255, 255, 255));
	ENGINE.DrawRectangle(RectInt{ m_SelectionRect });
}
void SkinScreen::Tick()
{
	m_pVecSkins[static_cast<Skin>(m_IndexCurrSkin)]->Update();
}
void SkinScreen::KeyInput(int virtualKeyCode)
{
	switch (virtualKeyCode)
	{
	case VK_LEFT:
		m_pVecSkins[static_cast<Skin>(m_IndexCurrSkin)]->ResetFrames();
		--m_IndexCurrSkin %= m_pVecSkins.size();
		m_SelectionRect.left = m_pVecSkins[static_cast<Skin>(m_IndexCurrSkin)]->GetHitBox().center.x - m_SelectionRect.width / 2;
		break;
	case VK_RIGHT:
		m_pVecSkins[static_cast<Skin>(m_IndexCurrSkin)]->ResetFrames();
		++m_IndexCurrSkin %= m_pVecSkins.size();
		m_SelectionRect.left = m_pVecSkins[static_cast<Skin>(m_IndexCurrSkin)]->GetHitBox().center.x - m_SelectionRect.width / 2;
		break;
	case VK_SPACE:
		m_pLoadLevelCommand->Execute();
	}
}
Skin SkinScreen::GetPlayer() const
{
	return static_cast<Skin>(m_IndexCurrSkin);
}


