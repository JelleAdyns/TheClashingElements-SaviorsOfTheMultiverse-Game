#ifndef SKINSCREEN_H
#define SKINSCREEN_H

#include "Screen.h"
#include "GlobalEnumClasses.h"
#include "BackGround.h"
#include "Commands.h"
#include "Structs.h"
#include <functional>


class Player;
class Button;
class SkinScreen final : public Screen
{
public:
	explicit SkinScreen(Game& game, GameState nextState);
	~SkinScreen() = default;

	SkinScreen(const SkinScreen& other) = delete;
	SkinScreen(SkinScreen&& other) noexcept = delete;
	SkinScreen& operator=(const SkinScreen& other) = delete;
	SkinScreen& operator=(SkinScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Tick() override;
	virtual void KeyInput(int virtualKeyCode) override;

	virtual void OnEnter() override {};
	virtual void OnExit() override{};
	virtual void OnSuspend() override{};
	virtual void OnResume() override{};

	Skin GetPlayer() const;

private:

	BackGround m_BackGround;

	std::map<Skin, std::unique_ptr<Player>> m_pVecSkins;
	std::unique_ptr<Command> m_pLoadLevelCommand;
	
	int m_IndexCurrSkin;
	
	RectInt m_SelectionRect;
};


#endif // !SKINSCREEN_H