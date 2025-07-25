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
#include "Commands.h"


Level::Level(Game& game, Skin playerSkin) :
	Screen{},
	m_VecBackGrounds
	{
		{ _T("MallBG.png")      , {_T("Space.png")    ,Point2Int{0, 0}} },
		{ _T("GloirbnPit.png"), {_T("GloirbnPit.png"),Point2Int{0, 0}} }
    },

	m_VecMusic
	{
		_T("Sounds/Spaceship.wav"),
		_T("Sounds/Spaceship.wav")
	},

	m_MaxStages{ 1 },
	m_StageNumber{ 0 },
	m_LoopNumber{ 0 },
	m_StageCompleted{false},
	m_Hud{ ENGINE.GetWindowRect().width, ENGINE.GetWindowRect().height, playerSkin },
	m_Camera{ ENGINE.GetWindowRect().width, ENGINE.GetWindowRect().height - HUD::GetHudHeight()},
	m_pPushCommand{nullptr},
	m_GameReference{game}
{
	AudioLocator::GetAudioService().AddSound(_T("Sounds/Spaceship.mp3"), static_cast<SoundID>(SoundEvent::Spaceship));

	m_Hud.AddObserver(this);

	m_pPickedUp = std::make_unique<Subject<int>>();
	m_pPickedUp->AddObserver(&m_Hud);

	m_pPlayer = std::make_unique<Player>(playerSkin, &m_Hud);
	m_pPlayer->Play();
	StartStage();

	m_Camera.Update(m_pPlayer->DestRect());

	m_pPushCommand = std::make_unique<PushScreenCommand>(m_GameReference, GameState::Welcome);
}

void Level::Tick()
{
	if (not m_StageCompleted)
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
			if (!pEnemy->IsMoving())
			{
				pEnemy->SetTarget(m_pPlayer->GetHitBox().center);

				TileID intersectionId = m_Graph.GetTileId(pEnemy->GetHitBox().center);

				m_Graph.SetWalkabilityOfTile(intersectionId, false);
				pEnemy->Move(m_Graph);
				m_Graph.SetWalkabilityOfTile(intersectionId, true);
			}
			if (utils::IsOverlapping(pEnemy->GetHitBox(), m_pPlayer->GetHitBox()))
			{
				m_pPlayer->TakeDamage();
			}
		}

		m_pPlayer->Move(m_Graph);
		m_pPlayer->Update();
		if (m_pPlayer->IsMoving()) HitCollectable();

		m_Camera.Update(m_pPlayer->DestRect());

		m_Hud.Tick();

		SetUpDrawBuffer();
	}
	else
	{
		if (m_Hud.FinishedCountSeconds())
		{
			++m_StageNumber %= m_MaxStages;

			float currentMultiplier = Character::GetSpeedMultiplier();
			if(currentMultiplier == 0.f) Character::SetSpeedMultiplier(1.4f);
			else Character::SetSpeedMultiplier(currentMultiplier * 1.2f);
			
			StartStage();
		}
	}

	if (m_pPushCommand)
	{
		m_pPushCommand->Execute();
		m_pPushCommand = nullptr;
	}
	
}

