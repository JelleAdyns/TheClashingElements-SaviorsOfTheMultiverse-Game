#include "SkinScreen.h"
#include "Player.h"
#include "Button.h"


SkinScreen::SkinScreen( const std::wstring& backGroundFilePath, const RectInt& window, std::function<void()> nextEvent) :
	Screen{window},
	m_BackGround{ backGroundFilePath },
	m_IndexCurrSkin{ 0 }
{
	m_pVecSkins.push_back(std::make_shared<Player>( Skin::Finn ));
	m_pVecSkins.push_back(std::make_shared<Player>(Skin::Wesley));

	std::vector<Point2Int> positions;
	positions.resize(m_pVecSkins.size());
	for (int i = 0; i < m_pVecSkins.size(); i++)
	{
		positions[i] = Point2Int{ m_Window.width / (static_cast<int>(m_pVecSkins.size()) + 1) * (i + 1), m_Window.height / 2 };
	}

	//auto finnFunction = [&](){}
	m_pVecSkinButtons.push_back(std::make_unique<Button>(_T("Finn"), positions[0], nextEvent));
	m_pVecSkinButtons.push_back(std::make_unique<Button>(_T("Wesley"), positions[1], nextEvent));
	//m_pVecSkinButtons.push_back(std::make_shared<Button>("Finn", positions[0], Skin::Finn));
	//m_pVecSkinButtons.push_back(std::make_shared<Button>(Skin::Wesley));
	
	for (int i = 0; i < m_pVecSkins.size(); i++)
	{
		m_pVecSkins[i]->SetPos(Point2Int{ m_Window.width / (static_cast<int>(m_pVecSkins.size()) + 1) * (i + 1), m_Window.height / 2 });
	}
	int rectWidth{40};
	int rectHeight{50};
	m_SelectionRect = RectInt{ m_pVecSkins[m_IndexCurrSkin]->GetHitBox().center.x - rectWidth / 2, m_pVecSkins[m_IndexCurrSkin]->DestRect().bottom - 10, rectWidth,rectHeight };
}
SkinScreen::~SkinScreen()
{
	/*for (int i = 0; i < m_pVecSkins.size(); ++i)
	{
		if (i != m_IndexCurrSkin)
		{
			delete m_pVecSkins[i];
			m_pVecSkins[i] = nullptr;
		}

	}*/
}

void SkinScreen::Draw() const
{
	m_BackGround.Draw();
	for (const auto& pSkin : m_pVecSkins)
	{
		pSkin->Draw();
	}
	ENGINE.SetColor(RGB(255, 255, 255));
	ENGINE.DrawRectangle(RectInt{ m_SelectionRect });
}
void SkinScreen::Tick()
{
	m_pVecSkins[m_IndexCurrSkin]->Update();
}
void SkinScreen::KeyInput(int virtualKeyCode)
{
	switch (virtualKeyCode)
	{
	case VK_LEFT:
		m_pVecSkins[m_IndexCurrSkin]->ResetFrames();
		--m_IndexCurrSkin %= m_pVecSkins.size();
		m_SelectionRect.left = m_pVecSkins[m_IndexCurrSkin]->GetHitBox().center.x - m_SelectionRect.width / 2;
		break;
	case VK_RIGHT:
		m_pVecSkins[m_IndexCurrSkin]->ResetFrames();
		++m_IndexCurrSkin %= m_pVecSkins.size();
		m_SelectionRect.left = m_pVecSkins[m_IndexCurrSkin]->GetHitBox().center.x - m_SelectionRect.width / 2;
		break;
	}
}
std::shared_ptr<Player> SkinScreen::GetPlayer() const
{
	return m_pVecSkins[m_IndexCurrSkin];
}


