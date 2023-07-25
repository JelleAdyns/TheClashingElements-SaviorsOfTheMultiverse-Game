#include "pch.h"
#include "Level.h"
#include "Character.h"
#include "PathGraph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <utils.h>


Level::Level(Character* pCharacter) :
	m_StageNumber{ 2 },
	m_LoopNumber{ 0 },
	m_pGraph{}
{
	
	m_pPlayer = pCharacter;
	m_pPlayer->Play();
	LoadStage();
	m_VecTestSprites.push_back(new BackGround{ Point2f{500, 0}, "Mall.png" });
	m_pBackGroundMusic = new SoundStream{ "Sounds/Spaceship.wav" };
	m_pBackGroundMusic->Play(true);
}

Level::~Level()
{
	for (auto& sprite : m_VecTestSprites)
	{
		delete sprite;
		sprite = nullptr;
	}
	for (auto& pCollectable : m_pVecCollectables)
	{
		delete pCollectable;
		pCollectable = nullptr;;
	}
	for (auto& pEscalator : m_pVecEscalators)
	{
		delete pEscalator;
		pEscalator = nullptr;;
	}
	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_pBackGroundMusic;
	m_pBackGroundMusic = nullptr;

}

void Level::Update(float elapsedSec)
{
	for (const auto& pSprite : m_VecTestSprites)
	{
		pSprite->Update(elapsedSec);
	}
	for (const auto& pCollectable : m_pVecCollectables)
	{
		pCollectable->Update(elapsedSec);
	}
	for (const auto& pEscalator : m_pVecEscalators)
	{
		if (utils::IsPointInRect(m_pPlayer->GetHitBox().center, pEscalator->Area)) m_pPlayer->SetSpeed(pEscalator->Velocity);
	}

	m_pPlayer->Move(m_pGraph);
	m_pPlayer->Update(elapsedSec);
	m_pPlayer->SetSpeed(0);
	if(m_pPlayer->IsMoving()) HitCollectable();
	
}

void Level::Draw() const
{
	for (const auto& pSprite : m_VecTestSprites)
	{
		pSprite->Draw();
	}
	m_pGraph.Draw();
	for (const auto& pCollectable : m_pVecCollectables)
	{
		pCollectable->Draw();
	}
	m_pPlayer->Draw();

}

Rectf Level::GetPlayerPos() const
{
	return m_pPlayer->DestRect();
}
Rectf Level::GetLevelBoundaries() const
{
	return m_VecTestSprites[0]->DestRect();
}

void Level::HitCollectable()
{
	for (int i = 0; i < m_pVecCollectables.size(); i++)
	{
		if (utils::IsOverlapping(m_pPlayer->GetHitBox(), m_pVecCollectables[i]->GetHitBox()))
		{
			delete m_pVecCollectables[i];
			m_pVecCollectables[i] = m_pVecCollectables[m_pVecCollectables.size() - 1];
			m_pVecCollectables.pop_back();
		}
	}	

}

