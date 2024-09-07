#include "PauseScreen.h"
#include "GlobalFont.h"

PauseScreen::PauseScreen(Game& game) :
	Screen{},
	m_pPopScreen{ std::make_unique<PopScreenCommand>(game) }

{
}

void PauseScreen::Draw() const
{
	const auto& wndwRect = ENGINE.GetWindowRect();
	constexpr int margin = 50;
	constexpr int textMargin = 5;
	constexpr int height = 100;
	const RectInt destRect{ margin, (wndwRect.height - height) / 2, wndwRect.width - margin * 2, height };

	ENGINE.SetColor(RGB(0, 0, 0), 0.3f);
	ENGINE.FillRectangle(wndwRect);
	ENGINE.SetColor(RGB(0, 0, 0), 0.5f);
	ENGINE.FillRectangle(destRect);

	auto& font = globalFont::GetFont();
	font.SetTextFormat(9, true, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Left);
	font.SetVerticalAllignment(Font::VertAllignment::Center);

	ENGINE.SetColor(RGB(0, 0, 0));
	ENGINE.DrawRectangle(destRect);
	ENGINE.SetColor(RGB(255, 255, 255));
	ENGINE.DrawString(
		_T("Walking:\tARROWS\nShooting:\tSPACE"),
		font,
		destRect.left + textMargin,
		destRect.bottom + textMargin,
		destRect.width - textMargin*2,
		destRect.height - textMargin*2);

	font.SetTextFormat(7, true, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Center);

	ENGINE.DrawString(
		_T("Press ESC to continue."),
		font,
		destRect.left + textMargin,
		destRect.bottom + textMargin,
		destRect.width - textMargin*2);
}

void PauseScreen::Tick()
{
}

void PauseScreen::KeyInput(int virtualKeyCode)
{
	switch (virtualKeyCode)
	{
	case VK_ESCAPE:
		m_pPopScreen->Execute();
		break;
	}
}
