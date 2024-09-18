#include "Game.h"
#include "SkinScreen.h"
#include "StartScreen.h"
#include "HighScoreScreen.h"
#include "HighScoreHandling.h"
#include "WelcomeScreen.h"
#include "PauseScreen.h"
#include "GameOverScreen.h"
#include "ResultsScreen.h"
#include "Level.h"

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

	highScoreHandling::RemoveHighScores(highScoreHandling::placeholderName);

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
	if (m_UpdateScreen) HandleEventQueue();
	m_pScreenStack.back().second->Tick();
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

	m_pScreenStack.back().second->KeyInput(virtualKeycode);
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
}

void Game::AddOperationToQueue(ScreenOperation screenOper)
{
	m_ScreenEventQueue.emplace(m_GameState, screenOper);
	m_UpdateScreen = true;
}

void Game::LoadScreen()
{
	Skin skinForLevel{};
	if (m_GameState == GameState::Playing) skinForLevel = static_cast<SkinScreen*>(m_pScreenStack.back().second.get())->GetPlayer();

	for (int i{ static_cast<int>(m_pScreenStack.size() - 1) }; i >= 0; --i)
	{
		m_pScreenStack.at(i).second->OnExit();
	}
	m_pScreenStack.clear();

	switch (m_GameState)
	{
	case GameState::Start:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<StartScreen>(
			std::make_unique<LoadScreenCommand>(*this, GameState::SelectingSkin),
			std::make_unique<PushScreenCommand>(*this, GameState::ShowingHighScores)
		));

		break;

	case GameState::ShowingHighScores:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<HighScoreScreen>(*this));

		break;

	case GameState::SelectingSkin:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<SkinScreen>(*this));

		break;

	case GameState::Playing:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<Level>(*this, skinForLevel));

		break;
	case GameState::Welcome:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<WelcomeScreen>(*this));

		break;
	case GameState::Pause:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<PauseScreen>(*this));

		break;
	case GameState::GameOver:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<GameOverScreen>(*this));

		break;

	case GameState::Results:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<ResultsScreen>(*this));

		break;
	}

	m_pScreenStack.back().second->OnEnter();

	m_UpdateScreen = false;
}
void Game::PushScreen()
{
	m_pScreenStack.back().second->OnSuspend();
	switch (m_GameState)
	{
	case GameState::Start:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<StartScreen>(
			std::make_unique<LoadScreenCommand>(*this, GameState::SelectingSkin),
			std::make_unique<PushScreenCommand>(*this, GameState::ShowingHighScores)
		));

		break;

	case GameState::ShowingHighScores:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<HighScoreScreen>(*this));

		break;

	case GameState::SelectingSkin:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<SkinScreen>(*this));

		break;

	case GameState::Playing:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<Level>(*this, static_cast<SkinScreen*>(m_pScreenStack.back().second.get())->GetPlayer()));

		break;
	case GameState::Welcome:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<WelcomeScreen>(*this));

		break;
	case GameState::Pause:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<PauseScreen>(*this));

		break;
	case GameState::GameOver:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<GameOverScreen>(*this));

		break;
	case GameState::Results:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<ResultsScreen>(*this));

		break;
	}

	m_pScreenStack.back().second->OnEnter();

}

void Game::PopScreen()
{
	m_pScreenStack.back().second->OnExit();

	m_pScreenStack.pop_back();

	m_pScreenStack.back().second->OnResume();
	m_GameState = m_pScreenStack.back().first;
}
void Game::DrawScreens() const
{
	for (const auto& [gameState, pScreen] : m_pScreenStack)
	{
		pScreen->Draw();
	}
}

void Game::HandleEventQueue()
{
	while (not m_ScreenEventQueue.empty())
	{
 		auto [gameState,screenOperation] = m_ScreenEventQueue.front();
		m_ScreenEventQueue.pop();

		switch (screenOperation)
		{
		case Game::ScreenOperation::Set:
			m_GameState = gameState;
			LoadScreen();
			break;
		case Game::ScreenOperation::Push:
			m_GameState = gameState;
			PushScreen();
			break;
		case Game::ScreenOperation::Pop:
			PopScreen();
			break;
		}
	}

	m_UpdateScreen = false;
}
