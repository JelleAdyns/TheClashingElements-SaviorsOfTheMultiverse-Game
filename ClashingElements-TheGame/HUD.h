#ifndef HUD_H
#define HUD_H

#include "Engine.h"
#include "Player.h"

class Level;
class HUD final : public Observer<int>, public Observer<Player*>
{
public:
	 HUD(int windowWidth, int windowHeight, Skin skin);
	virtual ~HUD() = default;

	HUD(const HUD& other) = delete;
	HUD(HUD&& other) noexcept = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD& operator=(HUD&& other) noexcept = delete;

	void Draw() const;
	void Tick();

	virtual void Notify(Player* player) override;
	virtual void Notify(int score) override;
	virtual void OnSubjectDestroy() override;

	static int GetHudHeight();
	void AddObserver(Level* levelObserver);

	bool FinishedCountSeconds();

	void Reset();

	struct Counters
	{
		int nrOfCollectables{};
		int nrOfSecondsLeft{};
		int nrOfEnemiesKilled{};
		int nrOfLivesLost{};
		int totalScore{};

		constexpr static int scorePerCollectable = 10;
		constexpr static int scorePerSecond = 100;
		constexpr static int scorePerEnemyKilled = 200;
		constexpr static int scorePerLifeLost = -100;
	};

	Counters GetCounters() const;
private:

	void AddScore(int points);

	const static int m_HudHeight;

	const RectInt m_HudArea;

	tstring m_YourScore{};
	tstring m_HighScore{};

	int m_CurrentScore{0};
	int m_CurrentHighScore{0};

	constexpr static int m_StartLives{ 3};
	int m_Lives{3};

	constexpr static int m_StartSeconds{ 250 };
	int m_SecondsLeft{ m_StartSeconds};

	Counters m_Counters{};

	std::unique_ptr<Subject<Counters>> m_pDied;

	const Texture& m_rLivesTexture;

	const RectInt m_LivesSrcRect{};
};


#endif // !HUD_H