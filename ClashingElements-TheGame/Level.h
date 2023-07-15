#pragma once

#include <vector>
#include <SoundStream.h>

class AnimatedSprite;
class Character;
class PathGraph;
class Collectable;

class Level final
{
public:
	explicit Level();
	~Level();

	Level(const Level& other) = delete;
	Level(Level&& other) noexcept = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) noexcept = delete;

	void Update(float elapsedSec);
	void Draw() const;

	void Move();

	Rectf GetPlayerPos() const;
	Rectf GetLevelBoundaries() const;
private:
	int m_StageNumber;
	int m_LoopNumber;
	std::vector<AnimatedSprite*> m_VecTestSprites;
	std::vector<Collectable*> m_pVecCollectables;
	Character* m_pPlayer;

	SoundStream* m_pBackGroundMusic;
	PathGraph* m_pGraph;

	void HitCollectable();
	void LoadStage();
};