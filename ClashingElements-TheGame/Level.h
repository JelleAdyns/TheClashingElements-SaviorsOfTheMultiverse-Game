#pragma once

#include <vector>
#include <SoundStream.h>
#include "AnimBackGround.h"
#include "BackGround.h"
#include "Collectable.h"
#include "PathGraph.h"
#include "Camera.h"


class AnimatedSprite;
class Character;

class Level final
{
public:
	explicit Level(Character* pCharacter, float viewportWidth, float viewportHeight);
	~Level();

	Level(const Level& other) = delete;
	Level(Level&& other) noexcept = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) noexcept = delete;

	void Update(float elapsedSec);
	void Draw() const;

	void SetWidthHeight(float width, float height);
	Rectf GetPlayerPos() const;
	Rectf GetLevelBoundaries() const;
private:
	int m_StageNumber;
	int m_LoopNumber;

	Camera m_Camera;

	AnimBackGround* m_pAnimBackGround;
	BackGround* m_pBackGround;

	std::vector<Collectable*> m_pVecCollectables;
	std::vector<AnimatedSprite*> m_pVecSprites;

	Character* m_pPlayer;


	SoundStream* m_pBackGroundMusic;
	PathGraph m_pGraph;

	void HitCollectable();
	void LoadStage();
};