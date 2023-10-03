#include "pch.h"
#include "Player.h"

int	Player::m_DefaultSpeed{ Tile::Size * 4 };
const int Player::m_PixelOffset{ 1 };

Player::Player(const Skin& skin):
	Character{ Point2f{}, 8, 32, 1.f / 20 },
	m_State{ PlayerState::ChoosingSkin },
	m_pTexture{nullptr}
{
	Character::SetDefaultSpeed(m_DefaultSpeed);
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
Player::~Player()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Player::Update(float elapsedSec)
{

	m_PassedTime += elapsedSec;
	if (m_PassedTime >= m_FrameTime)
	{
		if (m_State == PlayerState::Playing)
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

	if (m_State == PlayerState::Playing)
	{
		Character::Update(elapsedSec);
	}
}
void Player::Move(const PathGraph& graph, float elapsedSec)
{
	if (m_State == PlayerState::Playing)
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
					m_CurrentRow = int(m_Dir);
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
					m_CurrentRow = int(m_Dir);
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
					m_CurrentRow = int(m_Dir);
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
					m_CurrentRow = int(m_Dir);
					m_IsMoving = true;
					m_TargetYLocation = targetY - m_PixelOffset;
				}
			}
		}
	}
}
void Player::ResetFrames()
{
	m_CurrentCol = 0;
}
void Player::Play()
{
	m_State = PlayerState::Playing;
}
void Player::SetPos(const Point2f& newPos)
{
	Point2f pos{ newPos.x, newPos.y - m_PixelOffset };
	Character::SetPos(pos);
}
//void Player::InteractWithMobilityItem(const MobilityItem& mobilityItem)
//{
//
//}