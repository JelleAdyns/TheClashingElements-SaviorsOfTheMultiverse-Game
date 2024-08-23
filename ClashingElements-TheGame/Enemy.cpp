#include "Enemy.h"

Enemy::Enemy(const Point2Int& bottomCenter, int nrCols, int nrFrames, float frameTime) :
	Character{bottomCenter, nrCols,nrFrames,frameTime},
	m_SmartnessLevel{0}
{

}

void Enemy::Draw() const
{
	Character::Draw();

	int halfTile = Tile::Size / 2;
	ENGINE.SetColor(RGB(0, 255, 0));
	for (auto& center : m_Path)
	{
		ENGINE.FillRectangle(center.x - Tile::Size / 2, center.y - Tile::Size / 2, Tile::Size, Tile::Size);
	}
}

void Enemy::Move(const PathGraph& graph)
{
	OutputDebugString((_T("Target:") + to_tstring(m_TargetLocation.x) + _T(',') + to_tstring(m_TargetLocation.y) + _T(" | Pos:") + to_tstring(m_BottomCenter.x) + _T(',') + to_tstring(m_BottomCenter.y) + _T('\n')).c_str());

	if (graph.IsCurrTileIntersection(m_BottomCenter))
	{
		OutputDebugString(_T("Intersection\n"));
		m_DirMap.clear();
		int target{};
		if (graph.HasNeighbourInDirection(Direction::Left, m_BottomCenter, target))
		{
			m_DirMap.push_back(std::make_pair(Direction::Left, target));
		}
		if (graph.HasNeighbourInDirection(Direction::Right, m_BottomCenter, target))
		{
			m_DirMap.push_back(std::make_pair(Direction::Right, target));
		}
		if (graph.HasNeighbourInDirection(Direction::Up, m_BottomCenter, target))
		{
			m_DirMap.push_back(std::make_pair(Direction::Up, target));
		}
		if (graph.HasNeighbourInDirection(Direction::Down, m_BottomCenter, target))
		{
			m_DirMap.push_back(std::make_pair(Direction::Down, target));
		}


		int index{rand() % int(m_DirMap.size())};

		m_Dir = m_DirMap[index].first;
		m_Path.clear();
		auto path = graph.CalculatShortestPath(m_Dir, m_BottomCenter, Point2Int{72,664});
		m_Path.reserve(path.size());
		for (auto& tileId : path)
		{
			m_Path.push_back(Point2Int{ graph.GetXCenterOfTile(tileId), graph.GetYCenterOfTile(tileId) });
		}
		}


		int index{rand() % int(m_DirMap.size())};
		const auto& [direction, targetCoord] = m_DirMap[index];

		m_Dir = direction;
		if (m_Dir == Direction::Down || m_Dir == Direction::Up) m_TargetLocation.y = targetCoord;
		else m_TargetLocation.x = targetCoord;

	}
	else 
	{
		int target{};
		if (graph.HasNeighbourInDirection(m_Dir, m_BottomCenter, target))
		{
			if (m_Dir == Direction::Down || m_Dir == Direction::Up) m_TargetLocation.y = target;
			else m_TargetLocation.x = target;
		}

	}
	m_IsMoving = true;

}
