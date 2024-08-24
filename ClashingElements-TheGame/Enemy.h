#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "GlobalEnumClasses.h"
#include "PathGraph.h"

class Enemy : public Character
{
public:
	explicit Enemy(const Point2Int& bottomCenter, int nrCols, int nrFrames, float frameTime );
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
	uint8_t m_SmartnessLevel;
	const uint8_t m_MaxSmartnessLevel{100};


private:

	std::vector<std::tuple<Direction, int, Point2Int>> m_DirMap;
	std::vector<Point2Int> m_Path;
	Point2Int m_LastKnownPlayerPos;

	void FillDirectionMap(const PathGraph& graph);
	void CalculatePathsInAllDirections(const PathGraph& graph);
	void SortDirectionMap();
};


#endif // !ENEMY_H


