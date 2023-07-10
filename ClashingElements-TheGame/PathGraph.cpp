#include "pch.h"
#include "PathGraph.h"
#include "utils.h"


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
	//if (srcTileId > m_AdjacencyList.size() - 1)m_AdjacencyList.push_back(std::vector<int>{});
	m_AdjacencyList[srcTileId].push_back(neighbourId);
	//if (neighbourId > m_AdjacencyList.size() - 1)m_AdjacencyList.push_back(std::vector<int>{});
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