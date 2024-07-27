#pragma once
#include <Texture.h>
#include "Collectable.h"

class HUD
{
public:
	 HUD(float windowWidth, float windowHeight);
	~HUD();

	HUD(const HUD& other) = delete;
	HUD(HUD&& other) noexcept = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD& operator=(HUD&& other) noexcept = delete;

	void Update(float elapsedSec);
	void Draw() const;

	void SetNrCollectables(int nrOfCollectables);

	static int GetHudHeight();

private:

	const static int m_HudHeight;

	const Rectf m_HudArea;

	const Color4f m_TextColor{ 1.f,0.f,1.f,0.f };
	const Texture* m_pTextCollectables{ nullptr };
	const Collectable m_pCollectable;

};

