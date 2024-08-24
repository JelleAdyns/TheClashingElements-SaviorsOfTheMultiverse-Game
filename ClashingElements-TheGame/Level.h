#ifndef LEVEL_H
#define LEVEL_H


#include <vector>
#include <memory>
#include "AnimBackGround.h"
#include "BackGround.h"
#include "Collectable.h"
#include "PathGraph.h"
#include "Camera.h"
#include "HUD.h"


class AnimatedSprite;
class Player;
class Enemy;

class Level final
{
public:
	explicit Level(std::shared_ptr<Player> pCharacter, int viewportWidth, int viewportHeight);
	~Level();

	Level(const Level& other) = delete;
	Level(Level&& other) noexcept = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) noexcept = delete;

	void Tick();
	void Draw() const;

private:
	const std::vector<std::pair<tstring, std::pair<tstring, Point2Int>>> m_VecBackGrounds;
	const std::vector<tstring> m_VecMusic;

	uint8_t m_MaxStages;
	uint8_t m_StageNumber;
	int m_LoopNumber;

	HUD m_Hud;
	Camera m_Camera;

	std::unique_ptr < AnimBackGround > m_pAnimBackGround;
	std::unique_ptr < BackGround > m_pBackGround;

	std::vector< std::shared_ptr<Collectable> > m_pVecCollectables;
	std::vector< std::unique_ptr<AnimatedSprite> > m_pVecSprites;
	std::vector< std::shared_ptr<Enemy> > m_pVecEnemies;

	std::vector< std::shared_ptr<AnimatedSprite> > m_pDrawBuffer;

	std::shared_ptr<Player> m_pPlayer;

	PathGraph m_Graph;

	void HitCollectable();
	void LoadStage();
	void Reset();
	void SetUpDrawBuffer();

};
#endif // !LEVEL_H
