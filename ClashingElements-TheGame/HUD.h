#ifndef HUD_H
#define HUD_H

#include "Engine.h"

class HUD final : public Observer<int>
{
public:
	 HUD(int windowWidth, int windowHeight);
	~HUD() = default;

	HUD(const HUD& other) = delete;
	HUD(HUD&& other) noexcept = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD& operator=(HUD&& other) noexcept = delete;

	void Draw() const;

	virtual void Notify(int score) override;
	virtual void OnSubjectDestroy() override;
	static int GetHudHeight();

private:

	const static int m_HudHeight;

	tstring m_YourScore;
	tstring m_HighScore;

	const RectInt m_HudArea;
	int m_CurrentScore{0};

	COLORREF m_TextColor{ RGB(255,255,255) };
	tstring m_pTextCollectables{  };

};


#endif // !HUD_H