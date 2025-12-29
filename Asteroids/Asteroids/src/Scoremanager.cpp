#include "Scoremanager.h"
#include <fstream>
#include <iostream>
#include <algorithm>


Scoremanager::Scoremanager(const sf::Font& font)
	: gameFont(font)
{
	highScore.reserve(10);
	loadScore(filename);
}

void Scoremanager::loadScore(const std::string& filename)
{
	highScore.clear();
	
	std::ifstream file(filename);
	if (!file.is_open()) { return; }

	std::string name;
	int score;

	while (file >> name >> score)
	{
		highScore.push_back({ name, score });
	}

	sortScore();
	trimScore();

}

void Scoremanager::saveScore(const std::string& filename) const
{
	std::ofstream file(filename, std::ios::trunc);
	if (!file.is_open()) { return; }

	for (const auto& entry : highScore)
	{
		file << entry.userName << " " << entry.finalScore << "\n";
	}
}

void Scoremanager::addScore(std::string& name, int score)
{
	highScore.push_back({ name, score });
	sortScore();
	trimScore();
}

void Scoremanager::sortScore()
{
		std::sort(highScore.begin(), highScore.end(),
		[](const Scoreentry& a, const Scoreentry& b)
		{
			return a.finalScore > b.finalScore;
		});
}

void Scoremanager::trimScore()
{
	if (highScore.size() > 10)
	{
		highScore.resize(10);
	}
}

const std::vector<Scoreentry>& Scoremanager::getScore() const
{
	return highScore;
}

void Scoremanager::draw(sf::RenderWindow& window, sf::Font& gameFont)
{
	sf::Text scoreTextWindow(gameFont);
	
}