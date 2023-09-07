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

private:
	const std::vector<std::pair<std::string,std::pair<std::string, Point2f>>> m_VecBackGrounds;
	const std::vector<std::string> m_VecMusic;

	int m_StageNumber;
	int m_LoopNumber;

	Camera m_Camera;

	AnimBackGround* m_pAnimBackGround;
	BackGround* m_pBackGround;

	std::vector<Collectable*> m_pVecCollectables;
	std::vector<AnimatedSprite*> m_pVecSprites;

	Character* m_pPlayer;

	SoundStream* m_pBackGroundMusic;

	PathGraph m_Graph;

	void HitCollectable();
	void LoadStage();
	void Reset();
};