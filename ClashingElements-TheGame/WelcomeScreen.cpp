#include "WelcomeScreen.h"
#include "GlobalFont.h"

WelcomeScreen::WelcomeScreen(Game& game):
	Screen{},
	m_pPopScreen{std::make_unique<PopScreenCommand>(game)}

{
}

void WelcomeScreen::Draw() const
{
	const auto& wndwRect = ENGINE.GetWindowRect();
	const int margin = 50;
	const RectInt destRect{ margin, margin, wndwRect.width - margin * 2, wndwRect.height - margin * 2 };

	ENGINE.SetColor(RGB(0, 0, 0), 0.3f);
	ENGINE.FillRectangle(wndwRect);
	ENGINE.SetColor(RGB(0, 0, 0), 0.5f);
	ENGINE.FillRectangle(destRect);

	auto& font = globalFont::GetFont();
	font.SetTextFormat(7, true, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Center);

	ENGINE.SetColor(RGB(0, 0, 0));
	ENGINE.DrawRectangle(destRect);
	ENGINE.SetColor(RGB(255, 255, 255));
	ENGINE.DrawString(
		_T("Glarfius has taken over!\n\nTry to collect as many items as you can while avoiding Glarfius and his Gloobtroopers.\n\nPress ESC while playing to view the controls.\nPress SPACE to start.\n\nGood luck!"),
		font,
		destRect.left + 5,
		destRect.bottom + 5,
		destRect.width - 10,
		destRect.height - 10);
}

void WelcomeScreen::Tick()
{
}

void WelcomeScreen::KeyInput(int virtualKeyCode)
{
	switch (virtualKeyCode)
	{
	case VK_SPACE:
		m_pPopScreen->Execute();
		break;
	}
}
