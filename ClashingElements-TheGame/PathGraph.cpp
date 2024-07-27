#include "PathGraph.h"

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
		if (dir == Direction::Left)
		{
			if (m_VecTiles[neighbour].CenterX < m_VecTiles[id].CenterX)
			{
				targetLocation = m_VecTiles[neighbour].CenterX;
				return true;
			}
		}

		if (dir == Direction::Right)
		{
			if (m_VecTiles[neighbour].CenterX > m_VecTiles[id].CenterX)
			{
				targetLocation = m_VecTiles[neighbour].CenterX;
				return true;
			}
		}

		if (dir == Direction::Down)
		{
			if (m_VecTiles[neighbour].CenterY < m_VecTiles[id].CenterY)
			{
				targetLocation = m_VecTiles[neighbour].CenterY;
				return true;
			}
		}

		if (dir == Direction::Up)
		{
			if (m_VecTiles[neighbour].CenterY > m_VecTiles[id].CenterY)
			{
				targetLocation = m_VecTiles[neighbour].CenterY;
				return true;
			}
		}

	}
	
	return false;
}