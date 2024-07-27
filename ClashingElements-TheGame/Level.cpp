#include "pch.h"
#include "Level.h"
#include "Player.h"
#include "Boss.h"
#include "Minion.h"
#include "PathGraph.h"
#include "PalmTree.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <utils.h>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>


Level::Level(std::shared_ptr<Player> pPlayer, float viewportWidth, float viewportHeight) :
	m_VecBackGrounds
	{ 
		{ "Mall.png"      , {"BGMall.png"      ,Point2f{0, 300}} },
		{ "GloirbnPit.png", {"BGGloirbnPit.png",Point2f{0, 300}} }  
    },

	m_VecMusic
	{
		"Sounds/Spaceship.wav",
		"Sounds/Spaceship.wav"
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
	m_pBackGroundMusic->Stop();
	//delete m_pBackGroundMusic;
	//m_pBackGroundMusic = nullptr;

}

void Level::Update(float elapsedSec)
{
	if (!m_pVecCollectables.empty())
	{
		m_pAnimBackGround->Update(elapsedSec);

		for (const auto& pCollectable : m_pVecCollectables)
		{
			pCollectable->Update(elapsedSec);
		}
		for (const auto& pSprite : m_pVecSprites)
		{
			pSprite->Update(elapsedSec);
		}
		for (const auto& pEnemy : m_pVecEnemies)
		{
			pEnemy->Update(elapsedSec);
			if(!pEnemy->IsMoving()) pEnemy->Move(m_Graph, elapsedSec);
		}

		
		m_pPlayer->Move(m_Graph, elapsedSec);
		m_pPlayer->Update(elapsedSec);
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

	//std::vector<AnimatedSprite*> pVecSprites{};
	//pVecSprites.reserve(m_pVecCollectables.size() + m_pVecEnemies.size() + 1);
	//pVecSprites.insert(pVecSprites.end(), m_pVecCollectables.cbegin(), m_pVecCollectables.cend());
	//pVecSprites.insert(pVecSprites.end(), m_pVecEnemies.cbegin(), m_pVecEnemies.cend());
	//pVecSprites.push_back(m_pPlayer);
	//std::merge(m_pVecEnemies.begin(), m_pVecEnemies.end(), m_pVecCollectables.begin(), m_pVecCollectables.end(), pVecSprites);
	//std::sort(pVecSprites.cbegin(), pVecSprites.cend(), std::bind(std::less<float>{}, std::placeholders::_1, std::placeholders::_2))
	//auto it = std::copy(m_pVecCollectables.cbegin(), m_pVecCollectables.cend(), pVecSprites.begin());
	//std::copy(m_pVecEnemies.cbegin(), m_pVecEnemies.cend(), it);
	//pVecSprites.push_back(m_pPlayer);
	//for (const auto& pCollectable : m_pVecCollectables)
	//{
	//	pVecSprites.push_back(pCollectable);
	//}
	//for (const auto& pEnemy : m_pVecEnemies)
	//{
	//	pVecSprites.push_back(pEnemy);
	//}


	//std::multimap<float,int> YMap{};
	//for (int i = 0; i < pVecSprites.size(); i++)
	//{
	//	YMap.insert(std::make_pair(pVecSprites[i]->DestRect().bottom,i ));
	//}
	//
	//std::vector<int> VecIndexes{};
	//for (const std::pair<const float, const int>& p : YMap)
	//{
	//	VecIndexes.push_back(p.second);
	//}

	glPushMatrix();
	{
		m_Camera.Transform(m_pBackGround->GetParallaxSpeed());
		m_pBackGround->Draw();
	}
	glPopMatrix();

	glPushMatrix();
	{
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
	}
	glPopMatrix();

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
	std::cout << "collect" << std::endl;
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
	m_pBackGroundMusic = std::make_unique < SoundStream >( m_VecMusic[m_StageNumber]);
	//m_pBackGroundMusic->Play(true);
	

	std::ifstream inputFile{"StagePattern.txt"};

	std::string info{};

	std::stringstream stageTest{};
	while (getline(inputFile, info, '/'))
	{
		if (info.find("Stage " + std::to_string(m_StageNumber)) != std::string::npos)
		{
			info.erase(0, info.find(std::to_string(m_StageNumber) + '\n'));
			stageTest << info;
		}
	}

	int currTileId{};
	while (getline(stageTest, info))
	{
		std::string rowString{};
		std::stringstream infoStream{info};
		getline(infoStream, rowString, '\"');
		int row{ std::stoi(rowString) };
		int col{};

		getline(infoStream, rowString);

		const std::string possibleSymbols{ ".,PTBM" };

		while (rowString.find_first_of(possibleSymbols,col) != std::string::npos)
		{
		
			col = int(rowString.find_first_of(possibleSymbols, col));

			Point2f center
			{ 
				float(round(Tile::Size / 2 + Tile::Size * col)), 
				float(round(Tile::Size / 2 + Tile::Size * row))
			};

			bool isIntersection{};

			switch (rowString[col])
			{
			case 'T':
				m_pVecSprites.push_back(std::make_unique<PalmTree>( center ));
				break;
			case 'P':

				m_pPlayer->SetPos(center);

			case 'B':

				if (rowString[col] != 'P') m_pVecEnemies.push_back(std::make_shared<Boss>( center, Player::m_DefaultSpeed ));

			case 'M':

				if (rowString[col] != 'P' && rowString[col] != 'B') m_pVecEnemies.push_back(std::make_shared<Minion>(center));

			case ',':

				isIntersection = true;

			case '.':

				m_Graph.AddTile(currTileId, int(round(center.x)), int(round(center.y)), isIntersection);
				if(rowString[col] != 'P') m_pVecCollectables.push_back(std::make_shared<Collectable>(center));

				int previousColTileId{ m_Graph.GetTileId(Point2f{ center.x - Tile::Size, center.y }) };
				if(previousColTileId >= 0) m_Graph.AddEdge(currTileId, previousColTileId);
				
				int previousRowTileId{ m_Graph.GetTileId(Point2f{ center.x, center.y + Tile::Size }) };
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