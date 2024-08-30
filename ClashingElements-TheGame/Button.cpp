#include "Button.h"


Button::Button(const tstring& text, const Point2Int& center, std::unique_ptr<Command>&& toExecute, bool isSelected) :
 	m_IsSelected{ isSelected },
	m_Center{ center },
	m_CommandToExecute{ std::move(toExecute) },
	m_Border{},
	m_Text{ text }
{
	int borderDistance{ 5 };
	m_Border = RectInt{ center.x - 200 / 2 - borderDistance,
										  center.y - 16 / 2 - borderDistance,
										  200 + 2 * borderDistance,
										  16 + 2 * borderDistance };

}

void Button::Draw() const
{
	ENGINE.SetColor(m_TextColor);
	ENGINE.DrawString(
		m_Text,
		globalFont::GetFont(), 
		Point2Int{m_Center.x - m_Border.width / 2 , m_Center.y - m_Border.height / 2}, 
		m_Border.width
	);
	if(m_IsSelected) ENGINE.DrawRectangle(m_Border.left - m_BorderDistance, m_Border.bottom - m_BorderDistance, m_Border.width + 2 * m_BorderDistance, m_Border.height + 2 * m_BorderDistance, 2.f);

}

void Button::ToggleSelection()
{
	m_IsSelected = !m_IsSelected;
}

void Button::SetColor(COLORREF color)
{
	m_TextColor = color;
}

void Button::SetWidth(int width)
{
	m_Border.left = m_Center.x - width / 2;
	m_Border.width = width;
}

void Button::SetHeight(int height)
{
	m_Border.bottom = m_Center.y - height / 2;
	m_Border.height = height;
}
