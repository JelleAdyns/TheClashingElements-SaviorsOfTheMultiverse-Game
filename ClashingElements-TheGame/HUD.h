#ifndef HUD_H
#define HUD_H

#include "Engine.h"
#include "Player.h"

class HUD final : public Observer<int>, public Observer<Player*>
{
public:
	 HUD(int windowWidth, int windowHeight, Skin skin);
	~HUD() = default;

	HUD(const HUD& other) = delete;
	HUD(HUD&& other) noexcept = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD& operator=(HUD&& other) noexcept = delete;

	void Draw() const;

	virtual void Notify(Player* player) override;
	virtual void Notify(int score) override;
	virtual void OnSubjectDestroy() override;

	static int GetHudHeight();

private:

	void AddScore(int points);

	const static int m_HudHeight;

	tstring m_YourScore{};
	tstring m_HighScore{};

	const RectInt m_HudArea;
	int m_Lives{3};
	int m_CurrentScore{0};
	int m_CurrentHighScore{0};
	bool m_NewHighScoreReached{false};

	std::unique_ptr<Texture> m_pLivesTexture;
	const RectInt m_LivesSrcRect{};

	COLORREF m_TextColor{ RGB(255,255,255) };
	tstring m_pTextCollectables{  };

};


#endif // !HUD_H