void Level::LoadStage()
{
	std::ifstream inputFile{"Stages.txt"};

	std::string info{};

	getline(inputFile, info, '-');

	std::stringstream infoInput{info};

	std::string intersection{};

	//m_pGraph = new PathGraph{};
	while (getline(infoInput, intersection))
	{

		std::stringstream tile{intersection};
		std::string element{};
		getline(tile, element, ' ');
		int id{ std::stoi(element) };

		getline(tile, element, ',');
		int centerX{ std::stoi(element) };

		getline(tile, element);
		int centerY{ std::stoi(element) };

		if (intersection.find("Player") != std::string::npos)
		{
			m_pPlayer->SetPos(Point2f{ float(centerX), float(centerY) });
		}
		else
		{
			m_pVecCollectables.push_back(new Collectable{ Point2f{float(centerX),float(centerY)} });
		}

		m_pGraph.AddTile(id, centerX, centerY, true);
	}

	getline(inputFile, info, '-');
	info.erase(0,1);
	std::stringstream edgeInfoInput{info};
	std::string edges{};
	while (getline(edgeInfoInput, edges))
	{

		std::stringstream tile{edges};
		std::string element{};
		getline(tile, element, ',');
		int firstIntersection{ std::stoi(element) };

		getline(tile, element, ' ');
		int secondIntersection{ std::stoi(element) };

		int firstXCenter{ m_pGraph.GetXCenterOfTile(firstIntersection) };
		int firstYCenter{ m_pGraph.GetYCenterOfTile(firstIntersection) };

		int secondXCenter{ m_pGraph.GetXCenterOfTile(secondIntersection) };
		int secondYCenter{ m_pGraph.GetYCenterOfTile(secondIntersection) };

		int nrOfTiles{};
		if (firstYCenter - secondYCenter == 0 )
		{
			nrOfTiles = (secondXCenter - firstXCenter) / Tile::Size -1;

			//Add a tile to connect to the first intersection
			m_pGraph.AddTile(m_pGraph.GetNrOfTiles(), firstXCenter + Tile::Size, firstYCenter);
			m_pVecCollectables.push_back(new Collectable{ Point2f{float(firstXCenter + Tile::Size), float(firstYCenter)}});
			m_pGraph.AddEdge(firstIntersection, m_pGraph.GetNrOfTiles() - 1);

			//Loop to make and connect all the tiles between the intersections
			for (int i = 1; i < nrOfTiles; i++)
			{
				int newId{ m_pGraph.GetNrOfTiles() };
				int x{ m_pGraph.GetXCenterOfTile(newId - 1) + Tile::Size };

				m_pGraph.AddTile(newId , x, firstYCenter);
				m_pVecCollectables.push_back(new Collectable{ Point2f{float(x), float(firstYCenter)}});
				m_pGraph.AddEdge(newId , newId - 1);
			}

			//Connect last tile with the second intersection
			m_pGraph.AddEdge(m_pGraph.GetNrOfTiles() - 1, secondIntersection);
		}
		else if (secondXCenter - firstXCenter == 0)
		{
			nrOfTiles = (firstYCenter - secondYCenter) / Tile::Size - 1;

			//Add a tile to connect to the first intersection
			std::string escalatorInfo{};
			getline(tile, escalatorInfo);
			if (escalatorInfo.find("Escalator") != std::string::npos)
			{
				if (escalatorInfo.find("Up") != std::string::npos)
				{
					m_pVecEscalators.push_back(new Escalator{ Point2f{float(firstXCenter), float(firstYCenter)}, Point2f{float(secondXCenter), float(secondYCenter)}, false });
				}
				else m_pVecEscalators.push_back(new Escalator{ Point2f{float(firstXCenter), float(firstYCenter)}, Point2f{float(secondXCenter), float(secondYCenter)}, true });
			}

			m_pGraph.AddTile(m_pGraph.GetNrOfTiles(), firstXCenter, firstYCenter - Tile::Size );
			m_pVecCollectables.push_back(new Collectable{ Point2f{float(firstXCenter), float(firstYCenter - Tile::Size)} });
			m_pGraph.AddEdge(firstIntersection, m_pGraph.GetNrOfTiles() - 1);

			//Loop to make and connect all the tiles between the intersections
			for (int i = 1; i < nrOfTiles; i++)
			{
				int newId{ m_pGraph.GetNrOfTiles() };
				int y{ m_pGraph.GetYCenterOfTile(newId - 1) - Tile::Size };

				m_pGraph.AddTile(newId, firstXCenter, y);
				m_pVecCollectables.push_back(new Collectable{ Point2f{float(firstXCenter), float(y)} });
				m_pGraph.AddEdge(newId, newId - 1);
			}

			//Connect last tile with the second intersection
			m_pGraph.AddEdge(m_pGraph.GetNrOfTiles() - 1, secondIntersection);
		}
	}
}