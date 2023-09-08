#include "pch.h"
#include "Character.h"
#include "MyUtils.h"
#include "Tile.h"
#include <Texture.h>
#include <iostream>

int	Character::m_DefaultSpeed{ Tile::Size * 4 };
const int Character::m_PixelOffset{1};

Character::Character(const Skin& skin) :
	AnimatedSprite{ Point2f{}, 8, 32, 1.f / 20, false },

	m_State{ CharacterState::ChoosingSkin },
	m_Dir{ Direction::Down },
	m_HitBox{ Circlef{Point2f{}, 6} },
	m_Pos{},

	m_Velocity{ Vector2f{0,0} },

	m_TargetXLocation{ 0 },
	m_TargetYLocation{ 0 },

	m_IsMoving{ false }
{
	switch (skin)
	{
	case Skin::Finn:
		m_pTexture = new Texture{ "Finn.png" };
		break;
	case Skin::Wesley:
		m_pTexture = new Texture{ "Wesley.png" };
		break;
	}
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
		//int speed{ m_DefaultSpeed + (m_Dir == Direction::Down ? -m_Speed : m_Speed)};
		if (m_TargetXLocation != m_BottomCenter.x && m_IsMoving)
		{
			//m_Pos.x = Lerp<float>(m_Pos.x, float(m_TargetXLocation), speed * elapsedSec);
			if (m_TargetXLocation < m_BottomCenter.x) m_Velocity.x = float(-m_DefaultSpeed);
			else m_Velocity.x = float(m_DefaultSpeed);

			UpdatePos(m_Velocity, elapsedSec);

			if (m_BottomCenter.x == m_TargetXLocation) m_IsMoving = false;
		}
		else m_Velocity.x = 0;

		if (m_TargetYLocation != m_BottomCenter.y && m_IsMoving)
		{
			//m_Pos.y = Lerp<float>(m_Pos.y, float(m_TargetYLocation), speed * elapsedSec);

			if (m_TargetYLocation < m_BottomCenter.y) m_Velocity.y = float(-m_DefaultSpeed);
			else m_Velocity.y = float(m_DefaultSpeed);
		

			UpdatePos(m_Velocity, elapsedSec);

			if (m_BottomCenter.y == m_TargetYLocation) m_IsMoving = false;
		}
		else m_Velocity.y = 0;

		m_CurrentRow = int(m_Dir);
	}
}
void Character::Move(const PathGraph& graph, float elapsedSec)
{
	if (m_State == CharacterState::Playing)
	{
		const Uint8* pStates = SDL_GetKeyboardState(nullptr);

		if (pStates[SDL_SCANCODE_LEFT] && !pStates[SDL_SCANCODE_RIGHT])
		{
			int targetX{};
			if (graph.HasNeighbourInDirection(Direction::Left, m_BottomCenter, targetX))
			{
				if (m_TargetYLocation == m_BottomCenter.y)
				{
					m_Dir = Direction::Left;
					m_IsMoving = true;
					m_TargetXLocation = targetX;
				}
			}
		}
		if (pStates[SDL_SCANCODE_RIGHT] && !pStates[SDL_SCANCODE_LEFT])
		{
			int targetX{};
			if (graph.HasNeighbourInDirection(Direction::Right, m_BottomCenter, targetX))
			{
				if (m_TargetYLocation == m_BottomCenter.y)
				{
					m_Dir = Direction::Right;
					m_IsMoving = true;
					m_TargetXLocation = targetX;
				}
			}
		}
		if (pStates[SDL_SCANCODE_DOWN] && !pStates[SDL_SCANCODE_UP])
		{
			int targetY{};
			if (graph.HasNeighbourInDirection(Direction::Down, m_BottomCenter, targetY))
			{
				if (m_TargetXLocation == m_BottomCenter.x)
				{
					m_Dir = Direction::Down;
					m_IsMoving = true;
					m_TargetYLocation = targetY - m_PixelOffset;
				}
			}
		}
		if (pStates[SDL_SCANCODE_UP] && !pStates[SDL_SCANCODE_DOWN])
		{
			int targetY{};
			if (graph.HasNeighbourInDirection(Direction::Up, m_BottomCenter, targetY))
			{
				if (m_TargetXLocation == m_BottomCenter.x)
				{
					m_Dir = Direction::Up;
					m_IsMoving = true;
					m_TargetYLocation = targetY - m_PixelOffset;
				}
			}
		}

		int targetY{};
		UpdatePos(Vector2f{ 0, graph.GetEscalatorVelocity(m_BottomCenter, targetY) }, elapsedSec);
		if (targetY != 0)
		{
			if (targetY > m_BottomCenter.y) m_Dir = Direction::Up;
			else m_Dir = Direction::Down;

			m_IsMoving = true;
			m_TargetYLocation = targetY - m_PixelOffset;
			
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
	Point2f pos{ newPos.x, newPos.y - m_PixelOffset };
	m_BottomCenter = pos;
	m_HitBox.center = pos;
	m_Pos = pos;
	m_TargetXLocation = int(pos.x);
	m_TargetYLocation = int(pos.y);
	m_IsMoving = false;
}
void Character::UpdatePos(const Vector2f& newVelocity, float elapsedSec)
{
	m_Pos.x += newVelocity.x * elapsedSec;
	m_BottomCenter.x = round(m_Pos.x);
	m_Pos.y += newVelocity.y * elapsedSec;
	m_BottomCenter.y = round(m_Pos.y);

	m_HitBox.center = m_BottomCenter;
}
void Character::Play()
{
	m_State = CharacterState::Playing;
}