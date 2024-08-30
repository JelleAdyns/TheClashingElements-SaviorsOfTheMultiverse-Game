#include "HUD.h"
#include "GlobalFont.h"
#include "Collectable.h"
#include <sstream>

const int HUD::m_HudHeight{ 40 };


HUD::HUD(int windowWidth, int windowHeight) :
	m_HudArea{ 0, windowHeight - m_HudHeight, windowWidth, m_HudHeight }
{
	tstringstream yourStream{};
	yourStream << _T("Your Score\n") << std::setfill(_T('0')) << std::setw(6) << _T('0');
	m_YourScore = yourStream.str();

	tstringstream highStream{};
	highStream << _T("High Score\n") << std::setfill(_T('0')) << std::setw(6) << _T('0');
	m_HighScore = highStream.str();
}

void HUD::Draw() const
{
	ENGINE.SetColor(RGB(0,0,0));
	ENGINE.FillRectangle(m_HudArea);

	auto& font = globalFont::GetFont();
	font.SetTextFormat(8, false, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Top);

	int width{ 100 };
	int height{ font.GetFontSize() * 2 + 1};
	int top{ ENGINE.GetWindowRect().height - 6 };

	Point2Int yourPos{ ENGINE.GetWindowRect().width / 3 - width / 2, top - height};
	Point2Int highPos{ ENGINE.GetWindowRect().width / 3 * 2 - width / 2, top - height };

	ENGINE.SetColor(m_TextColor);

	ENGINE.DrawString(m_YourScore.c_str(), font, yourPos, width, height);

	ENGINE.DrawString(m_HighScore.c_str(), font, highPos, width, height);

}

void HUD::Notify(int score)
{
	m_CurrentScore += score;

	tstringstream yourStream{};
	yourStream << _T("Your Score\n") << std::setfill(_T('0')) << std::setw(6) << to_tstring(m_CurrentScore);
	m_YourScore = yourStream.str();
}

void HUD::OnSubjectDestroy()
{
}

int HUD::GetHudHeight()
{
	return m_HudHeight;
}