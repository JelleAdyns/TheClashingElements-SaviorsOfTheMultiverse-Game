#include "pch.h"
#include "Character.h"
#include "Texture.h"
#include "MyUtils.h"


Character::Character(const Point2f& bottomCenter) :
	AnimatedSprite{ bottomCenter, 8, 32, 1.f / 20 }
{
	Texture* characterTexture{ new Texture{"Wesley.png"} };
	AnimatedSprite::SetTexture(characterTexture);
}

void Character::Update(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_DOWN])
	{
		m_Dir = Direction::Down;
		m_BottomCenter.y -= 64 * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_LEFT])
	{
		m_Dir = Direction::Left;
		m_BottomCenter.x -= 64 * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_UP])
	{
		m_Dir = Direction::Up;
		m_BottomCenter.y += 64 * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		m_Dir = Direction::Right;
		m_BottomCenter.x += 64 * elapsedSec;
	}

	m_CurrentRow = int(m_Dir);
	m_PassedTime += elapsedSec;
	if (m_PassedTime >= m_FrameTime)
	{
		//if (m_CurrentCol == m_NrOfCols - 1) ++m_CurrentRow %= m_NrOfRows;
		++m_CurrentCol %= m_NrOfCols;
		m_PassedTime = 0.f;
	}
}

//Point2f Character::GetPos()
//{
//	return m_BottomCenter;
//}