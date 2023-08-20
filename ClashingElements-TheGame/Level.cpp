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
	m_StageNumber{ 2 },
	m_LoopNumber{ 0 },
	m_pGraph{},
	m_Camera{viewportWidth, viewportHeight}
{
	
	m_pPlayer = pCharacter;
	m_pPlayer->Play();
	LoadStage();
	m_pAnimBackGround = new AnimBackGround{ Point2f{500, 0}, "Mall.png" };
	m_pVecSprites.push_back(new PalmTree{ Point2f{434, 704} });
	m_pVecSprites.push_back(new PalmTree{ Point2f{566, 704} });
	m_Camera.SetLevelBoundaries(m_pAnimBackGround->DestRect());
	m_pBackGround = new BackGround{ Point2f{0, 300}, "BGMall.png" ,0.8f };
	m_pBackGroundMusic = new SoundStream{ "Sounds/Spaceship.wav" };
	//m_pBackGroundMusic->Play(true);
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
	delete m_pBackGroundMusic;
	m_pBackGroundMusic = nullptr;

}

void Level::Update(float elapsedSec)
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

	//Point2f pos{ m_pPlayer->GetHitBox().center };

	m_pPlayer->Move(m_pGraph, elapsedSec);
	m_pPlayer->Update(elapsedSec);
	if (m_pPlayer->IsMoving()) HitCollectable();

	m_Camera.Update(m_pPlayer->DestRect());
	
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
		m_pGraph.Draw();
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

Rectf Level::GetPlayerPos() const
{
	return m_pPlayer->DestRect();
}
Rectf Level::GetLevelBoundaries() const
{
	return m_pAnimBackGround->DestRect();
}


void Level::HitCollectable()
{
	std::cout << "collect" << std::endl;
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
		int centerX{ std::stoi(element)/* - int(m_pAnimBackGround->DestRect().width / 2)*/ };

		getline(tile, element);
		int centerY{ std::stoi(element) /*+ int(m_pAnimBackGround->DestRect().height / 2)*/ };

		if (intersection.find("Player") != std::string::npos)
		{
			m_pPlayer->SetPos(Point2f{ float(centerX), float(centerY)});
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
			
			nrOfTiles = abs(secondXCenter - firstXCenter) / Tile::Size -1;
			int tileSize{ secondXCenter > firstXCenter ? Tile::Size : -Tile::Size };

			//Add a tile to connect to the first intersection
			m_pGraph.AddTile(m_pGraph.GetNrOfTiles(), firstXCenter + tileSize, firstYCenter);
			m_pVecCollectables.push_back(new Collectable{ Point2f{float(firstXCenter + tileSize), float(firstYCenter)}});
			m_pGraph.AddEdge(firstIntersection, m_pGraph.GetNrOfTiles() - 1);

			//Loop to make and connect all the tiles between the intersections
			for (int i = 1; i < nrOfTiles; i++)
			{
				int newId{ m_pGraph.GetNrOfTiles() };
				int x{ m_pGraph.GetXCenterOfTile(newId - 1) + tileSize };

				m_pGraph.AddTile(newId , x, firstYCenter);
				m_pVecCollectables.push_back(new Collectable{ Point2f{float(x), float(firstYCenter)}});
				m_pGraph.AddEdge(newId , newId - 1);
			}

			//Connect last tile with the second intersection
			m_pGraph.AddEdge(m_pGraph.GetNrOfTiles() - 1, secondIntersection);
		}
		else if (secondXCenter - firstXCenter == 0)
		{
			nrOfTiles = abs(secondYCenter - firstYCenter) / Tile::Size - 1;
			int tileSize{ secondYCenter > firstYCenter ? Tile::Size : -Tile::Size };

			std::string escalatorInfo{};
			getline(tile, escalatorInfo);

			if (escalatorInfo.find("Escalator") != std::string::npos)
			{
				Point2f startCenter{ float(firstXCenter), float(firstYCenter) };
				Point2f endCenter{ float(secondXCenter), float(secondYCenter) };
				bool isDownWards{};

				if (escalatorInfo.find("Up") != std::string::npos) isDownWards = false;
				else isDownWards = true;

				m_pGraph.AddEscalator(startCenter, endCenter, isDownWards);
			}

			//Add a tile to connect to the first intersection
			m_pGraph.AddTile(m_pGraph.GetNrOfTiles(), firstXCenter, firstYCenter + tileSize);
			m_pVecCollectables.push_back(new Collectable{ Point2f{float(firstXCenter), float(firstYCenter + tileSize)} });
			m_pGraph.AddEdge(firstIntersection, m_pGraph.GetNrOfTiles() - 1);

			//Loop to make and connect all the tiles between the intersections
			for (int i = 1; i < nrOfTiles; i++)
			{
				int newId{ m_pGraph.GetNrOfTiles() };
				int y{ m_pGraph.GetYCenterOfTile(newId - 1) + tileSize };

				m_pGraph.AddTile(newId, firstXCenter, y);
				m_pVecCollectables.push_back(new Collectable{ Point2f{float(firstXCenter), float(y)} });
				m_pGraph.AddEdge(newId, newId - 1);
			}

			//Connect last tile with the second intersection
			m_pGraph.AddEdge(m_pGraph.GetNrOfTiles() - 1, secondIntersection);
		}
	}
}

void Level::SetWidthHeight(float width, float height)
{
	m_Camera.SetWidthHeight(width, height);
}