#ifndef PATHGRAPH_H
#define PATHGRAPH_H


#include <vector>
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

	int GetXCenterOfTile(int id) const;
	int GetYCenterOfTile(int id) const;

	int GetTileId(const Point2Int& location) const;
	bool IsCurrTileIntersection(const Point2Int& location) const;

	bool HasNeighbourInDirection(const Direction& dir, const Point2Int& playerPos, int& targetLocation) const;

private:
	std::vector<std::vector<int>> m_AdjacencyList;
	std::vector<Tile> m_VecTiles;

};


#endif // !PATHGRAPH_H
