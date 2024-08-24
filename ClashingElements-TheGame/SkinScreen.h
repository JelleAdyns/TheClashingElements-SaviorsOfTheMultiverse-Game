#ifndef SKINSCREEN_H
#define SKINSCREEN_H

#include "Screen.h"
#include "GlobalEnumClasses.h"
#include "BackGround.h"
#include <functional>


class Player;
class Button;
class SkinScreen final : public Screen
{
public:
	explicit SkinScreen(const std::wstring& backGroundFilePath, const RectInt& window, std::function<void()> nextEvent);
	~SkinScreen();

	SkinScreen(const SkinScreen& other) = delete;
	SkinScreen(SkinScreen&& other) noexcept = delete;
	SkinScreen& operator=(const SkinScreen& other) = delete;
	SkinScreen& operator=(SkinScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Tick() override;
	virtual void KeyInput(int virtualKeyCode) override;

	std::shared_ptr<Player> GetPlayer() const;

private:

	BackGround m_BackGround;

	std::vector<std::shared_ptr<Player>> m_pVecSkins;
	std::vector<std::unique_ptr<Button>> m_pVecSkinButtons;
	int m_IndexCurrSkin;
	
	RectInt m_SelectionRect;
};


#endif // !SKINSCREEN_H