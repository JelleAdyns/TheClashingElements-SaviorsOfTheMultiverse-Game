#ifndef GLOBALENUMCLASSES_H
#define GLOBALENUMCLASSES_H

#include "Audio.h"

enum class Skin
{
	Finn,
	Wesley
};

enum class Direction
{
	Down,
	Left,
	Up,
	Right
};

enum class GameState
{
	Start,
	ShowingHighScores,
	SelectingSkin,
	Playing,
	Welcome,
	Pause,
	GameOver,
	Results
};

enum class SoundEvent : SoundID
{
	Spaceship,
	Saw
};

enum class KeyState
{
	DownThisFrame,
	UpThisFrame,
	Pressed,
	NotPressed

};

#endif // !GLOBALENUMCLASSES_H
