#include "pch.h"
#include "Button.h"
#include <utils.h>


Button::Button(const std::string& text, const Point2f& center, std::function<void()> toExecute, bool isSelected):
	m_IsSelected{isSelected},
	m_Center{center},
	m_FuncToExecute{toExecute}
	//m_NextGameState{nextGameState}
{
	int borderDistance{ 5 };
	m_pText = new Texture{ text, GlobalFont::Get().GetFont(), Color4f{1.f,1.f,1.f,1.f} };
	const_cast<Rectf&>(m_Border) = Rectf{ center.x - m_pText->GetWidth()/2 - borderDistance,
										  center.y - m_pText->GetHeight()/2 - borderDistance,
										  m_pText->GetWidth() + 2 * borderDistance,
										  m_pText->GetHeight() + 2 * borderDistance };
	
}
//Button::Button(const Texture* texture, const Point2f& center, std::function<void()> toExecute, bool isSelected = false):
//	m_IsSelected{ isSelected },
//	m_Center{ center },
//	m_FuncToExecute{ toExecute }
//{
//	m_pText = texture;
//}
Button::~Button()
{
	delete m_pText;
	m_pText = nullptr;
}

void Button::Draw() const
{
	glPushMatrix();
	glTranslatef(m_Center.x, m_Center.y, 0);
	glScalef(0.5f, 0.5f, 1.f);
	glTranslatef(-m_Center.x, -m_Center.y, 0);
	m_pText->Draw(Point2f{ m_Center.x - m_pText->GetWidth() / 2, m_Center.y - m_pText->GetHeight() / 2 });
	if(m_IsSelected) utils::DrawRect(m_Border, 2.f);
	glPopMatrix();
}

void Button::ToggleSelection()
{
	m_IsSelected = !m_IsSelected;
}