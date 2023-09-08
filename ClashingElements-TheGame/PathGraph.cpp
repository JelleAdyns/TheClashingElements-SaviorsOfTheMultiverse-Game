#include "pch.h"
#include "PathGraph.h"
#include <utils.h>


void PathGraph::Draw() const
{
	for (const Tile& tile : m_VecTiles)
	{
		utils::DrawRect(tile.Area);
	}
	for (const std::vector<int>& vector : m_AdjacencyList)
	{
		std::vector<Point2f> points{};
		for (const int id : vector)
		{
			points.push_back(Point2f{ float(GetXCenterOfTile(id)), float(GetYCenterOfTile(id)) });
		}
		utils::DrawPolygon(points);
	}
	for (const Escalator& area : m_VecEscalators)
	{
		utils::DrawRect(area.Area);
		utils::DrawRect(area.TargetRect);
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
void PathGraph::AddEscalator(const Point2f& startCenter, const Point2f& endCenter, bool isDownwards)
{
	m_VecEscalators.push_back(Escalator{ startCenter, endCenter, isDownwards });
}

int PathGraph::GetXCenterOfTile(int id) const
{
	return m_VecTiles[id].CenterX;
}
int PathGraph::GetYCenterOfTile(int id) const
{
	return m_VecTiles[id].CenterY;
}
//int PathGraph::GetNrOfTiles() const
//{
//	return int(m_VecTiles.size());
//}

int PathGraph::GetTileId(const Point2f& location) const
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
bool PathGraph::HasNeighbourInDirection(const Direction& dir, const Point2f& playerPos, int& targetLocation) const
{
	int id{ GetTileId(playerPos) };
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
float PathGraph::GetEscalatorVelocity(const Point2f& playerPos, int& targetY) const
{
	if (!m_VecEscalators.empty())
	{
		for (const auto& pEscalator : m_VecEscalators)
		{
			bool isInArea{ utils::IsPointInRect(playerPos, pEscalator.Area) };
			if (utils::IsPointInRect(playerPos, pEscalator.Area)) return float(pEscalator.Velocity);
			if (utils::IsPointInRect(playerPos, pEscalator.TargetRect)) targetY = int(pEscalator.TargetRect.bottom);
		}
	}
	
	return 0;
}