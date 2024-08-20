#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "GlobalEnumClasses.h"
#include "PathGraph.h"
#include <map>

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


protected:
	int m_SmartnessLevel;


private:

	std::vector<std::pair<Direction, int>> m_DirMap;
	std::vector<Point2Int> m_Path;
};


#endif // !ENEMY_H


