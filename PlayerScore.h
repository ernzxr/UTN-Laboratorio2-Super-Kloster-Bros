#pragma once
#include <string>

class PlayerScore
{
private:
	char _playerName[6];
	int _points;
public:
	PlayerScore();

	PlayerScore(const std::string& playerName, int points);

	const char* getPlayerName() const;

	int getPoints() const;

	void setPlayerName(const std::string& playerName);

	void setPoints(int points);
};

