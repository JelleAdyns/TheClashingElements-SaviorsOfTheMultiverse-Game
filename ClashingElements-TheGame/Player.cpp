#include "Player.h"

int	Player::m_DefaultSpeed{ Tile::Size * 4 };

Player::Player(const Skin& skin):
	Character{ Point2Int{}, 8, 32, 1.f / 20, 1 },
	m_State{ PlayerState::ChoosingSkin },
	m_pTexture{nullptr}
{
	Character::SetDefaultSpeed(m_DefaultSpeed);
	switch (skin)
	{
	case Skin::Finn:
		m_pTexture = std::make_unique<Texture>( L"Finn.png" );
		break;
	case Skin::Wesley:
		m_pTexture = std::make_unique<Texture>(L"Wesley.png");
		break;
	}
	AnimatedSprite::SetTexture(m_pTexture.get());
}
void Player::Update()
{
	switch (m_State)
	{
	case Player::PlayerState::ChoosingSkin:

		m_PassedTime += ENGINE.GetDeltaTime();
		if (m_PassedTime >= m_FrameTime)
		{
			++m_CurrentCol %= m_NrOfCols;
			m_PassedTime = 0.f;
		}

		break;

	case Player::PlayerState::Playing:

		Character::Update();
		if (not m_IsMoving) ResetFrames();

		break;
	}
}
void Player::Move(const PathGraph& graph)
{
	if (m_State == PlayerState::Playing)
	{
		if (ENGINE.IsKeyPressed(VK_LEFT) && !ENGINE.IsKeyPressed(VK_RIGHT))
		{
			Point2Int newTarget{};
			if (graph.HasNeighbourInDirection(Direction::Left, m_BottomCenter, newTarget))
			{
				if (m_TargetLocation.y == m_BottomCenter.y)
				{
					m_Dir = Direction::Left;
					m_CurrentRow = int(m_Dir);
					m_IsMoving = true;
					m_TargetLocation = newTarget;
				}
			}
		}
		if (ENGINE.IsKeyPressed(VK_RIGHT) && !ENGINE.IsKeyPressed(VK_LEFT))
		{
			Point2Int newTarget{};
			if (graph.HasNeighbourInDirection(Direction::Right, m_BottomCenter, newTarget))
			{
				if (m_TargetLocation.y == m_BottomCenter.y)
				{
					m_Dir = Direction::Right;
					m_CurrentRow = int(m_Dir);
					m_IsMoving = true;
					m_TargetLocation = newTarget;
				}
			}
		}
		if (ENGINE.IsKeyPressed(VK_DOWN) && !ENGINE.IsKeyPressed(VK_UP))
		{
			Point2Int newTarget{};
			if (graph.HasNeighbourInDirection(Direction::Down, m_BottomCenter, newTarget))
			{
				if (m_TargetLocation.x == m_BottomCenter.x)
				{
					m_Dir = Direction::Down;
					m_CurrentRow = int(m_Dir);
					m_IsMoving = true;
					m_TargetLocation = newTarget;
				}
			}
		}
		if (ENGINE.IsKeyPressed(VK_UP) && !ENGINE.IsKeyPressed(VK_DOWN))
		{
			Point2Int newTarget{};
			if (graph.HasNeighbourInDirection(Direction::Up, m_BottomCenter, newTarget))
			{
				if (m_TargetLocation.x == m_BottomCenter.x)
				{
					m_Dir = Direction::Up;
					m_CurrentRow = int(m_Dir);
					m_IsMoving = true;
					m_TargetLocation = newTarget;
				}
			}
		}
	}
}

void Player::Play()
{
	m_State = PlayerState::Playing;
}
//void Player::InteractWithMobilityItem(const MobilityItem& mobilityItem)
//{
//
//}