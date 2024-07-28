#ifndef HUD_H
#define HUD_H

#include "Collectable.h"

class HUD
{
public:
	 HUD(int windowWidth, int windowHeight);
	~HUD() = default;

	HUD(const HUD& other) = delete;
	HUD(HUD&& other) noexcept = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD& operator=(HUD&& other) noexcept = delete;

	void Update();
	void Draw() const;

	void SetNrCollectables(int nrOfCollectables);

	static int GetHudHeight();

private:

	const static int m_HudHeight;

	const RectInt m_HudArea;

	COLORREF m_TextColor{ RGB(255,0,255) };
	tstring m_pTextCollectables{  };
	const Collectable m_pCollectable;

};


#endif // !HUD_H