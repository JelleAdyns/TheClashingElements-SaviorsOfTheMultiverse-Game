#include "pch.h"
#include "SkinScreen.h"

SkinScreen::SkinScreen(const Point2f& bottomCenter, const std::string& backGroundFilePath, const Rectf& window) :
	Screen{ bottomCenter, backGroundFilePath },
	m_IndexSelectedSkin{ 0 },
	m_NrOfCols{ 8 },
	m_NrOfFrames{ 32 },
	m_CurrentCol{ 0 },
	m_Window{window}
{
	m_pSkins.push_back(new Texture { "Finn.png" });
	m_pSkins.push_back(new Texture { "Wesley.png" });
}
SkinScreen::~SkinScreen()
{

}

void SkinScreen::Draw() const
{
	for (int i = 0; i < m_pSkins.size(); i++)
	{
		m_pSkins[i]->Draw(DestRect(*m_pSkins[i]), SrcRect(*m_pSkins[i]));
	}
}
void SkinScreen::Update(float elapsedSec)
{
	for (const auto& pSkin : m_pSkins)
	{
		m_PassedTime += elapsedSec;
		if (m_PassedTime >= m_FrameTime)
		{
			++m_CurrentCol %= m_NrOfCols;
			m_PassedTime = 0.f;
		}
	}
}
void SkinScreen::KeyInput(const SDL_KeyboardEvent& e)
{

}

Rectf SkinScreen::DestRect(const Texture& texture) const
{
	return Rectf{ m_Window.width / (m_pSkins.size() + 1), m_Window.height / 2 - SrcRect(texture).height / 2, SrcRect(texture).width, SrcRect(texture).height };
}

Rectf SkinScreen::SrcRect(const Texture& texture) const
{
	Rectf srcRect{};
	srcRect.width = texture.GetWidth() / m_NrOfCols;
	srcRect.height = texture.GetHeight() / (m_NrOfFrames/m_NrOfCols);
	srcRect.left = srcRect.width * m_CurrentCol;
	srcRect.bottom = srcRect.height;
	return srcRect;
}
