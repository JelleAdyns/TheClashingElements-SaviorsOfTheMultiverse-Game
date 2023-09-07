#pragma once
#include "Screen.h"
#include "GlobalEnumClasses.h"
#include "BackGround.h"
#include <vector>

class Character;
class SkinScreen final : public Screen
{
public:
	explicit SkinScreen(const std::string& backGroundFilePath, const Rectf& window);
	~SkinScreen();

	SkinScreen(const SkinScreen& other) = delete;
	SkinScreen(SkinScreen&& other) noexcept = delete;
	SkinScreen& operator=(const SkinScreen& other) = delete;
	SkinScreen& operator=(SkinScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;
	virtual void KeyInput(const SDL_KeyboardEvent& e) override;

	Character* GetCharacter() const;

private:

	BackGround m_BackGround;

	std::vector<Character*> m_pSkins;
	int m_IndexCurrSkin;
	
	Rectf m_SelectionRect;

};

