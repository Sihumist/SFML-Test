#pragma once
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include "screen.h"
#include <iostream>

class Game
{
public:
	Game(const unsigned int& width, const unsigned int& height,
		const unsigned int& bitsPerPixel, const std::string& windowName);
	~Game();

	virtual sf::RenderWindow& getWindow();

	virtual void createShape();
	virtual void setOrigin();
	virtual void drawScreen();
	virtual void update();
	virtual void close();
	virtual bool pollEvent(sf::Event& event);
	virtual bool isOpen() const;
	virtual void move(const unsigned int at, const sf::Vector2f& offset);
	virtual void rotate(const unsigned int at, const float& offset);
	virtual void setPosition(const unsigned int at, const sf::Vector2f& position);
	
	virtual Screen& getScreen();
	virtual sf::Vector2f setSize(const unsigned int at) const;
	virtual sf::Vector2f getPosition(const unsigned int at) const;


protected:
	unsigned int width, height;
	unsigned int progressFlags;
	sf::RenderWindow appWindow;
	Screen* currentScreen;
};