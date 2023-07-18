#pragma once
#include <vector>
#include <Texture.h>
class BackGround;
class Screen
{
public:
	explicit Screen(const Point2f& bottomCenter, const std::string& backGroundFilePath);
	virtual ~Screen();

	Screen(const Screen& other) = delete;
	Screen(Screen&& other) noexcept = delete;
	Screen& operator=(const Screen& other) = delete;
	Screen& operator=(Screen&& other) noexcept = delete;

	virtual void Draw() const = 0;
	virtual void Update(float elapsedSec) = 0;
	virtual void KeyInput(const SDL_KeyboardEvent& e) = 0;
protected:
	//Sprite
	BackGround* m_pBackGround;

};