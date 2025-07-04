#include "Player.h"
#include "HUD.h"

int	Player::m_DefaultSpeed{ Tile::Size * 4 };

Player::Player(Skin skin, HUD* hudObserver) :
	Character
	{ 
		Point2Int{},						//arg 1
		[&]() {								//arg 2
			switch (skin)
			{
			case Skin::Finn:
				return _T("Finn.png");
				break;
			case Skin::Wesley:
				return _T("Wesley.png");
				break;
			default:
				return _T("");
				break;
			}
		}(),
		SpriteInfo{.nrOfCols{8}, .nrOfFrames{32},.frameTime{1.f/15}},	//arg 3
		1		//arg 4
	},
	m_State{ PlayerState::ChoosingSkin },
	m_pTookDamage{std::make_unique<Subject<Player*>>()}
{
	Character::SetDefaultSpeed(m_DefaultSpeed);

	if(hudObserver) m_pTookDamage->AddObserver(hudObserver);
}
void Player::Update()
{
	switch (m_State)
	{
	case Player::PlayerState::ChoosingSkin:

		AnimatedSprite::Update();

		break;

	case Player::PlayerState::Playing:

		Character::Update();
		if (not m_IsMoving) ResetFrames();
		if (m_IsInvincible) UpdateInvincibility();

		break;
	}
}
void Player::Draw() const
{
	if(m_NeedsToDraw) Character::Draw();

#ifdef _DEBUG
	ENGINE.SetColor(RGB(255, 0, 255));
	ENGINE.DrawVector(m_BottomCenter, m_Velocity, 10);
#endif // __DEBUG

}

void Player::Move(const PathGraph& graph)
{
	if (m_State == PlayerState::Playing)
	{
		if ((ENGINE.IsKeyPressed(VK_LEFT) and not ENGINE.IsKeyPressed(VK_RIGHT)) or
			(ENGINE.ButtonPressed(Controller::Button::DpadLeft, 0) and not ENGINE.ButtonPressed(Controller::Button::DpadRight, 0)))
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
		if ((ENGINE.IsKeyPressed(VK_RIGHT) and not ENGINE.IsKeyPressed(VK_LEFT)) or
			(ENGINE.ButtonPressed(Controller::Button::DpadRight, 0) and not ENGINE.ButtonPressed(Controller::Button::DpadLeft, 0)))
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
		if ((ENGINE.IsKeyPressed(VK_DOWN) and not ENGINE.IsKeyPressed(VK_UP)) or
			(ENGINE.ButtonPressed(Controller::Button::DpadDown, 0) and not ENGINE.ButtonPressed(Controller::Button::DpadUp, 0)))
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
		if ((ENGINE.IsKeyPressed(VK_UP) and not ENGINE.IsKeyPressed(VK_DOWN)) or
			(ENGINE.ButtonPressed(Controller::Button::DpadUp, 0) and not ENGINE.ButtonPressed(Controller::Button::DpadDown, 0)))
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
void Player::TakeDamage()
{
	if(not m_IsInvincible)
	{
		m_pTookDamage->NotifyObservers(this);
		m_IsInvincible = true;
		m_NeedsToDraw = false;
	}
}

void Player::Respawn(const Point2Int& pos)
{
	ResetFrames();
	m_CurrentRow = 0;
	SetPos(pos);
}

void Player::UpdateInvincibility()
{
	auto dt = ENGINE.GetDeltaTime();

 	m_DrawTimer += dt;
	if (m_DrawTimer >= m_DrawTimeSteps)
	{
		m_NeedsToDraw = !m_NeedsToDraw;
		m_DrawTimer -= m_DrawTimeSteps;
	}

	m_InvincibleTimer += dt;
	if (m_InvincibleTimer >= m_MaxInvincibleTime)
	{
		m_IsInvincible = false;
		m_InvincibleTimer = 0.f;
		m_DrawTimer = 0.f;
		m_NeedsToDraw = true;
	}
}
