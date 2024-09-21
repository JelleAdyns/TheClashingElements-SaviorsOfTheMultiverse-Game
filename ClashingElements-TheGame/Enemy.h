#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "GlobalEnumClasses.h"
#include "PathGraph.h"
#include <deque>

class Enemy : public Character
{
public:
	explicit Enemy(const Point2Int& bottomCenter, const tstring& textureFile, SpriteInfo spriteInfo, uint8_t startSmartness);
	virtual ~Enemy() = default;

	Enemy(const Enemy& other) = delete;
	Enemy(Enemy&& other) noexcept = delete;
	Enemy& operator=(const Enemy& other) = delete;
	Enemy& operator=(Enemy&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Move(const PathGraph& graph) override;
	//virtual void InteractWithMobilityItem(const MobilityItem& mobilityItem) override;

	void SetTarget(const Point2Int& playerTarget);
protected:
	const uint8_t m_StartSmartnessLevel;
	uint8_t m_SmartnessLevel{};
	static constexpr uint8_t m_MaxSmartnessLevel{ 100 };


private:

	static constexpr float m_VisionGainPercentage{ 0.7f };

	struct DirInfo
	{
		Direction dir;
		int nrOfTiles;
		Point2Int nextTargetPos;
	};

	std::deque<DirInfo> m_DirMap{};
	std::vector<Point2Int> m_Path{};
	Point2Int m_LastKnownPlayerPos{};

	const int m_VisionRadius{ Tile::Size * 6 };

	void FillDirectionMap(const PathGraph& graph);
	void CalculatePathsInAllDirections(const PathGraph& graph);
	void SortDirectionMap();
	void ChoosePath();
};


#endif // !ENEMY_H


