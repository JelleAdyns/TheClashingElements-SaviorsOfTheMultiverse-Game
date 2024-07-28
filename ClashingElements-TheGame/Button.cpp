#include "Button.h"


Button::Button(const tstring& text, const Point2Int& center, std::function<void()> toExecute, bool isSelected):
	m_IsSelected{isSelected},
	m_Center{center},
	m_FuncToExecute{toExecute},
	m_Border{},
	m_Text{ text }
	//m_NextGameState{nextGameState}
{
	int borderDistance{ 5 };
	m_Border = RectInt{ center.x - 200/2 - borderDistance,
										  center.y - 16/2 - borderDistance,
										  200 + 2 * borderDistance,
										  16 + 2 * borderDistance };
	
}
//Button::Button(const Texture* texture, const Point2Int& center, std::function<void()> toExecute, bool isSelected = false):
//	m_IsSelected{ isSelected },
//	m_Center{ center },
//	m_FuncToExecute{ toExecute }
//{
//	m_pText = texture;
//}


void Button::Draw() const
{

	ENGINE.PushTransform();
	ENGINE.Scale(0.5f, m_Center);
	ENGINE.SetColor(RGB(255,255,255));
	ENGINE.DrawString(m_Text,GlobalFont::Get().GetFont(), Point2Int{m_Center.x - 200 / 2, m_Center.y - 16 / 2}, 200);
	if(m_IsSelected) ENGINE.DrawRectangle(m_Border, 2.f);
	ENGINE.PopTransform();
}

void Button::ToggleSelection()
{
	m_IsSelected = !m_IsSelected;
}