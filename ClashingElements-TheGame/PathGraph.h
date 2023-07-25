#pragma once
#include <vector>
#include <utils.h>
#include "Tile.h"

class PathGraph
{
public:
	explicit PathGraph() = default;
	~PathGraph() = default;

	PathGraph(const PathGraph& other) = delete;
	PathGraph(PathGraph&& other) noexcept = delete;
	PathGraph& operator=(const PathGraph& other) = delete;
	PathGraph& operator=(PathGraph&& other) noexcept = delete;

	//DEBUG DRAW
	void Draw() const;
	void AddTile(int id, int centerX, int centerY, bool isIntersection = false);
	void AddEdge(int srcTileId, int neighboutId);

	int GetXCenterOfTile(int id) const;
	int GetYCenterOfTile(int id) const;
	int GetNrOfTiles() const;

	bool HasNeighbourInDirection(const Vector2f& dir, const Point2f& playerPos, int& targetLocation) const;
private:
	std::vector<std::vector<int>> m_AdjacencyList;
	std::vector<Tile> m_VecTiles;

	int GetTileId(const Point2f& playerPos) const;
};

