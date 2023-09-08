#include "pch.h"
#include "Level.h"
#include "Character.h"
#include "PathGraph.h"
#include "PalmTree.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <utils.h>
#include <map>


Level::Level(Character* pCharacter, float viewportWidth, float viewportHeight) :
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
	m_Graph{},
	m_Camera{viewportWidth, viewportHeight}
{

	m_pPlayer = pCharacter;
	m_pPlayer->Play();
	LoadStage();
	
	m_pVecSprites.push_back(new PalmTree{ Point2f{434, 704} });
	m_pVecSprites.push_back(new PalmTree{ Point2f{566, 704} });


	

}

Level::~Level()
{

	delete m_pAnimBackGround;
	m_pAnimBackGround = nullptr;
	delete m_pBackGround;
	m_pBackGround = nullptr;

	for (auto& pCollectable : m_pVecCollectables)
	{
		delete pCollectable;
		pCollectable = nullptr;
	}
	for (auto& pSprite : m_pVecSprites)
	{
		delete pSprite;
		pSprite = nullptr;
	}

	delete m_pPlayer;
	m_pPlayer = nullptr;
	m_pBackGroundMusic->Stop();
	delete m_pBackGroundMusic;
	m_pBackGroundMusic = nullptr;

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


		m_pPlayer->Move(m_Graph, elapsedSec);
		m_pPlayer->Update(elapsedSec);
		if (m_pPlayer->IsMoving()) HitCollectable();

		m_Camera.Update(m_pPlayer->DestRect());

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

	std::vector<AnimatedSprite*> pVecSprites{};

	for (const auto& pCollectable : m_pVecCollectables)
	{
		pVecSprites.push_back(pCollectable);
	}
	pVecSprites.push_back(m_pPlayer);

	std::multimap<float,int> YMap{};
	for (int i = 0; i < pVecSprites.size(); i++)
	{
		YMap.insert(std::make_pair(pVecSprites[i]->DestRect().bottom,i ));
	}

	std::vector<int> VecIndexes{};
	for (const std::pair<const float, const int>& p : YMap)
	{
		VecIndexes.push_back(p.second);
	}

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
		for (int i = int(VecIndexes.size() - 1); i >= 0; --i)
		{
			pVecSprites[VecIndexes[i]]->Draw();
		}
		for (const auto& pSprite : m_pVecSprites)
		{
			pSprite->Draw();
		}
	}
	glPopMatrix();

}

void Level::HitCollectable()
{
	std::cout << "collect" << std::endl;
	for (int i = 0; i < m_pVecCollectables.size(); i++)
	{
		if (utils::IsOverlapping(m_pPlayer->GetHitBox(), m_pVecCollectables[i]->GetHitBox()))
		{
			if (m_StageNumber == 0)
			{
				for (int i = 0; i < m_pVecCollectables.size(); i++)
				{
					delete m_pVecCollectables[i];
					m_pVecCollectables[i] = nullptr;
				}
				m_pVecCollectables.clear();
			}
			else if (m_StageNumber == 1)
			{
				delete m_pVecCollectables[i];
				m_pVecCollectables[i] = m_pVecCollectables[m_pVecCollectables.size() - 1];
				m_pVecCollectables.pop_back();
			}
			
			
		}
	}	

}

void Level::LoadStage()
{
	m_Graph = std::move(PathGraph{});
	m_pAnimBackGround = new AnimBackGround{m_VecBackGrounds[m_StageNumber].first};
	m_Camera.SetLevelBoundaries(m_pAnimBackGround->DestRect());
	m_pBackGround = new BackGround{ m_VecBackGrounds[m_StageNumber].second.second, m_VecBackGrounds[m_StageNumber].second.first ,0.7f };
	m_pBackGroundMusic = new SoundStream{ m_VecMusic[m_StageNumber]};
	//m_pBackGroundMusic->Play(true);
	

	std::ifstream inputFile{"StagePatternTest.txt"};

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

		std::string possibleSymbols{ ".,P" };

		while (rowString.find_first_of(possibleSymbols,col) != std::string::npos)
		{
			col = int(rowString.find_first_of(possibleSymbols, col));

			int xCenter{ Tile::Size / 2 + Tile::Size * col };
			int yCenter{ Tile::Size / 2 + Tile::Size * row };

			bool isIntersection{};

			switch (rowString[col])
			{
			case '.':
				break;
			case 'P':
				m_pPlayer->SetPos(Point2f{ float(xCenter), float(yCenter) });
			case ',':
				isIntersection = true;
				break;
			}

			m_Graph.AddTile(currTileId, xCenter, yCenter, isIntersection);
			if(rowString[col] != 'P') m_pVecCollectables.push_back(new Collectable{Point2f{float(xCenter),float(yCenter)}});

			int previousColTileId{ m_Graph.GetTileId(Point2f{ float(xCenter) - Tile::Size, float(yCenter) }) };
			if(previousColTileId >= 0) m_Graph.AddEdge(currTileId, previousColTileId);
			
			int previousRowTileId{ m_Graph.GetTileId(Point2f{ float(xCenter), float(yCenter + Tile::Size) }) };
			if(previousRowTileId >= 0) m_Graph.AddEdge(currTileId, previousRowTileId);


			++currTileId;
			++col;
		}
	}
}


void Level::Reset()
{
	delete m_pAnimBackGround;
	delete m_pBackGround;

	for (auto& pSprite : m_pVecSprites)
	{
		delete pSprite;
	}
	m_pVecSprites.clear();

	delete m_pBackGroundMusic;
}