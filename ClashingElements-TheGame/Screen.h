#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include "Structs.h"
#include "Engine.h"

class Screen
{
public:
	explicit Screen(const RectInt& window);
	virtual ~Screen() = default;

	Screen(const Screen& other) = delete;
	Screen(Screen&& other) noexcept = delete;
	Screen& operator=(const Screen& other) = delete;
	Screen& operator=(Screen&& other) noexcept = delete;

	virtual void Draw() const {};
	virtual void Tick() {};
	virtual void KeyInput(int virtualKeyCode) {};
protected:
	RectInt m_Window;
};

#endif // !SCREEN_H