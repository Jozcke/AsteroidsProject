#include "Scoremanager.h"
#include <fstream>
#include <iostream>
#include <algorithm>


Scoremanager::Scoremanager(const sf::Font& font)
	: gameFont(font)
{
	v_highScore.reserve(10);
	loadScore(filename);
}

void Scoremanager::loadScore(const std::string& filename)
{
	v_highScore.clear();
	
	std::ifstream file(filename);
	if (!file.is_open()) 
	{ 
		std::cout << "could not load score.txt" << std::endl;
		return; 
	}

	std::string name;
	int score;

	while (file >> name >> score)
	{
		v_highScore.push_back({ name, score });
	}

	sortScore();
	trimScore();

}

void Scoremanager::saveScore(const std::string& filename) const
{
	std::ofstream file(filename, std::ios::trunc);
	if (!file.is_open()) 
	{ 
		std::cout << "could not load score.txt" << std::endl;
		return; 
	}

	for (const auto& entry : v_highScore)
	{
		file << entry.userName << " " << entry.finalScore << "\n";
	}
}

void Scoremanager::addScore(const std::string& name, int score)
{
	v_highScore.push_back({ name, score });
	sortScore();
	trimScore();
}

void Scoremanager::sortScore()
{
		std::sort(v_highScore.begin(), v_highScore.end(),
		[](const Scoreentry& a, const Scoreentry& b)
		{
			return a.finalScore > b.finalScore;
		});
}

void Scoremanager::trimScore()
{
	if (v_highScore.size() > 10)
	{
		v_highScore.resize(10);
	}
}

const std::vector<Scoreentry>& Scoremanager::getScore() const
{
	return v_highScore;
}

void Scoremanager::draw(sf::RenderWindow& window)
{
	sf::Text scoreTextWindow(gameFont);
	scoreTextWindow.setString("HIGH SCORES");
	scoreTextWindow.setCharacterSize(40);
	scoreTextWindow.setFillColor(sf::Color::White);
	scoreTextWindow.setPosition({ window.getSize().x / 2.f - 140.f, 50.f });

	window.draw(scoreTextWindow);
	float startY = 120.f;
	
	for (size_t i = 0; i < v_highScore.size(); i++)
	{
		sf::Text score(gameFont);
		score.setCharacterSize(24);
		score.setFillColor(sf::Color::White);

		score.setString(
			std::to_string(i + 1) + " " +
			v_highScore[i].userName + ' ' +
			std::to_string(v_highScore[i].finalScore)
		);
		
		score.setPosition({ window.getSize().x / 2.f - 150.f, startY + i * 30.f });

		window.draw(score);
	}
}

bool Scoremanager::checkifTopScore(int score) const
{
	if (v_highScore.size() < 10)
		return true;

	return score > v_highScore.back().finalScore;
}