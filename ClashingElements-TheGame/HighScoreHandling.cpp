#include "HighScoreHandling.h"
#include <algorithm>
#include <filesystem>
#include "Engine.h"
#include "GameFont.h"

namespace highScoreHandling
{
	const tstring fileName{ _T("HighScores.txt") };
	std::vector<PlayerScore> lastLoadedScores{};

	tostream& operator<<(tostream& out, const PlayerScore& player)
	{
		return out << player.name << ',' << player.score;
	}

	const std::vector<PlayerScore>& GetHighScores()
	{
		return lastLoadedScores;
	}

	void LoadHighScores()
	{
		tstring filePath{ ResourceManager::GetInstance().GetDataPath() + fileName};
		if (tifstream inputFile{ filePath, std::ios::in }; inputFile.is_open())
		{
			lastLoadedScores.clear();
			tstring line{};
			tregex reg{ _T("^(\\D{3}),(\\d+)$") };
			while (std::getline(inputFile, line))
			{
				tsmatch matches{};
				if (std::regex_search(line.cbegin(), line.cend(), matches, reg))
				{
					lastLoadedScores.push_back(PlayerScore{ matches.str(1), std::stoi(matches.str(2)) });
				}
				else OutputDebugString((_T("Invalid line: ") + line + _T('\n')).c_str());

			}
		}
		else MessageBox(ENGINE.GetWindow(), (_T("File not found: ") + filePath).c_str(), _T("File not found."), MB_ICONINFORMATION);
	}

	void WriteHighScores(const tstring& initials, int score, bool loadScores)
	{
		assert((initials.size() <= maxCharacters) && "The initials string was longer than 3 characters while trying to write to highscores.");

		if(loadScores) LoadHighScores();
		lastLoadedScores.push_back(PlayerScore{ initials, score });

		std::stable_sort(lastLoadedScores.begin(), lastLoadedScores.end(), [](const PlayerScore& firstStudent, const PlayerScore& secondStudent)
			{
				return firstStudent.score > secondStudent.score;
			});

		tstring filePath{ ResourceManager::GetInstance().GetDataPath() + fileName };
		if (tofstream outputFile{ filePath, std::ios::out }; outputFile.is_open())
		{
			std::copy(lastLoadedScores.cbegin(), lastLoadedScores.cend(), std::ostream_iterator<PlayerScore, tchar>(outputFile, _T("\n")));
		}
	}

	bool NameIsInList(const tstring& name, bool loadScores)
	{
		if(loadScores) LoadHighScores();

		return std::any_of(lastLoadedScores.cbegin(), lastLoadedScores.cend(), [&](const PlayerScore& playerScore) { return name == playerScore.name; });
	}

	PlayerScore GetFirstScore(bool loadScores)
	{
		if (loadScores) LoadHighScores();

		assert(lastLoadedScores.size() > 0);
		return lastLoadedScores.at(0);
	}

	void RemoveHighScores(const tstring& name, bool loadScores)
	{
		if(loadScores) LoadHighScores();

		lastLoadedScores.erase(
			std::remove_if(lastLoadedScores.begin(), lastLoadedScores.end(), [&](const PlayerScore& playerScore) { return name == playerScore.name; }),
			lastLoadedScores.end());

		tstring filePath{ ResourceManager::GetInstance().GetDataPath() + fileName };
		if (tofstream outputFile{ filePath, std::ios::out }; outputFile.is_open())
		{
			std::copy(lastLoadedScores.cbegin(), lastLoadedScores.cend(), std::ostream_iterator<PlayerScore, tchar>(outputFile, _T("\n")));
		}
	}
	void DrawScoreLine(const RectInt& destRect, const PlayerScore& playerScore, int rank)
	{
		tstring rankName{ to_tstring(rank) };

		const auto& addTH = [&]() {rankName += _T("TH"); };

		switch (rank % 10)
		{
		case 1:
			if (rank == 11) addTH();
			else rankName += _T("ST");
			break;
		case 2:
			if (rank == 12) addTH();
			else rankName += _T("ND");
			break;
		case 3:
			if (rank == 13) addTH();
			else rankName += _T("RD");
			break;
		default:
			addTH();
			break;
		}


		tstringstream highScoreText{};

		highScoreText << std::setfill(_T(' ')) << std::setw(4) << rankName << std::setw(maxCharacters + 1) << playerScore.name << std::setw(2) << _T(' ')
			<< std::setfill(_T('0')) << std::setw(6) << to_tstring(playerScore.score);

		ENGINE.DrawString(highScoreText.str(), globalFont::GetFont(), destRect);
	}

	void DrawScoreList(int maxScores, const RectInt& destRect, const tstring& nameToHighlight, bool drawTitle)
	{
		//const auto& wndwRect = ENGINE.GetWindowRect();
		auto& font = globalFont::GetFont();

		constexpr static int border{ 6 };
		const int posHeightSteps{ (destRect.height - border * 2) / (maxScores + (drawTitle ? 1 : 0)) };

		font.SetTextFormat(10, false, false);
		font.SetHorizontalAllignment(Font::HorAllignment::Center);
		font.SetVerticalAllignment(Font::VertAllignment::Center);

		ENGINE.SetColor(RGB(255, 255, 255));

		const int top{ destRect.bottom + destRect.height };
		ENGINE.DrawString(_T("HIGHSCORES"), font, 0, top - border - posHeightSteps , destRect.width, posHeightSteps);

		for (int i = 0; i < (lastLoadedScores.size() < maxScores ? lastLoadedScores.size() : maxScores); i++)
		{
			if (lastLoadedScores.at(i).name == nameToHighlight) ENGINE.SetColor(RGB(255, 255, 0));
			else ENGINE.SetColor(RGB(255, 255, 255));

			DrawScoreLine(RectInt{ 0, top - posHeightSteps * (i + 2) - border , destRect.width, posHeightSteps}, lastLoadedScores.at(i), (i + 1));
		}
	}
}
