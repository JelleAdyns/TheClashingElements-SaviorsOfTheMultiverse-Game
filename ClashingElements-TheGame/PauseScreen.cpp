#include "PauseScreen.h"
#include "GameFont.h"

PauseScreen::PauseScreen(Game& game) :
	Screen{},
	m_pPopScreen{ std::make_unique<PopScreenCommand>(game) },
	m_pLoadTitleScreen{std::make_unique<LoadScreenCommand>(game, GameState::Start) }
{
}

void PauseScreen::Draw() const
{
	const auto& wndwRect = ENGINE.GetWindowRect();
	constexpr int margin = 40;
	constexpr int textMargin = 5;
	constexpr int height = 80;
	const RectInt destRect{ margin, (wndwRect.height - height) / 2, wndwRect.width - margin * 2, height };

	ENGINE.SetColor(RGB(0, 0, 0), 0.3f);
	ENGINE.FillRectangle(wndwRect);
	ENGINE.SetColor(RGB(0, 0, 0), 0.5f);
	ENGINE.FillRectangle(destRect);
	
	const RectInt textDestRect{ destRect.left + textMargin, destRect.bottom + textMargin, destRect.width - textMargin * 2, destRect.height - textMargin * 2 };
	ENGINE.SetColor(RGB(0, 0, 0));
	ENGINE.DrawRectangle(destRect);
	ENGINE.SetColor(RGB(255, 255, 255));

	auto& font = gameFont::GetFont();
	font.SetTextFormat(7, true, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Top);

	ENGINE.DrawString(_T("PAUSE"), font, textDestRect);

	font.SetHorizontalAllignment(Font::HorAllignment::Left);
	font.SetVerticalAllignment(Font::VertAllignment::Center);

	ENGINE.DrawString(m_ControlsText.GetActiveString(), font, textDestRect);

	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Center);

	ENGINE.DrawString(m_ContinueText.GetActiveString(), 
		font, 
		destRect.left + textMargin,
		destRect.bottom + textMargin,
		destRect.width - textMargin * 2);
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
	case VK_BACK:
		m_pLoadTitleScreen->Execute();
		break;
	}
}

void PauseScreen::HandleControllerInput()
{
	if (ENGINE.ButtonDownThisFrame(Controller::Button::Start, 0))
	{
		m_pPopScreen->Execute();
	}
	if (ENGINE.ButtonDownThisFrame(Controller::Button::Y, 0))
	{
		m_pLoadTitleScreen->Execute();
	}
}

void PauseScreen::OnEnter()
{
	AudioLocator::GetAudioService().PauseAllSounds();
}

void PauseScreen::OnExit()
{
	AudioLocator::GetAudioService().ResumeAllSounds();
}
