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
	void AddTile(const int id, const int centerX, const int centerY, const bool isIntersection = false);
	void AddEdge(const int srcTileId, const int neighboutId);

	int GetXCenterOfTile(const int id) const;
	int GetYCenterOfTile(const int id) const;
	int GetNrOfTiles() const;

	int GetTileId(const Point2f& playerPos) const;

	bool HasNeighbourInDirection(const Vector2f& dir, const Point2f& playerPos, int& targetLocation) const;
private:
	std::vector<std::vector<int>> m_AdjacencyList;
	std::vector<Tile> m_VecTiles;

};

