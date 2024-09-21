#include "Enemy.h"
#include <algorithm>

Enemy::Enemy(const Point2Int& bottomCenter, const tstring& textureFile, SpriteInfo spriteInfo, uint8_t startSmartness) :
	Character{bottomCenter, textureFile, spriteInfo, 1},
	m_StartSmartnessLevel{startSmartness},
	m_SmartnessLevel{m_StartSmartnessLevel}
{

}

void Enemy::Draw() const
{
#ifdef _DEBUG

	if (ENGINE.IsKeyPressed('Z'))
	{
		ENGINE.SetColor(RGB(0, 255, 0), .2f);
		for (auto& center : m_Path)
		{
			ENGINE.FillRectangle(center.x - Tile::Size / 2, center.y - Tile::Size / 2, Tile::Size, Tile::Size);
		}

		ENGINE.SetColor(RGB(255, 0, 0));
		ENGINE.DrawCircle(CircleInt{ m_BottomCenter, m_VisionRadius }, 2.f);
	}

#endif // _DEBUG

	Character::Draw();
}

void Enemy::Move(const PathGraph& graph)
{
	OutputDebugString((_T("Target:") + to_tstring(m_TargetLocation.x) + _T(',') + to_tstring(m_TargetLocation.y) + _T(" | Pos:") + to_tstring(m_BottomCenter.x) + _T(',') + to_tstring(m_BottomCenter.y) + _T('\n')).c_str());
	
	m_SmartnessLevel = m_StartSmartnessLevel;

	if (utils::IsPointInCircle(m_LastKnownPlayerPos, CircleInt{ m_BottomCenter, m_VisionRadius }))
	{
		uint8_t addedSmartness = static_cast<uint8_t>((m_MaxSmartnessLevel - m_SmartnessLevel) * m_VisionGainPercentage);
		m_SmartnessLevel += addedSmartness;
	}

	if (graph.IsTileIntersection(m_BottomCenter))
	{
		OutputDebugString(_T("Intersection\n"));
		
		FillDirectionMap(graph);

		CalculatePathsInAllDirections(graph);

		SortDirectionMap();

		ChoosePath();
	}
	else 
	{
		Point2Int target{};
		if (graph.HasNeighbourInDirection(m_Dir, m_BottomCenter, target))
		{
			m_TargetLocation = target;
		}

	}
	m_IsMoving = true;

}

void Enemy::SetTarget(const Point2Int& playerTarget)
{
	m_LastKnownPlayerPos = playerTarget;
}

void Enemy::FillDirectionMap(const PathGraph& graph)
{
	m_DirMap.clear();
	Point2Int neighbourCenter{};
	if (graph.HasNeighbourInDirection(Direction::Left, m_BottomCenter, neighbourCenter))
	{
		m_DirMap.push_back(DirInfo{ Direction::Left, 0, neighbourCenter });
	}
	if (graph.HasNeighbourInDirection(Direction::Right, m_BottomCenter, neighbourCenter))
	{
		m_DirMap.push_back(DirInfo{Direction::Right, 0, neighbourCenter});
	}
	if (graph.HasNeighbourInDirection(Direction::Up, m_BottomCenter, neighbourCenter))
	{
		m_DirMap.push_back(DirInfo{Direction::Up, 0, neighbourCenter});
	}
	if (graph.HasNeighbourInDirection(Direction::Down, m_BottomCenter, neighbourCenter))
	{
		m_DirMap.push_back(DirInfo{Direction::Down, 0, neighbourCenter});
	}
}

void Enemy::CalculatePathsInAllDirections(const PathGraph& graph)
{
	m_Path.clear();
	for (DirInfo& dirInfo : m_DirMap)
	{
		TileID startID{ graph.GetTileId(dirInfo.nextTargetPos) };

		auto path = graph.CalculatShortestPath(startID, graph.GetTileId(m_LastKnownPlayerPos));
		dirInfo.nrOfTiles = static_cast<int>(path.size());

		m_Path.reserve(path.size() * 4);
		for (auto& tileId : path)
		{
			m_Path.push_back(graph.GetCenterOfTile(tileId));
		}
	}
}

void Enemy::SortDirectionMap()
{
	std::sort(m_DirMap.begin(), m_DirMap.end(), [](const DirInfo& tuple1, const DirInfo& tuple2)
		{
			return tuple1.nrOfTiles < tuple2.nrOfTiles and (tuple1.nrOfTiles > 0);
		});
	std::partition(m_DirMap.begin(), m_DirMap.end(), [](const DirInfo& tuple1)
		{
			return tuple1.nrOfTiles > 0;
		});
}

void Enemy::ChoosePath()
{

	bool choseShortestPath{ (rand() % m_MaxSmartnessLevel) < m_SmartnessLevel };

	while (not choseShortestPath and m_DirMap.size() > 1)
	{
		m_DirMap.pop_front();
		choseShortestPath = (rand() % m_MaxSmartnessLevel) < m_SmartnessLevel;
	}

	const DirInfo& dirInfo = m_DirMap.front();

	m_Dir = dirInfo.dir;
	m_TargetLocation = dirInfo.nextTargetPos;

	m_CurrentRow = int(m_Dir);
}
