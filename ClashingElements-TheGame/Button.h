#pragma once
#include <functional>
#include "GlobalFont.h"
#include "GlobalEnumClasses.h"
#include "Engine.h"
#include "Commands.h"

class Button
{
public:
	//explicit Button(const std::string& text, const Point2Int& center/*,const GameState& nextGameState*/,  bool isSelected = false);
	explicit Button(const tstring& text, const Point2Int& center, std::unique_ptr<Command>&& toExecute, bool isSelected = false);
	~Button() = default;

	Button(const Button& other) = delete;
	Button(Button&& other) noexcept = delete;
	Button& operator=(const Button& other) = delete;
	Button& operator=(Button&& other) noexcept = delete;


	void Draw() const;
	void ToggleSelection();
	void SetColor(COLORREF color);
	void SetWidth(int width);
	void SetHeight(int height);

	void ExecuteCommand() { m_CommandToExecute->Execute(); }
	
private:
	static const int m_BorderDistance{ 3 };

	bool m_IsSelected;
	const Point2Int m_Center;

	const tstring m_Text;

	COLORREF m_TextColor;
	RectInt m_Border;
	std::unique_ptr<Command> m_CommandToExecute;
};

