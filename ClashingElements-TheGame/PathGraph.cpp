#include "pch.h"
#include "PathGraph.h"
#include <utils.h>


void PathGraph::Draw() const
{
	for (const Tile& tile : m_VecTiles)
	{
		utils::DrawRect(tile.Area);
	}
}

void PathGraph::AddTile(const int id, const int centerX, const int centerY, const bool isIntersection)
{
	m_VecTiles.push_back(Tile{ id, centerX, centerY, isIntersection });
	m_AdjacencyList.push_back(std::vector<int>{});
}
void PathGraph::AddEdge(const int srcTileId, const int neighbourId)
{
	m_AdjacencyList[srcTileId].push_back(neighbourId);
	m_AdjacencyList[neighbourId].push_back(srcTileId);
}

int PathGraph::GetXCenterOfTile(const int id) const
{
	return m_VecTiles[id].CenterX;
}
int PathGraph::GetYCenterOfTile(const int id) const
{
	return m_VecTiles[id].CenterY;
}
int PathGraph::GetNrOfTiles() const
{
	return int(m_VecTiles.size());
}

int PathGraph::GetTileId(const Point2f& playerPos) const
{
	for (const auto& tile : m_VecTiles)
	{
		if (utils::IsPointInRect(playerPos, tile.Area))
		{
			return tile.Id;
		}
	}
	return 0;
}
bool PathGraph::HasNeighbourInDirection(const Vector2f& dir, const Point2f& playerPos, int& targetLocation) const
{
	int id{ GetTileId(playerPos) };
	for (const auto& neighbour : m_AdjacencyList[id])
	{
		if (dir.x < 0)
		{
			if (m_VecTiles[neighbour].CenterX < m_VecTiles[id].CenterX)
			{
				targetLocation = m_VecTiles[neighbour].CenterX;
				return true;
			}
		}
				
		if (dir.x > 0)
		{
			if (m_VecTiles[neighbour].CenterX > m_VecTiles[id].CenterX)
			{
				targetLocation = m_VecTiles[neighbour].CenterX;
				return true;
			}
		}
				
		if (dir.y < 0)
		{
			if (m_VecTiles[neighbour].CenterY < m_VecTiles[id].CenterY)
			{
				targetLocation = m_VecTiles[neighbour].CenterY;
				return true;
			}
		}

		if (dir.y > 0)
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