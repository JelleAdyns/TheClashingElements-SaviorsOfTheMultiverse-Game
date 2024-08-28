#include "Game.h"
#include "SkinScreen.h"
#include "StartScreen.h"

Game::Game()
{
	
}
Game::~Game()
{

}
void Game::Initialize()
{
	BaseGame::Initialize();

	ENGINE.SetTitle(_T("The Clashing Elements - The Game"));
	ENGINE.SetWindowScale(3.f);
	ENGINE.SetWindowDimensions(256,224);
	ENGINE.SetFrameRate(60);

	SetScreen(GameState::Start);
	LoadScreen();

}
void Game::Draw() const
{
	
	switch (m_GameState)
	{
	case GameState::Start:
	case GameState::ShowingHighScores:
	case GameState::SelectingSkin:
		m_pScreen->Draw();
		break;
	case GameState::Playing:

#ifdef _DEBUG


		ENGINE.PushTransform();
		if (m_DebugScale)
		{
			ENGINE.Scale(0.25f, ENGINE.GetWindowRect().width / 2, ENGINE.GetWindowRect().height / 2);
		}
		m_pScreen->Draw();

		ENGINE.PopTransform();

#else

		m_pScreen->Draw();

#endif // _DEBUG

		break;
	case GameState::GameOver:
		break;
	}

}
void Game::Tick()
{
	if (m_UpdateScreen) LoadScreen();
		m_pScreen->Tick();
}
void Game::KeyDown(int virtualKeycode)
{
	// Numbers and letters from '0' to '9' and 'A' to 'Z' are represented by their ASCII values
	// For example: if(virtualKeycode == 'B')
	// BE CAREFULL! Don't use lower caps, because those have different ASCII values
	//
	// Other keys are checked with their virtual Keycode defines
	// For example: if(virtualKeycode == VK_MENU)
	// VK_MENU represents the 'Alt' key
	//
	// Click here for more information: https://learn.microsoft.com/en-us/windows/win32/learnwin32/keyboard-input

		m_pScreen->KeyInput(virtualKeycode);
	switch (m_GameState)
	{

	case GameState::Playing:

		switch (virtualKeycode)
		{
		case 'S':
			m_DebugScale = !m_DebugScale;
			break;
		}
		break;

	}
}
void Game::KeyUp(int virtualKeycode)
{
	// Numbers and letters from '0' to '9' and 'A' to 'Z' are represented by their ASCII values
	// For example: if(virtualKeycode == 'B')
	// BE CAREFULL! Don't use lower caps, because those have different ASCII values
	//
	// Other keys are checked with their virtual Keycode defines
	// For example: if(virtualKeycode == VK_MENU)
	// VK_MENU represents the 'Alt' key
	//
	// Click here for more information: https://learn.microsoft.com/en-us/windows/win32/learnwin32/keyboard-input

}
void Game::MouseDown(bool isLeft, int x, int y)
{

}
void Game::MouseUp(bool isLeft, int x, int y)
{
	
}
void Game::MouseMove(int x, int y, int keyDown)
{
	//See this link to check which keys could be represented in the keyDown parameter
	//https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-mousemove
}
void Game::MouseWheelTurn(int x, int y, int turnDistance, int keyDown)
{
	//See this link to check which keys could be represented in the keyDown parameter and what the turnDistance is for
	//https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-mousewheel
}



void Game::SetScreen(GameState newGameState)
{
	m_GameState = newGameState;
	m_UpdateScreen = true;
}

void Game::LoadScreen()
{
	switch (m_GameState)
	{
	case GameState::Start:

		m_pScreen = std::make_unique<StartScreen>(
			L"Space.png",
			std::make_unique<LoadScreenCommand>(*this, GameState::SelectingSkin),
			std::make_unique<LoadScreenCommand>(*this, GameState::ShowingHighScores)
		);
		m_GameState = GameState::Start;

		break;

	case GameState::ShowingHighScores:
		break;

	case GameState::SelectingSkin:

		m_pScreen = std::make_unique<SkinScreen>(L"Space.png", *this, GameState::Playing);
		m_GameState = GameState::SelectingSkin;

		break;

	case GameState::Playing:

		m_pScreen = std::make_unique<Level>(static_cast<SkinScreen*>(m_pScreen.get())->GetPlayer());
		m_GameState = GameState::Playing;

		break;

	case GameState::GameOver:
		break;
	}

	m_UpdateScreen = false;
}
