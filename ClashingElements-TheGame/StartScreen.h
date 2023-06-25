#pragma once
#include <vector>

class Texture;
class StartScreen
{
public:
	explicit StartScreen();
	~StartScreen();

	StartScreen(const StartScreen& other) = delete;
	StartScreen(StartScreen&& other) noexcept = delete;
	StartScreen& operator=(const StartScreen& other) = delete;
	StartScreen& operator=(StartScreen&& other) noexcept = delete;
private:
	//Sprite
	std::vector<Texture*> m_pVecText;

};