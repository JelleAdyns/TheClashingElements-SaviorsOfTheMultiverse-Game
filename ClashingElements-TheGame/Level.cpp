#include "Level.h"
#include "Player.h"
#include "Boss.h"
#include "Minion.h"
#include "PathGraph.h"
#include "PalmTree.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>


Level::Level(std::shared_ptr<Player> pPlayer, int viewportWidth, int viewportHeight) :
	m_VecBackGrounds
	{
		{ _T("Mall.png")      , {_T("BGMall.png")      ,Point2Int{0, 300}} },
		{ _T("GloirbnPit.png"), {_T("GloirbnPit.png"),Point2Int{0, 300}} }
    },

	m_VecMusic
	{
		_T("Sounds/Spaceship.wav"),
		_T("Sounds/Spaceship.wav")
	},

	m_StageNumber{ 0 },
	m_LoopNumber{ 0 },
	m_Hud{viewportWidth, viewportHeight},
	m_Camera{viewportWidth, viewportHeight - HUD::GetHudHeight()}
{
	m_pPlayer = pPlayer;
	m_pPlayer->Play();
	LoadStage();
}

Level::~Level()
{

	//delete m_pAnimBackGround;
	//m_pAnimBackGround = nullptr;
	//delete m_pBackGround;
	//m_pBackGround = nullptr;

	//for (auto& pCollectable : m_pVecCollectables)
	//{
	//	delete pCollectable;
	//	pCollectable = nullptr;
	//}
	//for (auto& pSprite : m_pVecSprites)
	//{
	//	delete pSprite;
	//	pSprite = nullptr;
	//}
	//for (auto& pEnemy : m_pVecEnemies)
	//{
	//	delete pEnemy;
	//	pEnemy = nullptr;
	//}
	//
	//delete m_pPlayer;
	//m_pPlayer = nullptr;
	//m_pBackGroundMusic->Stop();
	//delete m_pBackGroundMusic;
	//m_pBackGroundMusic = nullptr;

}

void Level::Tick()
{
	if (!m_pVecCollectables.empty())
	{
		m_pAnimBackGround->Update();

		for (const auto& pCollectable : m_pVecCollectables)
		{
			pCollectable->Update();
		}
		for (const auto& pSprite : m_pVecSprites)
		{
			pSprite->Update();
		}
		for (const auto& pEnemy : m_pVecEnemies)
		{
			pEnemy->Update();
			if (!pEnemy->IsMoving()) pEnemy->Move(m_Graph);
		}

		m_pPlayer->Move(m_Graph);
		m_pPlayer->Update();
		if (m_pPlayer->IsMoving()) HitCollectable();

		m_Camera.Update(m_pPlayer->DestRect());
		SetUpDrawBuffer();
	}
	else
	{
		Reset();
		++m_StageNumber;
		LoadStage();
	}

	
}

void Level::Draw() const
{
	
	ENGINE.PushTransform();
	m_Camera.Transform(m_pBackGround->GetParallaxSpeed());
	m_pBackGround->Draw();
	ENGINE.PopTransform();

	
	ENGINE.PushTransform();
	m_Camera.Transform();
		
	m_pAnimBackGround->Draw();
	m_Graph.Draw();
	/*for (int i = int(VecIndexes.size() - 1); i >= 0; --i)
	{
		pVecSprites[VecIndexes[i]]->Draw();
	}*/
	for (const auto& pSprite : m_pDrawBuffer)
	{
		pSprite->Draw();
	}
	for (const auto& pSprite : m_pVecSprites)
	{
		pSprite->Draw();
	}
	ENGINE.PopTransform();

	m_Hud.Draw();
}

void Level::SetUpDrawBuffer()
{
	m_pDrawBuffer.clear();
	m_pDrawBuffer.reserve(m_pVecCollectables.size() + m_pVecEnemies.size() + 1);

	m_pDrawBuffer.insert(m_pDrawBuffer.end(), m_pVecCollectables.cbegin(), m_pVecCollectables.cend());
	m_pDrawBuffer.insert(m_pDrawBuffer.end(), m_pVecEnemies.cbegin(), m_pVecEnemies.cend());
	m_pDrawBuffer.push_back(m_pPlayer);

	std::sort(m_pDrawBuffer.begin(), m_pDrawBuffer.end(), [](const std::shared_ptr<AnimatedSprite>& sprite1, const std::shared_ptr<AnimatedSprite>& sprite2)
		{
			return sprite1->DestRect().bottom > sprite2->DestRect().bottom;
		});
}

