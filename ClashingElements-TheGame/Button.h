#pragma once
#include <functional>
#include "GlobalFont.h"
#include "GlobalEnumClasses.h"
#include "Engine.h"

class Button
{
public:
	//explicit Button(const std::string& text, const Point2Int& center/*,const GameState& nextGameState*/,  bool isSelected = false);
	explicit Button(const tstring& text, const Point2Int& center, std::function<void()> toExecute, bool isSelected = false);
	~Button() = default;

	Button(const Button& other) = delete;
	Button(Button&& other) noexcept = delete;
	Button& operator=(const Button& other) = delete;
	Button& operator=(Button&& other) noexcept = delete;


	void Draw() const;
	void ToggleSelection();

	void ExecuteFunction() { m_FuncToExecute(); }
	
private:
	bool m_IsSelected;
	const Point2Int m_Center;
	//const GameState m_NextGameState;

	const tstring m_Text;
	RectInt m_Border;
	std::function<void()> m_FuncToExecute;
};

