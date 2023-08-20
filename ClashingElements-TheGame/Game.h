#pragma once
#include "BaseGame.h"
#include "Level.h"

#include "Screen.h"
#include <vector>


class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;


	
private:

	enum class GameState
	{
		Start,
		ShowingHighScores,
		SelectingSkin,
		Playing,
		GameOver
	};

	// VARIABLES

	GameState m_GameState{ GameState::SelectingSkin };
	Level* m_pLevel;
	Screen* m_pScreen;

	bool m_DebugScale{ false };
	float m_DScale{ 0.25f };
	
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};