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

	m_DefaultSpeed{ Tile::Size * 4 },
	m_Speed{ 0 },

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
		int speed{ m_DefaultSpeed + (m_Dir == Direction::Down ? -m_Speed : m_Speed)};
		if (m_TargetXLocation != m_BottomCenter.x)
		{
			m_Pos.x = Lerp<float>(m_Pos.x, float(m_TargetXLocation), speed * elapsedSec);
			m_BottomCenter.x = round(m_Pos.x);

			if (m_BottomCenter.x == m_TargetXLocation) m_IsMoving = false;
		}

		if (m_TargetYLocation != m_BottomCenter.y)
		{
			m_Pos.y = Lerp<float>(m_Pos.y, float(m_TargetYLocation), speed * elapsedSec);
			m_BottomCenter.y = round(m_Pos.y);

			if (m_BottomCenter.y == m_TargetYLocation) m_IsMoving = false;
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

		if (pStates[SDL_SCANCODE_LEFT])
		{
			int targetX{};
			if (graph.HasNeighbourInDirection(Vector2f{ -1,0 }, m_BottomCenter, targetX))
			{
				if (m_TargetYLocation == m_BottomCenter.y)
				{
					m_Dir = Direction::Left;
					m_IsMoving = true;
					m_TargetXLocation = targetX;
				}
			}
		}
		if (pStates[SDL_SCANCODE_RIGHT])
		{
			int targetX{};
			if (graph.HasNeighbourInDirection(Vector2f{ 1,0 }, m_BottomCenter, targetX))
			{
				if (m_TargetYLocation == m_BottomCenter.y)
				{
					m_Dir = Direction::Right;
					m_IsMoving = true;
					m_TargetXLocation = targetX;
				}
			}
		}
		if (pStates[SDL_SCANCODE_DOWN])
		{
			int targetY{};
			if (graph.HasNeighbourInDirection(Vector2f{ 0, -1 }, m_BottomCenter, targetY))
			{
				if (m_TargetXLocation == m_BottomCenter.x)
				{
					m_Dir = Direction::Down;
					m_IsMoving = true;
					m_TargetYLocation = targetY;
				}
			}
		}
		if (pStates[SDL_SCANCODE_UP] )
		{
			int targetY{};
			if (graph.HasNeighbourInDirection(Vector2f{ 0, 1 }, m_BottomCenter, targetY))
			{
				if (m_TargetXLocation == m_BottomCenter.x)
				{
					m_Dir = Direction::Up;
					m_IsMoving = true;
					m_TargetYLocation = targetY;
				}
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
void Character::SetSpeed(int newSpeed)
{
	m_Speed = newSpeed;
}
void Character::Play()
{
	m_State = CharacterState::Playing;
}