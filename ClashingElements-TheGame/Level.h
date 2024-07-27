#pragma once

#include <vector>
#include <SoundStream.h>
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
	explicit Level(std::shared_ptr<Player> pCharacter, float viewportWidth, float viewportHeight);
	~Level();

	Level(const Level& other) = delete;
	Level(Level&& other) noexcept = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) noexcept = delete;

	void Update(float elapsedSec);
	void Draw() const;

private:
	const std::vector<std::pair<std::string, std::pair<std::string, Point2f>>> m_VecBackGrounds;
	const std::vector<std::string> m_VecMusic;

	int m_StageNumber;
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

	std::unique_ptr < SoundStream > m_pBackGroundMusic;

	PathGraph m_Graph;

	void HitCollectable();
	void LoadStage();
	void Reset();
	void SetUpDrawBuffer();

};