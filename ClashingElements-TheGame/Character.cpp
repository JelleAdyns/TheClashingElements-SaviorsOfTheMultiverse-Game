#include "pch.h"
#include "Character.h"
#include "MyUtils.h"
#include "Tile.h"
#include <Texture.h>
#include <iostream>

Character::Character( const Skin& skin) :
	AnimatedSprite{ Point2f{}, 8, 32, 1.f / 20 },
	
	m_State{CharacterState::ChoosingSkin},
	m_Dir{ Direction::Down },
	m_HitBox{ Circlef{Point2f{}, 6} },
	m_Pos{},

	m_Speed{ Tile::Size * 4 },

	m_TargetXLocation{ 0 },
	m_TargetYLocation{ 0 },

	m_IsMoving{ false }
{
	if (skin == Skin::Finn) m_pTexture = new Texture{ "Finn.png" };
	else if (skin == Skin::Wesley) m_pTexture = new Texture{ "Wesley.png" };
	
	AnimatedSprite::SetTexture(m_pTexture);
}
Character::~Character()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Character::Update(float elapsedSec)
{

	m_PassedTime += elapsedSec;
	if (m_PassedTime >= m_FrameTime)
	{
		if (m_State == CharacterState::Playing)
		{
			if (m_IsMoving) ++m_CurrentCol %= m_NrOfCols;
			else ResetFrames();
		}
		else
		{
			++m_CurrentCol %= m_NrOfCols;
		}
			
		m_PassedTime = 0.f;
	}

	if (m_State == CharacterState::Playing)
	{
		if (m_TargetXLocation != m_BottomCenter.x)
		{
			if (m_TargetXLocation < m_BottomCenter.x) m_Dir = Direction::Left;
			else m_Dir = Direction::Right;

			m_Pos.x = Lerp<float>(m_Pos.x, float(m_TargetXLocation), m_Speed * elapsedSec);
			m_BottomCenter.x = round(m_Pos.x);
			std::cout << m_BottomCenter.x << std::endl;
			if (m_BottomCenter.x == m_TargetXLocation)
			{
				//m_BottomCenter.x = float(round(m_BottomCenter.x));
				m_IsMoving = false;
			}
		}

		if (m_TargetYLocation != m_BottomCenter.y)
		{
			if (m_TargetYLocation < m_BottomCenter.y) m_Dir = Direction::Down;
			else m_Dir = Direction::Up;

			m_Pos.y = Lerp<float>(m_Pos.y, float(m_TargetYLocation), m_Speed * elapsedSec);
			m_BottomCenter.y = round(m_Pos.y);
			if (m_BottomCenter.y == m_TargetYLocation)
			{
				//m_BottomCenter.y = float(round(m_BottomCenter.y));
				m_IsMoving = false;
			}
		}

		m_HitBox.center = m_BottomCenter;

		m_CurrentRow = int(m_Dir);
	}
}
void Character::Move(const PathGraph& graph)
{
	if (m_State == CharacterState::Playing)
	{
		const Uint8* pStates = SDL_GetKeyboardState(nullptr);

		if (pStates[SDL_SCANCODE_LEFT] && !m_IsMoving)
		{
			int targetX{};
			if (graph.HasNeighbourInDirection(Vector2f{ -1,0 }, m_HitBox.center, targetX))
			{
				m_IsMoving = true;
				m_TargetXLocation = targetX;
				std::cout << "left" << std::endl;
			}
		}
		if (pStates[SDL_SCANCODE_RIGHT] && !m_IsMoving)
		{
			int targetX{};
			if (graph.HasNeighbourInDirection(Vector2f{ 1,0 }, m_HitBox.center, targetX))
			{
				m_IsMoving = true;
				m_TargetXLocation = targetX;
				std::cout << "right" << std::endl;
			}
		}
		if (pStates[SDL_SCANCODE_DOWN] && !m_IsMoving)
		{
			int targetY{};
			if (graph.HasNeighbourInDirection(Vector2f{ 0, -1 }, m_HitBox.center, targetY))
			{
				m_IsMoving = true;
				m_TargetYLocation = targetY;
				std::cout << "down" << std::endl;
			}
		}
		if (pStates[SDL_SCANCODE_UP] && !m_IsMoving)
		{
			int targetY{};
			if (graph.HasNeighbourInDirection(Vector2f{ 0, 1 }, m_HitBox.center, targetY))
			{
				m_IsMoving = true;
				m_TargetYLocation = targetY;
				std::cout << "up" << std::endl;
			}
		}
	}
}

void Character::ResetFrames()
{
	m_CurrentCol = 0;
}
Circlef Character::GetHitBox() const
{
	return m_HitBox;
}
bool Character::IsMoving() const
{
	return m_IsMoving;
}
void Character::SetPos(const Point2f& newPos)
{
	m_BottomCenter = newPos;
	m_HitBox.center = newPos;
	m_Pos = newPos;
	m_TargetXLocation = int(newPos.x);
	m_TargetYLocation = int(newPos.y);
}
void Character::Play()
{
	m_State = CharacterState::Playing;
}

//#include "pch.h"
//#include "Character.h"
//#include "MyUtils.h"
//#include "Tile.h"
//#include <iostream>
//
//Character::Character(const Point2f& bottomCenter, const Texture* pTexture) :
//	AnimatedSprite{ bottomCenter, 8, 32, 1.f / 20 },
//	m_Dir{ Direction::Down },
//	m_State{ CharacterState::ChoosingSkin }
//{
//	m_pTexture = pTexture;
//	AnimatedSprite::SetTexture(m_pTexture);
//}
//Character::~Character()
//{
//	delete m_pTexture;
//	m_pTexture = nullptr;
//}
//
//void Character::Update(float elapsedSec)
//{
//	m_CurrentRow = int(m_Dir);
//
//	m_PassedTime += elapsedSec;
//	if (m_PassedTime >= m_FrameTime)
//	{
//		if (m_State == CharacterState::Playing)
//		{
//			if (m_IsMoving) ++m_CurrentCol %= m_NrOfCols;
//			else ResetFrames();
//		}
//		else
//		{
//			++m_CurrentCol %= m_NrOfCols;
//		}
//		
//		m_PassedTime = 0.f;
//	}
//
//}
//
//void Character::ResetFrames()
//{
//	m_CurrentCol = 0;
//}
//bool Character::IsMoving() const
//{
//	return m_IsMoving;
//}
//void Character::SetIsMoving(bool isMoving)
//{
//	m_IsMoving = isMoving;
//}
//void Character::SetDir(const Direction& newDir)
//{
//	m_Dir = newDir;
//}
//void Character::SetPos(const Point2f& newPos)
//{
//	m_BottomCenter = newPos;
//}