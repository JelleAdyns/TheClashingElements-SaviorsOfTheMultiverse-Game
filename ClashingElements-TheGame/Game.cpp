#include "pch.h"
#include "Game.h"
#include "SkinScreen.h"
#include <utils.h>
#include <iostream>


int BaseGame::m_Scale{4};

Game::Game( const Window& window ) 
	:BaseGame{ window }
{

	Initialize();

}

Game::~Game( )
{
	Cleanup( );

}

void Game::Initialize( )
{
	m_pScreen = new SkinScreen{ Point2f{GetViewPort().width / 2, 0},"", GetViewPort() };
	m_pLevel = nullptr;
	
}

void Game::Cleanup( )
{
	
	delete m_pScreen;
	m_pScreen = nullptr;
	if (m_pLevel != nullptr)
	{
		delete m_pLevel;
		m_pLevel = nullptr;
	}
}

void Game::Update( float elapsedSec )
{
	switch (m_GameState)
	{
	case Game::GameState::Start:
		break;
	case Game::GameState::ShowingHighScores:
		break;
	case Game::GameState::SelectingSkin:
		m_pScreen->Update(elapsedSec);
		break;
	case Game::GameState::Playing:
		m_pLevel->Update(elapsedSec);
		break;
	case Game::GameState::GameOver:
		break;
	default:
		break;
	}

	
}

void Game::Draw( ) const
{

	ClearBackground();
	switch (m_GameState)
	{
	case Game::GameState::Start:
		break;
	case Game::GameState::ShowingHighScores:
		break;
	case Game::GameState::SelectingSkin:
		m_pScreen->Draw();
		break;
	case Game::GameState::Playing:
		glPushMatrix();
		//glScalef( m_Scale,m_Scale, 1 );
		m_Camera.Transform(m_pLevel->GetPlayerPos());
		//utils::DrawRect(1, 1, 1280 - 1, 720 - 1);
		m_pLevel->Draw();
		glPopMatrix();
		break;
	case Game::GameState::GameOver:
		break;
	default:
		break;
	}
	
	
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch (m_GameState)
	{
	case Game::GameState::Start:
		break;
	case Game::GameState::ShowingHighScores:
		break;
	case Game::GameState::SelectingSkin:
		m_pScreen->KeyInput(e);
		switch (e.keysym.sym)
		{
		case SDLK_SPACE:
			m_pLevel = new Level{ static_cast<SkinScreen*>(m_pScreen)->GetCharacter() };
			delete m_pScreen;
			m_pScreen = nullptr;
			m_Camera.SetLevelBoundaries(m_pLevel->GetLevelBoundaries());
			m_GameState = GameState::Playing;
			break;
		}
		break;
	case Game::GameState::Playing:
		break;
	case Game::GameState::GameOver:
		break;
	}
	
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
