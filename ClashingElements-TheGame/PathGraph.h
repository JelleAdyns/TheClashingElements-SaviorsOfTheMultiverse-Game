#ifndef PATHGRAPH_H
#define PATHGRAPH_H


#include <vector>
#include <map>
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

	//This guy helped me out a lot!
	//https://www.youtube.com/watch?v=mZfyt03LDH4&t=1094s
	std::vector<int> CalculatShortestPath(const Direction& dir, const Point2Int& intersectionPos, const Point2Int& endPos) const;

private:

	struct Node
	{
		int gCost{};
		int hCost{};
		int tileId{};
		int parentId{};

		int fCost() const { return gCost + hCost; }

		static int CalculateCost(const Point2Int& A, const Point2Int& B)
		{
			int x = std::abs(A.x - B.x) / Tile::Size;
			int y = std::abs(A.y - B.y) / Tile::Size;
			return x + y;
		}
	};

	std::vector<int> RetracePath(const std::map<int, Node>& closedNodes, int startId, int endId) const;

	std::vector<std::vector<int>> m_AdjacencyList;
	std::vector<Tile> m_VecTiles;

};


#endif // !PATHGRAPH_H
