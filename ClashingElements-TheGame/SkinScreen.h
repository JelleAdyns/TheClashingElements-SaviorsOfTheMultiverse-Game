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

	Skin GetPlayer() const;

private:

	BackGround m_BackGround;

	std::vector<std::unique_ptr<Player>> m_pVecSkinSprites;
	std::vector<Skin> m_pVecSkins;
	std::vector<std::unique_ptr<Button>> m_pVecSkinButtons;
	int m_IndexCurrSkin;
	
	RectInt m_SelectionRect;
};


#endif // !SKINSCREEN_H