#include "Game.h"
#include "SkinScreen.h"
#include "StartScreen.h"
#include "HighScoreScreen.h"
#include "HighScoreHandling.h"

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
	ENGINE.SetWindowDimensions(256,256);
	ENGINE.SetFrameRate(60);

	LoadScreen();

#ifdef _DEBUG
	AudioLocator::RegisterAudioService(std::make_unique<LogAudio>(std::make_unique<Audio>()));
#else
	AudioLocator::RegisterAudioService(std::make_unique<Audio>());
#endif // _DEBUG

	globalFont::InitFont();

	//highScoreHandling::WriteHighScores(_T("BOB"), 20);

}
void Game::Draw() const
{
	
	switch (m_GameState)
	{

	case GameState::Playing:

#ifdef _DEBUG


		ENGINE.PushTransform();
		if (m_DebugScale)
		{
			ENGINE.Scale(0.25f, ENGINE.GetWindowRect().width / 2, ENGINE.GetWindowRect().height / 2);
		}
		DrawScreens();

		ENGINE.PopTransform();

#else

		DrawScreens();

#endif // _DEBUG

		break;
	default:
		DrawScreens();
		break;
	}

}
void Game::Tick()
{
	if (m_UpdateScreen) LoadScreen();
	m_pScreenStack.back()->Tick();
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

	m_pScreenStack.back()->KeyInput(virtualKeycode);
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
	Skin skinForLevel{};
	if (m_GameState == GameState::Playing) skinForLevel = static_cast<SkinScreen*>(m_pScreenStack.back().get())->GetPlayer();

	for (int i{ static_cast<int>(m_pScreenStack.size() - 1) }; i >= 0; --i)
	{
		m_pScreenStack.at(i)->OnExit();
	}
	m_pScreenStack.clear();

	switch (m_GameState)
	{
	case GameState::Start:

		m_pScreenStack.emplace_back(std::make_unique<StartScreen>(
			std::make_unique<LoadScreenCommand>(*this, GameState::SelectingSkin),
			std::make_unique<PushScreenCommand>(*this, GameState::ShowingHighScores)
		));

		break;

	case GameState::ShowingHighScores:

		m_pScreenStack.emplace_back(std::make_unique<HighScoreScreen>(*this));

		break;

	case GameState::SelectingSkin:

		m_pScreenStack.emplace_back(std::make_unique<SkinScreen>(*this, GameState::Playing));

		break;

	case GameState::Playing:

		m_pScreenStack.emplace_back(std::make_unique<Level>(skinForLevel));

		break;

	case GameState::GameOver:
		break;
	}

	m_pScreenStack.back()->OnEnter();

	m_UpdateScreen = false;
}
void Game::PushScreen(GameState newScreen)
{
	m_GameState = newScreen;
	m_pScreenStack.back()->OnSuspend();
	switch (m_GameState)
	{
	case GameState::Start:

		m_pScreenStack.emplace_back(std::make_unique<StartScreen>(
			std::make_unique<LoadScreenCommand>(*this, GameState::SelectingSkin),
			std::make_unique<PushScreenCommand>(*this, GameState::ShowingHighScores)
		));

		break;

	case GameState::ShowingHighScores:

		m_pScreenStack.emplace_back(std::make_unique<HighScoreScreen>(*this));

		break;

	case GameState::SelectingSkin:

		m_pScreenStack.emplace_back(std::make_unique<SkinScreen>(*this, GameState::Playing));

		break;

	case GameState::Playing:

		m_pScreenStack.emplace_back(std::make_unique<Level>(static_cast<SkinScreen*>(m_pScreenStack.back().get())->GetPlayer()));

		break;

	case GameState::GameOver:
		break;
	}

	m_pScreenStack.back()->OnEnter();

	m_UpdateScreen = false;
}

void Game::PopScreen()
{
	m_pScreenStack.back()->OnExit();

	m_pScreenStack.pop_back();

	m_pScreenStack.back()->OnResume();

	m_UpdateScreen = false;
}
void Game::DrawScreens() const
{
	for (const auto& pScreen : m_pScreenStack)
	{
		pScreen->Draw();
	}
}