void Level::Draw() const
{
	
	m_pBackGround->Draw();
	//ENGINE.PushTransform();
	//m_Camera.Transform(m_pBackGround->GetParallaxSpeed());
	//ENGINE.PopTransform();

	
	ENGINE.PushTransform();

	m_Camera.Transform();
		
	m_pAnimBackGround->Draw();
	m_Graph.Draw();

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

void Level::KeyInput(int virtualKeyCode)
{
	if (virtualKeyCode == VK_ESCAPE)
	{
		m_pPushCommand = std::make_unique<PushScreenCommand>(m_GameReference, GameState::Pause);

	}
#ifdef _DEBUG
	if (virtualKeyCode == 'R')
	{
		m_Hud.Reset();
	}
#endif // _DEBUG
}

void Level::HandleControllerInput()
{
	if (ENGINE.ButtonDownThisFrame(Controller::Button::Start, 0))
	{
		m_pPushCommand = std::make_unique<PushScreenCommand>(m_GameReference, GameState::Pause);
	}
}

void Level::OnEnter()
{
	
}

void Level::OnExit()
{
	AudioLocator::GetAudioService().StopAllSounds();
	AudioLocator::GetAudioService().RemoveSound(static_cast<SoundID>(SoundEvent::Spaceship));
	Character::SetSpeedMultiplier(1);
}

void Level::Notify(HUD::Counters counters)
{
	m_pPushCommand = std::make_unique<PushScreenCommand>(m_GameReference, GameState::GameOver);
}

void Level::OnSubjectDestroy()
{
}


void Level::SetUpDrawBuffer()
{
	m_pDrawBuffer.clear();
	m_pDrawBuffer.reserve(m_pVecCollectables.size() + m_pVecEnemies.size() + 1);

	for (const auto& pCollcetable : m_pVecCollectables) 
		m_pDrawBuffer.push_back(pCollcetable.get());

	for (const auto& pEnemy : m_pVecEnemies) 
		m_pDrawBuffer.push_back(pEnemy.get());

	m_pDrawBuffer.push_back(m_pPlayer.get());

	std::sort(m_pDrawBuffer.begin(), m_pDrawBuffer.end(), [](const AnimatedSprite* sprite1, const AnimatedSprite* sprite2)
		{
			return sprite1->DestRect().bottom > sprite2->DestRect().bottom;
		});
}

void Level::HitCollectable()
{
	m_pVecCollectables.erase(std::remove_if(m_pVecCollectables.begin(), m_pVecCollectables.end(), [&](const std::unique_ptr<Collectable>& collectable)
			{
				if (utils::IsOverlapping(m_pPlayer->GetHitBox(), collectable->GetHitBox()))
				{
					m_pPickedUp->NotifyObservers(HUD::Counters::scorePerCollectable);
					return true;
				}
				return false;
			}),
		m_pVecCollectables.end());

	if (m_pVecCollectables.empty())
	{
		m_StageCompleted = true;
		AudioLocator::GetAudioService().StopAllSounds();
	}
}

void Level::StartStage()
{
	Reset();

	const auto& [stageArtFile, backgroundPosPair] = m_VecBackGrounds.at(m_StageNumber);
	const auto& [backgroundFile, pos] = backgroundPosPair;

	m_pAnimBackGround = std::make_unique<AnimBackGround>(stageArtFile);
	m_pBackGround = std::make_unique < BackGround >( backgroundFile, pos, 0.f );

	m_Camera.SetLevelBoundaries(m_pAnimBackGround->DestRect());
	
	LoadStage();

	m_pDrawBuffer.reserve(m_pVecCollectables.size() + m_pVecEnemies.size() + 1);

	AudioLocator::GetAudioService().PlaySoundClip(static_cast<SoundID>(SoundEvent::Spaceship), true);
}

void Level::LoadStage()
{
	
	tifstream inputFile{ ResourceManager::GetInstance().GetDataPath() + _T("StagePattern.txt") };

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

	TileID currTileId{};
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
			//case _T('T'):
			//	m_pVecSprites.push_back(std::make_unique<PalmTree>( center ));
			//	break;
			case _T('P'):

				m_pPlayer->Respawn(center);

			case _T('B'):

				if (rowString[col] != _T('P')) m_pVecEnemies.push_back(std::make_unique<Boss>( center, Player::GetDefaultSpeed() ));

			case _T('M'):

				if (rowString[col] != _T('P') && rowString[col] != _T('B')) m_pVecEnemies.push_back(std::make_unique<Minion>(center));

			case _T(','):

				isIntersection = true;

			case _T('.'):

				m_Graph.AddTile(currTileId, center.x, center.y, isIntersection);
				if(rowString[col] != _T('P')) m_pVecCollectables.push_back(std::make_unique<Collectable>(center));
				
				TileID previousColTileId{ m_Graph.GetTileId(Point2Int{ center.x - Tile::Size, center.y }) };
				if(previousColTileId >= 0) m_Graph.AddEdge(currTileId, previousColTileId);
				
				TileID previousRowTileId{ m_Graph.GetTileId(Point2Int{ center.x, center.y + Tile::Size }) };
				if(previousRowTileId >= 0) m_Graph.AddEdge(currTileId, previousRowTileId);

				++currTileId;


				break;
			}


			++col;
		}
	}
	//m_pVecCollectables.push_back(std::make_unique<Collectable>(Point2Int{452, 226}));
	
}


void Level::Reset()
{
	m_pVecSprites.clear();
	m_pVecEnemies.clear();
	m_Graph.Reset();
	m_Hud.Reset();
	m_pDrawBuffer.clear();
	m_StageCompleted = false;
}