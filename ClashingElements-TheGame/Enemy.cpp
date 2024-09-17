#include "Enemy.h"
#include <algorithm>

Enemy::Enemy(const Point2Int& bottomCenter, const tstring& textureFile, SpriteInfo spriteInfo) :
	Character{bottomCenter, textureFile, spriteInfo, 1},
	m_SmartnessLevel{50}
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
	}

#endif // _DEBUG

	Character::Draw();
}

void Enemy::Move(const PathGraph& graph)
{
	OutputDebugString((_T("Target:") + to_tstring(m_TargetLocation.x) + _T(',') + to_tstring(m_TargetLocation.y) + _T(" | Pos:") + to_tstring(m_BottomCenter.x) + _T(',') + to_tstring(m_BottomCenter.y) + _T('\n')).c_str());

	if (graph.IsTileIntersection(m_BottomCenter))
	{
		OutputDebugString(_T("Intersection\n"));
		
		FillDirectionMap(graph);

		CalculatePathsInAllDirections(graph);

		SortDirectionMap();

		bool choseShortestPath{ (rand() % m_MaxSmartnessLevel) < m_SmartnessLevel };
		int index{0};

		if (m_DirMap.size() > 1 and !choseShortestPath) 
			index = rand() % (m_DirMap.size() - 1) + 1;

		const auto& [direction, nrOfTilesToTarget, nextTargetPos] = m_DirMap[index];

		m_Dir = direction;
		m_TargetLocation = nextTargetPos;

		m_CurrentRow = int(m_Dir);
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
		m_DirMap.push_back(std::make_tuple(Direction::Left, 0, neighbourCenter));
	}
	if (graph.HasNeighbourInDirection(Direction::Right, m_BottomCenter, neighbourCenter))
	{
		m_DirMap.push_back(std::make_tuple(Direction::Right, 0, neighbourCenter));
	}
	if (graph.HasNeighbourInDirection(Direction::Up, m_BottomCenter, neighbourCenter))
	{
		m_DirMap.push_back(std::make_tuple(Direction::Up, 0, neighbourCenter));
	}
	if (graph.HasNeighbourInDirection(Direction::Down, m_BottomCenter, neighbourCenter))
	{
		m_DirMap.push_back(std::make_tuple(Direction::Down, 0, neighbourCenter));
	}
}

void Enemy::CalculatePathsInAllDirections(const PathGraph& graph)
{
	m_Path.clear();
	for (auto& [direction, nrOfTilesToTarget, nextTilePos] : m_DirMap)
	{
		TileID startID{ graph.GetTileId(nextTilePos) };

		auto path = graph.CalculatShortestPath(startID, graph.GetTileId(m_LastKnownPlayerPos));
		nrOfTilesToTarget = static_cast<int>(path.size());

		m_Path.reserve(path.size() * 4);
		for (auto& tileId : path)
		{
			m_Path.push_back(graph.GetCenterOfTile(tileId));
		}
	}
}

void Enemy::SortDirectionMap()
{
	std::sort(m_DirMap.begin(), m_DirMap.end(), [](const std::tuple<Direction, int, Point2Int>& tuple1, const std::tuple<Direction, int, Point2Int>& tuple2)
		{
			const auto& [direction1, nrOfTiles1, nextPos1] = tuple1;
			const auto& [direction2, nrOfTiles2, nextPos2] = tuple2;
			return nrOfTiles1 < nrOfTiles2 and (nrOfTiles1 > 0);
		});
	std::partition(m_DirMap.begin(), m_DirMap.end(), [](const std::tuple<Direction, int, Point2Int>& tuple1)
		{
			const auto& [direction1, nrOfTiles1, nextPos1] = tuple1;
			return nrOfTiles1 > 0;
		});
}
