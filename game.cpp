#include "game.h"

Game::Game(const unsigned int& width, const unsigned int& height,
	const unsigned int& bitsPerPixel, const std::string& windowName)
{
	this->width = width;
	this->height = height;
	this->progressFlags = 0;
	this->appWindow.create(sf::VideoMode(width, height, bitsPerPixel), windowName, sf::Style::Default, sf::ContextSettings(0U, 0U, 8U, 1U, 1U));
	this->appWindow.setFramerateLimit(120);
	this->appWindow.setVerticalSyncEnabled(true);
	this->currentScreen = new Screen();
}

Game::~Game()
{
	delete[] this->currentScreen;
}

sf::RenderWindow& Game::getWindow()
{
	return appWindow;
}

void Game::createShape()
{
}

void Game::setOrigin()
{
}

void Game::drawScreen()
{
	appWindow.draw(*currentScreen);
}

void Game::update()
{
	appWindow.clear();
	drawScreen();	//todo undo
	appWindow.display();
}

void Game::close()
{
	this->appWindow.close();
}

bool Game::pollEvent(sf::Event& event)
{
	return this->appWindow.pollEvent(event);
}

bool Game::isOpen() const
{
	return this->appWindow.isOpen();
}

Screen& Game::getScreen()
{
	return (*this->currentScreen);
}

void Game::move(const unsigned int at, const sf::Vector2f& offset)
{
	sf::Shape* shape = nullptr;

	shape = dynamic_cast<sf::RectangleShape*>(this->currentScreen->sceneElements[at]);
	if (shape != nullptr) {
		shape->move(offset);
	}

	shape = dynamic_cast<sf::CircleShape*>(this->currentScreen->sceneElements[at]);
	if (shape != nullptr) {
		shape->move(offset);
	}
}

void Game::rotate(const unsigned int at, const float& offset)
{
	sf::Shape* shape = nullptr;

	shape = dynamic_cast<sf::RectangleShape*>(this->currentScreen->sceneElements[at]);
	if (shape != nullptr) {
		shape->rotate(offset);
	}

	shape = dynamic_cast<sf::CircleShape*>(this->currentScreen->sceneElements[at]);
	if (shape != nullptr) {
		shape->rotate(offset);
	}
}

void Game::setPosition(const unsigned int at, const sf::Vector2f& position)
{
	sf::Shape* shape = nullptr;

	shape = dynamic_cast<sf::RectangleShape*>(this->currentScreen->sceneElements[at]);
	if (shape != nullptr) {
		shape->setPosition(position);
	}

	shape = dynamic_cast<sf::CircleShape*>(this->currentScreen->sceneElements[at]);
	if (shape != nullptr) {
		shape->setPosition(position);
	}
}

sf::Vector2f Game::setSize(const unsigned int at) const
{
	sf::Shape* shape = nullptr;

	shape = dynamic_cast<sf::RectangleShape*>(this->currentScreen->sceneElements[at]);
	if (shape != nullptr) {
		//shape->getSize();
	}
	return sf::Vector2f();
}

sf::Vector2f Game::getPosition(const unsigned int at) const
{
	sf::Shape* shape = nullptr;

	shape = dynamic_cast<sf::CircleShape*>(this->currentScreen->sceneElements[at]);
	if (shape != nullptr) {
		return shape->getPosition();
	}
	return sf::Vector2f(0, 0);
}
