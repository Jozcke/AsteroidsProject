#include "Renderwindow.h"
#include "SFML/graphics.hpp"


Renderwindow::Renderwindow()
	: window(sf::VideoMode({ WIDTH,HEIGHT }), "Asteroids", sf::State::Windowed)
	//max framerate or not??? 
{	
	window.setFramerateLimit(60);
}

Renderwindow::~Renderwindow()
{
}

bool Renderwindow::isOpen() const
{
	return this->window.isOpen();
}

std::optional<sf::Event>Renderwindow::pollEventWindow()
{
	return this->window.pollEvent();
}

void Renderwindow::clear(const sf::Color& color)
{
	this->window.clear(color);
}

void Renderwindow::display()
{
	this->window.display();
}

void Renderwindow::close()
{
	this->window.close();
}
sf::RenderWindow& Renderwindow::getWindow()
{
	return this->window;
}

const sf::RenderWindow& Renderwindow::getWindow() const
{
	return this->window;
}