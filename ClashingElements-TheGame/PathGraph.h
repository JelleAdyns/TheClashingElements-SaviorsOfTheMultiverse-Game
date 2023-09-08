#pragma once
#include <vector>
#include <utils.h>
#include "Tile.h"
#include "GlobalEnumClasses.h"

class PathGraph
{
public:
	explicit PathGraph() = default;
	~PathGraph() = default;

	PathGraph(const PathGraph& other) = delete;
	PathGraph(PathGraph&& other) noexcept = delete;
	PathGraph& operator=(const PathGraph& other) = delete;
	PathGraph& operator=(PathGraph&& other) noexcept = default;

	//DEBUG DRAW
	void Draw() const;
	void AddTile(int id, int centerX, int centerY, bool isIntersection = false);
	void AddEdge(int srcTileId, int neighboutId);
	void AddEscalator(const Point2f& startCenter, const Point2f& endCenter, bool isDownwards);

	int GetXCenterOfTile(int id) const;
	int GetYCenterOfTile(int id) const;
	int GetNrOfTiles() const;

	bool HasNeighbourInDirection(const Direction& dir, const Point2f& playerPos, int& targetLocation) const;
	float GetEscalatorVelocity(const Point2f& playerPos, int& targetY) const;

	void Reset();
private:
	std::vector<std::vector<int>> m_AdjacencyList;
	std::vector<Tile> m_VecTiles;
	std::vector<Escalator> m_VecEscalators;

	int GetTileId(const Point2f& playerPos) const;
};

