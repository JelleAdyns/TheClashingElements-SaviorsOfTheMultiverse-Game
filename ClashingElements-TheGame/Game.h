#pragma once
#include "BaseGame.h"
#include "Level.h"
#include "Camera.h"
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
	Camera m_Camera{ GetViewPort().width , GetViewPort().height};
	Screen* m_pScreen;

	
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};