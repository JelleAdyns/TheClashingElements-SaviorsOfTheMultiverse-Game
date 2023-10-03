#pragma once
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
	GameOver
};