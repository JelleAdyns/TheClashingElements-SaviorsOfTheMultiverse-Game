#pragma once
#include <functional>
#include <Texture.h>
#include "GlobalFont.h"
#include "GlobalEnumClasses.h"

class Button
{
public:
	//explicit Button(const std::string& text, const Point2f& center/*,const GameState& nextGameState*/,  bool isSelected = false);
	explicit Button(const std::string& text, const Point2f& center, std::function<void()> toExecute, bool isSelected = false);
	explicit Button(const Texture* texture, const Point2f& center, std::function<void()> toExecute, bool isSelected = false);
	~Button();

	Button(const Button& other) = delete;
	Button(Button&& other) noexcept = delete;
	Button& operator=(const Button& other) = delete;
	Button& operator=(Button&& other) noexcept = delete;


	void Draw() const;
	void ToggleSelection();

	void ExecuteFunction() { m_FuncToExecute(); }
	
private:
	bool m_IsSelected;
	const Point2f m_Center;
	//const GameState m_NextGameState;

	const Texture* m_pText;
	const Rectf m_Border;
	std::function<void()> m_FuncToExecute;
};