void Level::HitCollectable()
{
	OutputDebugString(_T("Collect"));
	//m_pVecCollectables.erase(std::remove_if(m_pVecCollectables.begin(), m_pVecCollectables.end(), std::bind( &Level::Test , this, std::placeholders::_1)),
	//	m_pVecCollectables.end());

	m_pVecCollectables.erase(std::remove_if(m_pVecCollectables.begin(), m_pVecCollectables.end(), [&](const std::shared_ptr<Collectable>& collectable)
			{
				return utils::IsOverlapping(m_pPlayer->GetHitBox(), collectable->GetHitBox());
			}),
		m_pVecCollectables.end());

	//for (int i = 0; i < m_pVecCollectables.size(); i++)
	//{
	//	if (utils::IsOverlapping(m_pPlayer->GetHitBox(), m_pVecCollectables[i]->GetHitBox()))
	//	{
	//		/*if (m_StageNumber == 0)
	//		{
	//			for (int i = 0; i < m_pVecCollectables.size(); i++)
	//			{
	//				delete m_pVecCollectables[i];
	//				m_pVecCollectables[i] = nullptr;
	//			}
	//			m_pVecCollectables.clear();
	//		}
	//		else if (m_StageNumber == 1)
	//		{
	//		}*/
	//			delete m_pVecCollectables[i];
	//			m_pVecCollectables[i] = m_pVecCollectables[m_pVecCollectables.size() - 1];
	//			m_pVecCollectables.pop_back();
	//		
	//	}
	//}	
				m_Hud.SetNrCollectables(int(m_pVecCollectables.size()));

}

void Level::LoadStage()
{
	m_Graph = std::move(PathGraph{});
	m_pAnimBackGround = std::make_unique<AnimBackGround>(m_VecBackGrounds[m_StageNumber].first);
	m_Camera.SetLevelBoundaries(m_pAnimBackGround->DestRect());
	m_pBackGround = std::make_unique < BackGround >( m_VecBackGrounds[m_StageNumber].second.second, m_VecBackGrounds[m_StageNumber].second.first ,0.8f );
	//m_pBackGroundMusic->Play(true);
	

	tifstream inputFile{ ENGINE.GetResourcePath() + L"StagePattern.txt" };

	tstring info{};

	tstringstream stageTest{};
	while (getline(inputFile, info, _T('/')))
	{
		if (info.find(_T("Stage " + to_tstring(m_StageNumber))) != tstring::npos)
		{
			info.erase(0, info.find(to_tstring(m_StageNumber) + _T('\n')));
			stageTest << info;
		}
	}

	int currTileId{};
	while (getline(stageTest, info))
	{
		tstring rowString{};
		tstringstream infoStream{info};
		getline(infoStream, rowString, _T('\"'));
		int row{ std::stoi(rowString) };
		int col{};

		getline(infoStream, rowString);

		const tstring possibleSymbols{ _T(".,PTBM") };

		while (rowString.find_first_of(possibleSymbols,col) != tstring::npos)
		{
		
			col = int(rowString.find_first_of(possibleSymbols, col));

			Point2Int center
			{ 
				Tile::Size / 2 + Tile::Size * col, 
				Tile::Size / 2 + Tile::Size * row
			};

			bool isIntersection{};

			switch (rowString[col])
			{
			case _T('T'):
				m_pVecSprites.push_back(std::make_unique<PalmTree>( center ));
				break;
			case _T('P'):

				m_pPlayer->SetPos(center);

			case _T('B'):

				if (rowString[col] != _T('P')) m_pVecEnemies.push_back(std::make_shared<Boss>( center, Player::m_DefaultSpeed ));

			case _T('M'):

				//if (rowString[col] != _T('P') && rowString[col] != _T('B')) m_pVecEnemies.push_back(std::make_shared<Minion>(center));

			case _T(','):

				isIntersection = true;

			case _T('.'):

				m_Graph.AddTile(currTileId, int(round(center.x)), int(round(center.y)), isIntersection);
				if(rowString[col] != _T('P')) m_pVecCollectables.push_back(std::make_shared<Collectable>(center));

				int previousColTileId{ m_Graph.GetTileId(Point2Int{ center.x - Tile::Size, center.y }) };
				if(previousColTileId >= 0) m_Graph.AddEdge(currTileId, previousColTileId);
				
				int previousRowTileId{ m_Graph.GetTileId(Point2Int{ center.x, center.y + Tile::Size }) };
				if(previousRowTileId >= 0) m_Graph.AddEdge(currTileId, previousRowTileId);

				++currTileId;


				break;
			}


			++col;
		}
	}
	m_Hud.SetNrCollectables(int(m_pVecCollectables.size()));

	m_pDrawBuffer.clear();
	m_pDrawBuffer.reserve(m_pVecCollectables.size() + m_pVecEnemies.size() + 1);
}


void Level::Reset()
{
	//delete m_pAnimBackGround;
	//delete m_pBackGround;

	//for (auto& pSprite : m_pVecSprites)
	//{
	//	delete pSprite;
	//}
	m_pVecSprites.clear();
	//for (auto& pEnemy : m_pVecEnemies)
	//{
	//	delete pEnemy;
	//}
	m_pVecEnemies.clear();

	//delete m_pBackGroundMusic;
}