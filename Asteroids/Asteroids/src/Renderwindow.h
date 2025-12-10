#pragma once

#include <SFML/graphics.hpp>
#include <string>



class Renderwindow
{
private:
	static const int WIDTH = 900;
	static const int HEIGHT = 600;
	sf::RenderWindow window;

public:
	Renderwindow();
	~Renderwindow();

	bool isOpen() const;
	std::optional<sf::Event> pollEventWindow();
	void clear(const sf::Color& color = sf::Color::Black);
	void display();
	void close();
};

