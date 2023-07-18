#pragma once
#include "Screen.h"
#include <vector>

class SkinScreen final : public Screen
{
public:
	explicit SkinScreen(const Point2f& bottomCenter, const std::string& backGroundFilePath, const Rectf& window);
	~SkinScreen();

	SkinScreen(const SkinScreen& other) = delete;
	SkinScreen(SkinScreen&& other) noexcept = delete;
	SkinScreen& operator=(const SkinScreen& other) = delete;
	SkinScreen& operator=(SkinScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;
	virtual void KeyInput(const SDL_KeyboardEvent& e) override;

private:
	std::vector<Texture*> m_pSkins;
	int m_IndexSelectedSkin;
	int m_NrOfCols;
	int m_NrOfFrames;
	int m_CurrentCol;
	Rectf m_Window;

	Rectf DestRect(const Texture& texture) const;
	Rectf SrcRect(const Texture& texture) const;
};

