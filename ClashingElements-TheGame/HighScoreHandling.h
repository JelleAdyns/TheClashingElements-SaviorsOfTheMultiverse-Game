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

	void LoadHighScores(std::vector<PlayerScore>& highscores);
	void WriteHighScores(const tstring& initials, int score);
	bool NameIsInList(const tstring& name);
	PlayerScore GetFirstScore();
	void RemoveHighScore(const tstring& name);
}

#endif // !HIGHSCOREHANDLING_H
