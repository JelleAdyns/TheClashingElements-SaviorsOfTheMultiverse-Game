#include "HighScoreHandling.h"
#include <algorithm>
#include <filesystem>
#include "Engine.h"
#include "GlobalFont.h"

namespace highScoreHandling
{
	const tstring fileName{ _T("HighScores.txt") };

	tostream& operator<<(tostream& out, const PlayerScore& player)
	{
		return out << player.name << ',' << player.score;
	}

	void LoadHighScores(std::vector<PlayerScore>& highscores)
	{
		tstring filePath{ ResourceManager::GetInstance().GetDataPath() + fileName};
		if (tifstream inputFile{ filePath, std::ios::in }; inputFile.is_open())
		{
			tstring line{};
			tregex reg{ _T("^(\\D{3}),(\\d+)$") };
			while (std::getline(inputFile, line))
			{
				tsmatch matches{};
				if (std::regex_search(line.cbegin(), line.cend(), matches, reg))
				{
					highscores.push_back(PlayerScore{ matches.str(1), std::stoi(matches.str(2)) });
				}
#ifdef _DEBUG
				else OutputDebugString((_T("Invalid line: ") + line + _T('\n')).c_str());

#endif // _DEBUG
			}
		}
		else MessageBox(ENGINE.GetWindow(), (_T("File not found: ") + filePath).c_str(), _T("File not found."), MB_ICONINFORMATION);
	}

	void WriteHighScores(const tstring& initials, int score)
	{
		assert((initials.size() <= 3) && "The initials string was longer than 3 characters while trying to write to highscores.");

		std::vector<PlayerScore> highScores{};
		LoadHighScores(highScores);
		highScores.push_back(PlayerScore{ initials, score });

		std::sort(highScores.begin(), highScores.end(), [](const PlayerScore& firstStudent, const PlayerScore& secondStudent)
			{
				return firstStudent.score > secondStudent.score;
			});

		tstring filePath{ ResourceManager::GetInstance().GetDataPath() + fileName };
		if (tofstream outputFile{ filePath, std::ios::out }; outputFile.is_open())
		{
			std::copy(highScores.cbegin(), highScores.cend(), std::ostream_iterator<PlayerScore, tchar>(outputFile, _T("\n")));
		}
	}

	bool NameIsInList(const tstring& name)
	{
		std::vector<PlayerScore> highScores{};
		LoadHighScores(highScores);

		return std::any_of(highScores.cbegin(), highScores.cend(), [&](const PlayerScore& playerScore) { return name == playerScore.name; });
	}

	PlayerScore GetFirstScore()
	{
		tstring filePath{ ResourceManager::GetInstance().GetDataPath() + fileName };
		if (tifstream inputFile{ filePath, std::ios::in }; inputFile.is_open())
		{
			tstring firstLine{};
			std::getline(inputFile, firstLine);
			tregex reg{ _T("^(\\D{3}),(\\d+)$") };

			tsmatch matches{};
			if (std::regex_search(firstLine.cbegin(), firstLine.cend(), matches, reg))
			{
				return PlayerScore{ matches.str(1), std::stoi(matches.str(2)) };
			}
		}
		else MessageBox(ENGINE.GetWindow(), (_T("File not found: ") + filePath).c_str(), _T("File not found."), MB_ICONINFORMATION);
		return PlayerScore{};
	}

	void RemoveHighScore(const tstring& name)
	{
		std::vector<PlayerScore> highScores{};
		LoadHighScores(highScores);

		highScores.erase(
			std::remove_if(highScores.begin(), highScores.end(), [&](const PlayerScore& playerScore) { return name == playerScore.name; }),
			highScores.end());

		tstring filePath{ ResourceManager::GetInstance().GetDataPath() + fileName };
		if (tofstream outputFile{ filePath, std::ios::out }; outputFile.is_open())
		{
			std::copy(highScores.cbegin(), highScores.cend(), std::ostream_iterator<PlayerScore, tchar>(outputFile, _T("\n")));
		}
	}
	void DrawScoreLine(const Point2Int& pos, int width, const PlayerScore& playerScore, int rank)
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

		highScoreText << std::setfill(_T(' ')) << std::setw(4) << rankName << std::setw(4) << playerScore.name << std::setw(2) << _T(' ')
			<< std::setfill(_T('0')) << std::setw(6) << to_tstring(playerScore.score);

		ENGINE.DrawString(highScoreText.str(), globalFont::GetFont(), pos, width);
	}
}
