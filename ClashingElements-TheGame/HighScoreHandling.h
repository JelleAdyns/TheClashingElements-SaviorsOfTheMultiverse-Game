#ifndef HIGHSCOREHANDLING_H
#define HIGHSCOREHANDLING_H

#include <string>
#include <vector>
#include "Engine.h"


namespace highScoreHandling
{
	struct PlayerScore
	{
		tstring name;
		int score;
	};

	static const int maxCharacters{ 3 };
	static const tstring placeholderName{_T(' ')};

	const std::vector<PlayerScore>& GetHighScores();
	void LoadHighScores();
	void WriteHighScores(const tstring& initials, int score, bool loadScores = true);
	bool NameIsInList(const tstring& name, bool loadScores = true);
	PlayerScore GetFirstScore(bool loadScores = true);
	void RemoveHighScores(const tstring& name, bool loadScores = true);
	void DrawScoreLine(const RectInt& destRect, const PlayerScore& playerScore, int rank);
	void DrawScoreList(int maxScores, const RectInt& destRect, const tstring& nameToHighlight, bool drawTitle = true);
}

#endif // !HIGHSCOREHANDLING_H
