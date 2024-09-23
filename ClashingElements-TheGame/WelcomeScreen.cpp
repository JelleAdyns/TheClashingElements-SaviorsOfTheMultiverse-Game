#include "WelcomeScreen.h"
#include "GameFont.h"

WelcomeScreen::WelcomeScreen(Game& game):
	Screen{},
	m_pPopScreen{std::make_unique<PopScreenCommand>(game)}

{
}

void WelcomeScreen::Draw() const
{
	const auto& wndwRect = ENGINE.GetWindowRect();
	constexpr int margin = 50;
	constexpr int textMargin = 5;
	const RectInt destRect{ margin, margin, wndwRect.width - margin * 2, wndwRect.height - margin * 2 };

	ENGINE.SetColor(RGB(0, 0, 0), 0.3f);
	ENGINE.FillRectangle(wndwRect);
	ENGINE.SetColor(RGB(0, 0, 0), 0.5f);
	ENGINE.FillRectangle(destRect);

	auto& font = gameFont::GetFont();
	font.SetTextFormat(7, true, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Center);

	ENGINE.SetColor(RGB(0, 0, 0));
	ENGINE.DrawRectangle(destRect);
	ENGINE.SetColor(RGB(255, 255, 255));
	ENGINE.DrawString(
		_T("Glarfius has taken over!\n\nTry to collect as many items as you can while avoiding Glarfius and his Gloobtroopers.\n\n") + 
		m_ButtonsText.GetActiveString() + 
		_T("Good luck!"),
		font,
		destRect.left + textMargin,
		destRect.bottom + textMargin,
		destRect.width - textMargin*2,
		destRect.height - textMargin*2);
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

void WelcomeScreen::HandleControllerInput()
{
	if (ENGINE.ButtonDownThisFrame(Controller::Button::A, 0))
	{
		m_pPopScreen->Execute();
	}
}
