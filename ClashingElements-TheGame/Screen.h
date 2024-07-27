#pragma once
#include <iostream>
#include <utils.h>
#include <vector>
class Screen
{
public:
	explicit Screen(const Rectf& window);
	virtual ~Screen() = default;

	Screen(const Screen& other) = delete;
	Screen(Screen&& other) noexcept = delete;
	Screen& operator=(const Screen& other) = delete;
	Screen& operator=(Screen&& other) noexcept = delete;

	virtual void Draw() const = 0;
	virtual void Update(float elapsedSec) = 0;
	virtual void KeyInput(int virtualKeyCode) = 0;
protected:
	Rectf m_Window;
};