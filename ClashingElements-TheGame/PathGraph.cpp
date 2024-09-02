#include "PathGraph.h"
#include <map>


void PathGraph::Draw() const
{
#ifdef _DEBUG

	ENGINE.SetColor(RGB(255, 255, 255));
	for (const Tile& tile : m_VecTiles)
	{
		ENGINE.DrawRectangle(tile.Area);
	}

	for (const std::vector<TileID>& vector : m_AdjacencyList)
	{
		std::vector<Point2Int> points{};
		for (const TileID id : vector)
		{
			points.push_back(GetCenterOfTile(id));
		}
		for (size_t i = 1; i < points.size(); i++)
		{
			ENGINE.DrawLine(points.at(i - 1), points.at(i));
		}
		ENGINE.DrawLine(points.at(points.size() - 1), points.at(0));

	}

#endif // _DEBUG
}
void PathGraph::AddTile(TileID id, int centerX, int centerY, bool isIntersection)
{
	m_VecTiles.push_back(Tile{ id, centerX, centerY, isIntersection });
	m_AdjacencyList.push_back(std::vector<TileID>{});
}
void PathGraph::AddEdge(TileID srcTileId, TileID neighbourId)
{
	m_AdjacencyList[srcTileId].push_back(neighbourId);
	m_AdjacencyList[neighbourId].push_back(srcTileId);
}

Point2Int PathGraph::GetCenterOfTile(TileID id) const
{
	return m_VecTiles[id].Center;
}


TileID PathGraph::GetTileId(int locationX, int locationY) const
{
	return GetTileId(Point2Int{ locationX, locationY });
}

TileID PathGraph::GetTileId(const Point2Int& location) const
{
	for (const auto& tile : m_VecTiles)
	{
		if (utils::IsPointInRect(location, tile.Area))
		{
			return tile.Id;
		}
	}
	return -1;
}
const Tile& PathGraph::ReadTile(TileID tileId) const
{
	assert(tileId < m_VecTiles.size() && tileId >= 0);
	return m_VecTiles.at(tileId);
}
void PathGraph::SetWalkabilityOfTile(TileID tileId, bool walkable)
{
	assert(tileId < m_VecTiles.size() && tileId >= 0);
	m_VecTiles.at(tileId).IsWalkable = walkable;
}
bool PathGraph::IsTileIntersection(const Point2Int& location) const
{	
	return m_VecTiles[GetTileId(location)].IsIntersection;
}

bool PathGraph::HasNeighbourInDirection(const Direction& dir, const Point2Int& characterPos, Point2Int& neigbourCenter) const
{
	TileID id{ GetTileId(characterPos) };
	
	for (const auto& neighbour : m_AdjacencyList[id])
	{
		switch (dir)
		{
		case Direction::Left:

			if (m_VecTiles[neighbour].Center.x < m_VecTiles[id].Center.x)
			{
				neigbourCenter = m_VecTiles[neighbour].Center;
				return true;
			}
			break;

		case Direction::Right:

			if (m_VecTiles[neighbour].Center.x > m_VecTiles[id].Center.x) 
			{
				neigbourCenter = m_VecTiles[neighbour].Center;
				return true;
			}
			break;

		case Direction::Down:

			if (m_VecTiles[neighbour].Center.y < m_VecTiles[id].Center.y)
			{
				neigbourCenter = m_VecTiles[neighbour].Center;
				return true;
			}
			break;

		case Direction::Up:

			if (m_VecTiles[neighbour].Center.y > m_VecTiles[id].Center.y) 
			{
				neigbourCenter = m_VecTiles[neighbour].Center;
				return true;
			}
			break;
		}

	}
	
	return false;
}

std::vector<TileID> PathGraph::GetNeighbours(TileID tileId) const
{
	return m_AdjacencyList.at(tileId);
}

namespace
{
	struct Node
	{
		int gCost{};
		int hCost{};
		TileID tileId{};
		TileID parentId{};

		int fCost() const { return gCost + hCost; }

		static int CalculateCost(const Point2Int& A, const Point2Int& B)
		{
			int x = std::abs(A.x - B.x) / Tile::Size;
			int y = std::abs(A.y - B.y) / Tile::Size;
			return x + y;
		}
	};
	std::pair<TileID, Node> GetCurrentNode(const std::map<TileID, Node>& openNodes)
	{
		std::pair<TileID, Node> pair = *openNodes.cbegin();
		auto [currentTileId, currentNode] = pair;
		for (auto& [tileId, node] : openNodes)
		{
			if (node.fCost() < currentNode.fCost() or
				(node.fCost() == currentNode.fCost() and node.hCost < currentNode.hCost))
			{
				currentNode = node;
				currentTileId = tileId;
			}
		}
		return std::make_pair(currentTileId, currentNode);
	}
}

std::vector<TileID> PathGraph::CalculatShortestPath(TileID startId, TileID endId) const
{
	//This guy helped me out a lot!
	//https://www.youtube.com/watch?v=mZfyt03LDH4&t=1094s

	Point2Int startPos{ GetCenterOfTile(startId) };
	Point2Int endPos{ GetCenterOfTile(endId) };

	std::map<TileID, Node> openNodes{};
	std::map<TileID, Node> closedNodes{};

	openNodes.emplace(startId, Node{.hCost = Node::CalculateCost(startPos, endPos), .tileId = startId });

	while (!openNodes.empty())
	{
		// get the node with the lowest f_cost
		auto [currentTileId, currentNode] = GetCurrentNode(openNodes);

		// close this node
		openNodes.erase(currentTileId);
		closedNodes.emplace(currentTileId, currentNode); 

		//check if path is found
		if (currentTileId == endId)
		{
			std::vector<TileID> path{ };
			TileID currentTile{ closedNodes.at(endId).tileId };
			do
			{
				path.push_back(currentTile);
				currentTile = closedNodes.at(currentTile).parentId;

			} while (path.back() != startId);

			return path;
		}

		//loop over neighbours to calculate f_cost 
		for (const auto& neighbourTileId : m_AdjacencyList[currentTileId])
		{
			if (not ReadTile(neighbourTileId).IsWalkable or closedNodes.contains(neighbourTileId))
				continue;

			Point2Int neighbourPos{ GetCenterOfTile(neighbourTileId) };
			Point2Int currentPos{ GetCenterOfTile(currentTileId) };

			int newCostToNeighbour = currentNode.gCost + Node::CalculateCost(currentPos, neighbourPos);
			if (!openNodes.contains(neighbourTileId) || newCostToNeighbour < openNodes.at(neighbourTileId).gCost)
			{
				
				if (openNodes.contains(neighbourTileId))
				{
					openNodes.at(neighbourTileId).gCost = newCostToNeighbour;
					openNodes.at(neighbourTileId).hCost = Node::CalculateCost(neighbourPos, endPos);
					openNodes.at(neighbourTileId).parentId = currentTileId;
				}
				else
				{
					openNodes.emplace(neighbourTileId, Node{
						.gCost = newCostToNeighbour,
						.hCost = Node::CalculateCost(neighbourPos, endPos),
						.tileId = neighbourTileId,
						.parentId = currentTileId
						});
				}
			}
		}
	}
	return std::vector<TileID>{};
}

