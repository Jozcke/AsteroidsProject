#pragma once

#include <string>
#include <vector>
#include "SFML/Graphics.hpp"


struct Scoreentry {
		
	std::string userName;
	int finalScore;

};


class Scoremanager
{

private:
	
	const std::string filename = "score/score.txt";
	const sf::Font& gameFont;
	
	std::vector<Scoreentry> highScore;
	std::vector<sf::Text> v_scoreText;

	void sortScore();

public:
	Scoremanager(const sf::Font& font);
	void loadScore(const std::string& filename);
	void saveScore(const std::string& filename) const;
	void trimScore();
	void addScore(std::string& name, int score);
	void draw(sf::RenderWindow& window, sf::Font& gameFont);

	const std::vector<Scoreentry>& getScore() const;


};

