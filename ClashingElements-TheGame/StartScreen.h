#pragma once
#include "Screen.h"
class StartScreen final: public Screen
{
public:
	explicit StartScreen();
	~StartScreen();

	StartScreen(const StartScreen& other) = delete;
	StartScreen(StartScreen&& other) noexcept = delete;
	StartScreen& operator=(const StartScreen& other) = delete;
	StartScreen& operator=(StartScreen&& other) noexcept = delete;

private:

};

