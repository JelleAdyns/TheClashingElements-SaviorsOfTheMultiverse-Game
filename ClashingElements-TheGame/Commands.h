#ifndef COMMANDS_H
#define COMMANDS_H

#include "GlobalEnumClasses.h"
#include "Game.h"

class Command
{
public:

	Command() = default;

	Command(const Command& other) = delete;
	Command(Command&& other) noexcept = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other) noexcept = delete;


	virtual void Execute() = 0;
};

class LoadScreenCommand final : public Command
{
public:
	LoadScreenCommand(Game& game, GameState newGameState) :
		Command{},
		m_NewGameState{ newGameState },
		m_Game{ game }
	{}

	LoadScreenCommand(const LoadScreenCommand& other) = delete;
	LoadScreenCommand(LoadScreenCommand&& other) noexcept = delete;
	LoadScreenCommand& operator=(const LoadScreenCommand& other) = delete;
	LoadScreenCommand& operator=(LoadScreenCommand&& other) noexcept = delete;


	virtual void Execute() override { m_Game.SetScreen(m_NewGameState); }

private:
	const GameState m_NewGameState;
	Game& m_Game;
};

#endif // !COMMANDS_H

