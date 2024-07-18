#pragma once
#include "PlayerScore.h"
#include <cstring>

PlayerScore::PlayerScore()
{
	std::strncpy(_playerName, "AAAAA", 5);
	_playerName[5] = '\0';
	_points = 0;
}

PlayerScore::PlayerScore(const std::string& playerName, int points)
{
	std::strncpy(_playerName, playerName.c_str(), 5);
	_playerName[5] = '\0';
	_points = points;
}

const char* PlayerScore::getPlayerName() const
{
	return _playerName;
}

int PlayerScore::getPoints() const
{
	return _points;
}

void PlayerScore::setPlayerName(const std::string& playerName)
{
	std::strncpy(_playerName, playerName.c_str(), 5);
	_playerName[5] = '\0';
}

void PlayerScore::setPoints(int points)
{
	_points = points;
}
