#pragma once
#include "Screen.h"
#include "GlobalEnumClasses.h"
#include "BackGround.h"
#include <functional>



class Player;
class Button;
class SkinScreen final : public Screen
{
public:
	explicit SkinScreen(const std::string& backGroundFilePath, const RectInt& window, std::function<void()> nextEvent);
	~SkinScreen();

	SkinScreen(const SkinScreen& other) = delete;
	SkinScreen(SkinScreen&& other) noexcept = delete;
	SkinScreen& operator=(const SkinScreen& other) = delete;
	SkinScreen& operator=(SkinScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;
	virtual void KeyInput(int virtualKeyCode) override;

	std::shared_ptr<Player> GetPlayer() const;

private:

	BackGround m_BackGround;

	std::vector<std::shared_ptr<Player>> m_pVecSkins;
	std::vector<std::unique_ptr<Button>> m_pVecSkinButtons;
	int m_IndexCurrSkin;
	
	Rectf m_SelectionRect;
};

