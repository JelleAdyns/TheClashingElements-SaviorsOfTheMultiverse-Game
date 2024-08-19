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

	m_pScreen = std::make_unique<StartScreen>(L"Space.png", ENGINE.GetWindowRect(),
		[&]()
		{
			/*m_GameState = GameState::SelectingSkin;
			m_pScreen.reset(new SkinScreen{ L"Space.png", ENGINE.GetWindowSize(),  []() {} });*/
		},
		[]() {}
	);
	m_pLevel = nullptr;
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

		ENGINE.PushTransform();
		if (m_DebugScale)
		{
			ENGINE.Scale(m_DScale, ENGINE.GetWindowRect().width / 2, ENGINE.GetWindowRect().height / 2);
		}
		m_pLevel->Draw();
		ENGINE.PopTransform();
		break;
	case GameState::GameOver:
		break;
	}

}
void Game::Tick()
{
	switch (m_GameState)
	{
	case GameState::Start:
	case GameState::ShowingHighScores:
	case GameState::SelectingSkin:
		m_pScreen->Tick();
		break;
	case GameState::Playing:
		m_pLevel->Tick();
		break;
	case GameState::GameOver:
		break;
	default:
		break;
	}

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

	switch (m_GameState)
	{
	case GameState::Start:
		m_pScreen->KeyInput(virtualKeycode);
		switch (virtualKeycode)
		{
		case VK_SPACE:
			m_pScreen = std::make_unique<SkinScreen>( L"Space.png", ENGINE.GetWindowRect(), [] (){} );
			//m_pScreen = new SkinScreen{ "Space.png", ENGINE.GetWindowSize() };
			m_GameState = GameState::SelectingSkin;
			break;
		}
		break;

		break;
	case GameState::ShowingHighScores:
		break;
	case GameState::SelectingSkin:
		m_pScreen->KeyInput(virtualKeycode);
		switch (virtualKeycode)
		{
		case VK_SPACE:
			m_pLevel = std::make_unique<Level>(static_cast<SkinScreen*>(m_pScreen.get())->GetPlayer(), ENGINE.GetWindowRect().width, ENGINE.GetWindowRect().height);
			m_pScreen.reset();
			//delete m_pScreen;
			//m_pScreen = nullptr;
			m_GameState = GameState::Playing;
			break;
		}
		break;
	case GameState::Playing:
		switch (virtualKeycode)
		{
		case 'S':
			m_DebugScale = !m_DebugScale;
			break;
		}
		break;
	case GameState::GameOver:
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