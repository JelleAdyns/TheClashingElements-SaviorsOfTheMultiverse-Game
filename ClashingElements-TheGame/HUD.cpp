#include "HUD.h"
#include "GlobalFont.h"
#include "Collectable.h"
#include "HighScoreHandling.h"
#include "Level.h"
#include <sstream>

const int HUD::m_HudHeight{ 40 };


HUD::HUD(int windowWidth, int windowHeight, Skin skin) :
	m_HudArea{ -1, windowHeight - m_HudHeight, windowWidth + 2, m_HudHeight },
	m_pDied{std::make_unique<Subject<Counters>>()},
	m_pLivesTexture{std::make_unique<Texture>(L"Lives.png")},
	m_LivesSrcRect{ 
		[&]() {

			switch (skin)
			{
			case Skin::Finn:
				return RectInt{0,0, 8, 8};
				break;
			case Skin::Wesley:
				return RectInt{ 8,0,8,8 };
				break;
			}
			return RectInt{};
		}()
	}
{
	tstringstream yourStream{};
	yourStream << _T("Your Score\n") << std::setfill(_T('0')) << std::setw(6) << _T('0');
	m_YourScore = yourStream.str();

	m_CurrentHighScore = highScoreHandling::GetFirstScore().score;

	tstringstream highStream{};
	highStream << _T("High Score\n") << std::setfill(_T('0')) << std::setw(6) << to_tstring(m_CurrentHighScore);
	m_HighScore = highStream.str();

	AudioLocator::GetAudioService().AddSound(L"Sounds/saw_sfx1.mp3", static_cast<SoundID>(SoundEvent::Saw));
}

void HUD::Draw() const
{
	ENGINE.SetColor(RGB(0,0,0));
	ENGINE.FillRectangle(m_HudArea);

	auto& font = globalFont::GetFont();
	font.SetTextFormat(8, false, false);
	font.SetHorizontalAllignment(Font::HorAllignment::Center);
	font.SetVerticalAllignment(Font::VertAllignment::Top);

	const auto& wndwRect{ ENGINE.GetWindowRect() };
	int width{ 100 };
	int height{ font.GetFontSize() * 2 + 1};
	int top{ wndwRect.height - 6 };

	Point2Int yourPos{ wndwRect.width / 3 - width / 2, top - height};
	Point2Int highPos{ wndwRect.width / 3 * 2 - width / 2, top - height };

	ENGINE.SetColor(RGB(255,255,255));

	ENGINE.DrawString(m_YourScore.c_str(), font, yourPos, width, height);

	ENGINE.DrawString(m_HighScore.c_str(), font, highPos, width, height);

	for (int i = 0; i < m_Lives; i++)
	{
		ENGINE.DrawTexture(*m_pLivesTexture, RectInt{ 12 + ((8 + 2) * i), wndwRect.height - (m_HudHeight - 6), 8,8}, m_LivesSrcRect);
	}
	
	ENGINE.DrawString((tstringstream{} << std::setfill(_T('0')) << std::setw(4) << m_SecondsLeft).str(), font, wndwRect.width / 2 - width / 2, m_HudArea.bottom + 6, width);
}

void HUD::Tick()
{
	static float time{};
	time += ENGINE.GetDeltaTime();
	if (time > 1.f)
	{
		--m_SecondsLeft;
		time -= 1.f;
	}
	if (m_SecondsLeft == 0)
	{
		m_pDied->NotifyObservers(m_Counters);
	}
}

void HUD::Notify(Player* player)
{
	--m_Lives;
	AddScore(Counters::scorePerLifeLost);
	++m_Counters.nrOfLivesLost;

	if (m_Lives < 0)
	{
		m_pDied->NotifyObservers(m_Counters);
	}
}

void HUD::Notify(int score)
{
	AddScore(Counters::scorePerCollectable);
	++m_Counters.nrOfCollectables;
}

void HUD::OnSubjectDestroy()
{
}

int HUD::GetHudHeight()
{
	return m_HudHeight;
}

void HUD::AddObserver(Level* levelObserver)
{
	m_pDied->AddObserver(levelObserver);
}

bool HUD::FinishedCountSeconds()
{

	static float time{};
	static bool count{false};
	static bool ready{false};
	time += ENGINE.GetDeltaTime();
	
	if (count and time > 0.05f)
	{
		--m_SecondsLeft;
		++m_Counters.nrOfSecondsLeft;
		AddScore(Counters::scorePerSecond);
		time -= 0.05f;
	
		if (m_SecondsLeft == 0)
		{
			count = false;
			AudioLocator::GetAudioService().StopSound(static_cast<SoundID>(SoundEvent::Saw));
		}
	}
	else if (time > 2.f)
	{
		count = !count;
		if (m_SecondsLeft == 0) ready = true;
		else AudioLocator::GetAudioService().PlaySoundClip(static_cast<SoundID>(SoundEvent::Saw),true);
		time = 0.f;
	}

	return ready;
}

void HUD::Reset()
{
	m_Lives = m_StartLives;
	m_SecondsLeft = m_StartSeconds;
}

HUD::Counters HUD::GetCounters() const
{
	return m_Counters;
}

void HUD::AddScore(int points)
{
	m_CurrentScore += points;

	if (m_CurrentScore < 0) m_CurrentScore = 0;

	m_Counters.totalScore = m_CurrentScore;

	tstringstream yourStream{};
	yourStream << _T("Your Score\n") << std::setfill(_T('0')) << std::setw(6) << to_tstring(m_CurrentScore);
	m_YourScore = yourStream.str();

	tstringstream highStream{};
	highStream << _T("High Score\n") << std::setfill(_T('0')) << std::setw(6) << to_tstring(m_CurrentScore > m_CurrentHighScore ? m_CurrentScore : m_CurrentHighScore); // Check correct highscore
	m_HighScore = highStream.str();

}
