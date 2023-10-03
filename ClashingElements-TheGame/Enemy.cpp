#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(const Point2f& bottomCenter, int nrCols, int nrFrames, float frameTime) :
	Character{bottomCenter, nrCols,nrFrames,frameTime},
	m_SmartnessLevel{0}
{

}

void Enemy::Move(const PathGraph& graph, float elapsedSec)
{

	if (graph.IsCurrTileIntersection(m_BottomCenter))
	{
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

		int targetCoordinate{ m_DirMap[index].second };

		if (m_Dir == Direction::Down || m_Dir == Direction::Up) m_TargetYLocation = targetCoordinate;
		else m_TargetXLocation = targetCoordinate;

	}
	else 
	{
		int target{};
		if (graph.HasNeighbourInDirection(m_Dir, m_BottomCenter, target))
		{
			if (m_Dir == Direction::Down || m_Dir == Direction::Up) m_TargetYLocation = target;
			else m_TargetXLocation = target;
		}

	}
	m_IsMoving = true;

}
