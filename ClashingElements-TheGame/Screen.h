#pragma once
#include <vector>

class Texture;
class Screen
{
public:
	explicit Screen();
	~Screen();

	Screen(const Screen& other) = delete;
	Screen(Screen&& other) noexcept = delete;
	Screen& operator=(const Screen& other) = delete;
	Screen& operator=(Screen&& other) noexcept = delete;
private:
	//Sprite
	

};