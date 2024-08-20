#include "PathGraph.h"
#include <map>

void PathGraph::Draw() const
{

	ENGINE.SetColor(RGB(255, 255, 255));
	for (const Tile& tile : m_VecTiles)
	{
		ENGINE.DrawRectangle(tile.Area);
	}
	
	for (const std::vector<int>& vector : m_AdjacencyList)
	{
		std::vector<Point2Int> points{};
		for (const int id : vector)
		{
			points.push_back(Point2Int{ GetXCenterOfTile(id), GetYCenterOfTile(id) });
		}
		for (size_t i = 1; i < points.size(); i++)
		{
			ENGINE.DrawLine(points.at(i - 1), points.at(i));
		}
		ENGINE.DrawLine(points.at(points.size()-1), points.at(0));

	}
}
void PathGraph::AddTile(int id, int centerX, int centerY, bool isIntersection)
{
	m_VecTiles.push_back(Tile{ id, centerX, centerY, isIntersection });
	m_AdjacencyList.push_back(std::vector<int>{});
}
void PathGraph::AddEdge(int srcTileId, int neighbourId)
{
	m_AdjacencyList[srcTileId].push_back(neighbourId);
	m_AdjacencyList[neighbourId].push_back(srcTileId);
}

int PathGraph::GetXCenterOfTile(int id) const
{
	return m_VecTiles[id].CenterX;
}
int PathGraph::GetYCenterOfTile(int id) const
{
	return m_VecTiles[id].CenterY;
}

int PathGraph::GetTileId(const Point2Int& location) const
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
bool PathGraph::IsCurrTileIntersection(const Point2Int& location) const
{	
	return m_VecTiles[GetTileId(location)].IsIntersection;
}

bool PathGraph::HasNeighbourInDirection(const Direction& dir, const Point2Int& CharacterPos, int& targetLocation) const
{
	int id{ GetTileId(CharacterPos) };
	
	for (const auto& neighbour : m_AdjacencyList[id])
	{
		switch (dir)
		{
		case Direction::Left:

			if (m_VecTiles[neighbour].CenterX < m_VecTiles[id].CenterX)
			{
				targetLocation = m_VecTiles[neighbour].CenterX;
				return true;
			}
			break;

		case Direction::Right:

			if (m_VecTiles[neighbour].CenterX > m_VecTiles[id].CenterX)
			{
				targetLocation = m_VecTiles[neighbour].CenterX;
				return true;
			}
			break;

		case Direction::Down:

			if (m_VecTiles[neighbour].CenterY < m_VecTiles[id].CenterY)
			{
				targetLocation = m_VecTiles[neighbour].CenterY;
				return true;
			}
			break;

		case Direction::Up:

			if (m_VecTiles[neighbour].CenterY > m_VecTiles[id].CenterY)
			{
				targetLocation = m_VecTiles[neighbour].CenterY;
				return true;
			}
			break;
		}

	}
	
	return false;
}

std::vector<int> PathGraph::CalculatShortestPath(const Direction& dir, const Point2Int& intersectionPos, const Point2Int& targetPos) const
{
	//This guy helped me out a lot!
	//https://www.youtube.com/watch?v=mZfyt03LDH4&t=1094s

	int target{}; 
	assert(HasNeighbourInDirection(dir, intersectionPos, target));
	
	Point2Int startPos{intersectionPos};
	switch (dir)
	{
	case Direction::Left:
		startPos.x -= Tile::Size;
		break;
	case Direction::Right:
		startPos.x += Tile::Size;
		break;
	case Direction::Down:
		startPos.y -= Tile::Size;
		break;
	case Direction::Up:
		startPos.y += Tile::Size;
		break;
	}
	int startId{ GetTileId(startPos) };
	int endId{ GetTileId(targetPos) };

	Point2Int endPos{ GetXCenterOfTile(endId), GetYCenterOfTile(endId) };

	int intersectionId{ GetTileId(intersectionPos) };

	std::map<int, Node> openNodes{};
	std::map<int, Node> closedNodes{};

	openNodes.emplace(startId, Node{.hCost = Node::CalculateCost(startPos, endPos), .tileId = startId });

	int AmountOfTiles{};
	while (!openNodes.empty())
	{
		// get the node with the lowest f_cost
		std::pair<int, Node> pair = *openNodes.cbegin();
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

		// close this node
		openNodes.erase(currentTileId);
		closedNodes.emplace(currentTileId, currentNode); 

		if (currentTileId == endId) return RetracePath(closedNodes, startId, endId);

		for (auto& neighbourTileId : m_AdjacencyList[currentTileId])
		{
			if (intersectionId == neighbourTileId or closedNodes.contains(neighbourTileId)) continue;

			Point2Int neighbourPos{ GetXCenterOfTile(neighbourTileId), GetYCenterOfTile(neighbourTileId) };
			Point2Int currentPos{ GetXCenterOfTile(currentTileId), GetYCenterOfTile(currentTileId) };

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


		++AmountOfTiles;
	}
	return std::vector<int>{};
}

std::vector<int> PathGraph::RetracePath(const std::map<int, Node>& closedNodes, int startId, int endId) const
{
	std::vector<int> path{ };
	int currentTile{closedNodes.at(endId).tileId};
	do
	{
		path.push_back(currentTile);
		currentTile = closedNodes.at(currentTile).parentId;

	} while (path.back() != startId);

	return path;
}
