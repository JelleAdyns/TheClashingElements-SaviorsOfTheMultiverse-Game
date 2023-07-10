#include "pch.h"
#include "Level.h"
#include "BackGround.h"
#include "Character.h"
#include "PathGraph.h"
#include <fstream>
#include <iostream>
#include <sstream>


Level::Level():
	m_StageNumber{2},
	m_LoopNumber{0}
{
	m_VecTestSprites.push_back(new BackGround{ Point2f{500, 0}, "Mall.png" });
	m_pPlayer = new Character{ Point2f{500, 400} };
	m_pBackGroundMusic = new SoundStream{ "Sounds/Spaceship.wav" };
	m_pBackGroundMusic->Play(true);
	m_pGraph = new PathGraph{};
	LoadStage();
}

Level::~Level()
{
	for (auto sprite : m_VecTestSprites)
	{
		delete sprite;
		sprite = nullptr;
	}
	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_pBackGroundMusic;
	m_pBackGroundMusic = nullptr;
	delete m_pGraph;
	m_pGraph = nullptr;
}

void Level::Update(float elapsedSec)
{
	for (const auto& sprite : m_VecTestSprites)
	{
		sprite->Update(elapsedSec);
	}
	m_pPlayer->Update(elapsedSec);
}

void Level::Draw() const
{
	for (const auto& sprite : m_VecTestSprites)
	{
		sprite->Draw();
	}
	m_pPlayer->Draw();
	m_pGraph->Draw();
}

Rectf Level::GetPlayerPos() const
{
	return m_pPlayer->DestRect();
}
Rectf Level::GetLevelBoundaries() const
{
	return m_VecTestSprites[0]->DestRect();
}

void Level::LoadStage() const
{
	std::ifstream inputFile{"Stages.txt"};

	std::string info{};

	getline(inputFile, info, '-');

	std::stringstream infoInput{info};

	std::string intersection{};
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

		m_pGraph->AddTile(id, centerX, centerY, true);
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

		getline(tile, element);
		int secondIntersection{ std::stoi(element) };

		int firstXCenter{ m_pGraph->GetXCenterOfTile(firstIntersection) };
		int firstYCenter{ m_pGraph->GetYCenterOfTile(firstIntersection) };

		int secondXCenter{ m_pGraph->GetXCenterOfTile(secondIntersection) };
		int secondYCenter{ m_pGraph->GetYCenterOfTile(secondIntersection) };

		int nrOfTiles{};
		if (firstYCenter - secondYCenter == 0 )
		{
			nrOfTiles = (secondXCenter - firstXCenter) / Tile::Size -1;

			//Add a tile to connect to the first intersection
			m_pGraph->AddTile(m_pGraph->GetNrOfTiles(), firstXCenter + Tile::Size, firstYCenter);
			m_pGraph->AddEdge(firstIntersection, m_pGraph->GetNrOfTiles() - 1);

			//Loop to make end connect all the tiles between the intersections
			for (int i = 1; i < nrOfTiles; i++)
			{
				m_pGraph->AddTile(m_pGraph->GetNrOfTiles() , m_pGraph->GetXCenterOfTile(m_pGraph->GetNrOfTiles() - 1) + Tile::Size, firstYCenter);
				m_pGraph->AddEdge(m_pGraph->GetNrOfTiles() - 1 , m_pGraph->GetNrOfTiles() - 2);
			}

			//Connect last tile with the second intersection
			m_pGraph->AddEdge(secondIntersection, m_pGraph->GetNrOfTiles() - 1);
		}
		else if (secondXCenter - firstXCenter == 0)
		{
			nrOfTiles = (firstYCenter - secondYCenter) / Tile::Size - 1;

			//Add a tile to connect to the first intersection
			m_pGraph->AddTile(m_pGraph->GetNrOfTiles(), firstXCenter, firstYCenter - Tile::Size);
			m_pGraph->AddEdge(firstIntersection, m_pGraph->GetNrOfTiles() - 1);

			//Loop to make end connect all the tiles between the intersections
			for (int i = 1; i < nrOfTiles; i++)
			{
				m_pGraph->AddTile(m_pGraph->GetNrOfTiles(), firstXCenter, m_pGraph->GetYCenterOfTile(m_pGraph->GetNrOfTiles() - 1) - Tile::Size);
				m_pGraph->AddEdge(m_pGraph->GetNrOfTiles() - 1, m_pGraph->GetNrOfTiles() - 2);
			}

			//Connect last tile with the second intersection
			m_pGraph->AddEdge(secondIntersection, m_pGraph->GetNrOfTiles() - 1);
		}
	}
}