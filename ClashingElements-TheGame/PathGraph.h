#ifndef PATHGRAPH_H
#define PATHGRAPH_H


#include <vector>
#include <map>
#include "Tile.h"
#include "GlobalEnumClasses.h"

class PathGraph final
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

	void AddTile(TileID id, int centerX, int centerY, bool isIntersection = false);
	void AddEdge(TileID srcTileId, TileID neighboutId);

	Point2Int GetCenterOfTile(TileID id) const;

	TileID GetTileId(int locationX, int locationY) const;
	TileID GetTileId(const Point2Int& location) const;
	const Tile& ReadTile(TileID tileId) const;
	std::vector<TileID> GetNeighbours(TileID tileId) const;

	void SetWalkabilityOfTile(TileID tileId, bool walkable);
	bool IsTileIntersection(const Point2Int& location) const;
	bool HasNeighbourInDirection(const Direction& dir, const Point2Int& playerPos, Point2Int& neigbourCenter) const;

	//This guy helped me out a lot!
	//https://www.youtube.com/watch?v=mZfyt03LDH4&t=1094s
	std::vector<TileID> CalculatShortestPath(TileID startId, TileID endId) const;

	void Reset();
private:

	std::vector<std::vector<TileID>> m_AdjacencyList;
	std::vector<Tile> m_VecTiles;

};


#endif // !PATHGRAPH_H
