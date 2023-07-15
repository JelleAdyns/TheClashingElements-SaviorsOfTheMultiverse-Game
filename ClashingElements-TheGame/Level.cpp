#include "pch.h"
#include "Level.h"
#include "BackGround.h"
#include "Character.h"
#include "PathGraph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <utils.h>


Level::Level():
	m_StageNumber{2},
	m_LoopNumber{0}
{
	
	LoadStage();
	m_VecTestSprites.push_back(new BackGround{ Point2f{500, 0}, "Mall.png" });
	//m_pPlayer = new Character{ Point2f{500, 400} };
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
	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_pBackGroundMusic;
	m_pBackGroundMusic = nullptr;
	delete m_pGraph;
	m_pGraph = nullptr;
}

void Level::Update(float elapsedSec)
{
	for (const auto& pSprite : m_VecTestSprites)
	{
		pSprite->Update(elapsedSec);
	}
	for (const auto& pCollectable : m_pVecCollectables)
	{
		if(pCollectable != nullptr) pCollectable->Update(elapsedSec);
	}
	Move();
	m_pPlayer->Update(elapsedSec);
	if(m_pPlayer->IsMoving()) HitCollectable();
}

void Level::Draw() const
{
	for (const auto& pSprite : m_VecTestSprites)
	{
		pSprite->Draw();
	}
	//m_pGraph->Draw();
	for (const auto& pCollectable : m_pVecCollectables)
	{
		if (pCollectable != nullptr) pCollectable->Draw();
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
void Level::Move()
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_LEFT] && !m_pPlayer->IsMoving())
	{
		int targetX{};
		if (m_pGraph->HasNeighbourInDirection(Vector2f{ -1,0 },m_pPlayer->GetHitBox().center, targetX))
		{
			m_pPlayer->SetIsMoving(true);
			m_pPlayer->SetTargetLocation(targetX,0);
			std::cout << "left" << std::endl;
		}
		//else m_pPlayer->SetFrame(0);
	}
	if (pStates[SDL_SCANCODE_RIGHT] && !m_pPlayer->IsMoving())
	{
		int targetX{};
		if (m_pGraph->HasNeighbourInDirection(Vector2f{ 1,0 }, m_pPlayer->GetHitBox().center, targetX))
		{
			m_pPlayer->SetIsMoving(true);
			m_pPlayer->SetTargetLocation(targetX,0);
			std::cout << "right" << std::endl;
		}
		//else m_pPlayer->SetFrame(0);
	}
	if (pStates[SDL_SCANCODE_DOWN] && !m_pPlayer->IsMoving())
	{
		int targetY{};
		if (m_pGraph->HasNeighbourInDirection(Vector2f{ 0, -1 }, m_pPlayer->GetHitBox().center, targetY))
		{
			m_pPlayer->SetIsMoving(true);
			m_pPlayer->SetTargetLocation(0, targetY);
			std::cout << "down" << std::endl;
		}
		//else m_pPlayer->SetFrame(0);
	}
	if (pStates[SDL_SCANCODE_UP] && !m_pPlayer->IsMoving())
	{
		int targetY{};
		if (m_pGraph->HasNeighbourInDirection(Vector2f{ 0, 1 }, m_pPlayer->GetHitBox().center, targetY))
		{
			m_pPlayer->SetIsMoving(true);
			m_pPlayer->SetTargetLocation(0,targetY);
			std::cout << "up" << std::endl;
		}
		//else m_pPlayer->SetFrame(0);
	}

	//if (!pStates[SDL_SCANCODE_UP] && !pStates[SDL_SCANCODE_DOWN] && !pStates[SDL_SCANCODE_LEFT] && !pStates[SDL_SCANCODE_RIGHT] && !m_pPlayer->IsMoving()) m_pPlayer->SetFrame(0);
}
void Level::HitCollectable()
{
	/*for (int i = 0; i < m_pVecCollectables.size(); i++)
	{
	}*/
		int tileId{ m_pGraph->GetTileId(m_pPlayer->GetHitBox().center) };
		if (m_pVecCollectables[tileId] != nullptr)
		{
			/*if (m_pVecCollectables[tileId]->GetId() == tileId)
			{*/
				if (utils::IsOverlapping(m_pPlayer->GetHitBox(), m_pVecCollectables[tileId]->GetHitBox()))
				{
					std::cout << "Collect" << std::endl;
					delete m_pVecCollectables[tileId];
					std::cout << m_pVecCollectables.capacity()<< std::endl;
					m_pVecCollectables[tileId] = nullptr;
					//m_pVecCollectables[tileId] = m_pVecCollectables[m_pVecCollectables.size() - 1];
					//m_pVecCollectables.pop_back();
				}
			//}
		}
		

}

void Level::LoadStage()
{
	std::ifstream inputFile{"Stages.txt"};

	std::string info{};

	getline(inputFile, info, '-');

	std::stringstream infoInput{info};

	std::string intersection{};

	m_pGraph = new PathGraph{};
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
			m_pPlayer = new Character{ Point2f{float(centerX), float(centerY)}, id };
		}

		m_pGraph->AddTile(id, centerX, centerY, true);
		m_pVecCollectables.push_back(new Collectable{ Point2f{float(centerX),float(centerY)} });
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
			m_pVecCollectables.push_back(new Collectable{ Point2f{float(firstXCenter + Tile::Size), float(firstYCenter)}});
			m_pGraph->AddEdge(firstIntersection, m_pGraph->GetNrOfTiles() - 1);

			//Loop to make and connect all the tiles between the intersections
			for (int i = 1; i < nrOfTiles; i++)
			{
				int newId{ m_pGraph->GetNrOfTiles() };
				int x{ m_pGraph->GetXCenterOfTile(newId - 1) + Tile::Size };

				m_pGraph->AddTile(newId , x, firstYCenter);
				m_pVecCollectables.push_back(new Collectable{ Point2f{float(x), float(firstYCenter)}});
				m_pGraph->AddEdge(newId , newId - 1);
			}

			//Connect last tile with the second intersection
			m_pGraph->AddEdge(m_pGraph->GetNrOfTiles() - 1, secondIntersection);
		}
		else if (secondXCenter - firstXCenter == 0)
		{
			nrOfTiles = (firstYCenter - secondYCenter) / Tile::Size - 1;

			//Add a tile to connect to the first intersection
			m_pGraph->AddTile(m_pGraph->GetNrOfTiles(), firstXCenter, firstYCenter - Tile::Size);
			m_pVecCollectables.push_back(new Collectable{ Point2f{float(firstXCenter), float(firstYCenter - Tile::Size)} });
			m_pGraph->AddEdge(firstIntersection, m_pGraph->GetNrOfTiles() - 1);

			//Loop to make and connect all the tiles between the intersections
			for (int i = 1; i < nrOfTiles; i++)
			{
				int newId{ m_pGraph->GetNrOfTiles() };
				int y{ m_pGraph->GetYCenterOfTile(newId - 1) - Tile::Size };

				m_pGraph->AddTile(newId, firstXCenter, y);
				m_pVecCollectables.push_back(new Collectable{ Point2f{float(firstXCenter), float(y)} });
				m_pGraph->AddEdge(newId, newId - 1);
			}

			//Connect last tile with the second intersection
			m_pGraph->AddEdge(m_pGraph->GetNrOfTiles() - 1, secondIntersection);
		}
	}
}