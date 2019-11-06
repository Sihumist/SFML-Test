#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>		// io for logging
#include <cmath>
#include <cstdlib>
#include "steam/steam_api.h"
#include "game.h"
#include "screen.h"
#include "timer.h"

constexpr int W_WIDTH = 600;
constexpr int W_HEIGHT = 400;

constexpr float ballSize = 8.f;
constexpr float ballOrigin = ballSize / 2;

enum {
	PLAYER = 0,
	BALL,
	OBSTACLE
};

enum {
	RECTANGLE = 0,
	CIRCLE,
	VERTEX
};


sf::Vector2f toCenter(const sf::Vector2f& lho, const sf::Vector2f& rho)
{
	return sf::Vector2f((lho.x / 2) - (rho.x / 2), (lho.y / 2) - (rho.y / 2));
}

sf::Vector2f toCenter(const sf::Vector2i& lho, const sf::Vector2f& rho)
{
	return sf::Vector2f((lho.x / 2) - (rho.x / 2), (lho.y / 2) - (rho.y / 2));
}

sf::Vector2f toCenter(const sf::Vector2f& lho, const float& rho)
{
	return sf::Vector2f((lho.x / 2) - (rho / 2), (lho.y / 2) - (rho / 2));
}

void addObstacle(Game& game, int& counter, const sf::Vector2f& size, const int& type = 0)
{
	sf::Shape* shape = nullptr;
	sf::Vector2f new_pos;


	switch (type)
	{
	case RECTANGLE:
	{
		shape = new sf::RectangleShape(size);
		shape->setOrigin(size / 2.f);
		shape->setPosition(
			sf::Vector2f(50.f, 50.f) +
			sf::Vector2f(static_cast<float>(counter % 10)  * size.x * 1.1f, static_cast<float>(counter / 10) * 15.f)
		);
		shape->setFillColor(sf::Color(240, 240, 250, 250));
		shape->setOutlineColor(sf::Color(180, 180, 220, 200));
		shape->setOutlineThickness(2.f);
		game.getScreen().addElement(*(dynamic_cast<sf::RectangleShape*>(shape)));
		break;
	}
	case CIRCLE:
	{
		shape = new sf::CircleShape(size.x);
		shape->setOrigin(size / 2.f);
		shape->setPosition(size + sf::Vector2f(static_cast<float>(counter) * size.x, 0));
		shape->setFillColor(sf::Color(240, 240, 250));
		shape->setOutlineColor(sf::Color(180, 180, 220));
		shape->setOutlineThickness(2.f);
		game.getScreen().addElement(*(dynamic_cast<sf::CircleShape*>(shape)));
		break;
	}
	case VERTEX:
		break;

	default:
		break;
	}
	++counter;	// number of objects created
}

/*
TODO:

Add hitboxes
Add gravity

*/

int main()
{
	Game game(W_WIDTH, W_HEIGHT, 32, "Title!");
	game.getWindow().setPosition(sf::Vector2i((1920 / 2) - (W_WIDTH / 2), (1080 / 2) - (W_HEIGHT / 2)));		// Center the window
	sf::Vector2f windowSize(W_WIDTH, W_HEIGHT);	//todo remove

	// View	not working
	sf::View view(
		sf::Vector2f(350.f, 300.f),		// center
		sf::Vector2f(100.f, 100.f));	// size

	// Data
	float offset = 3.f;
	float x = 1, y = 3;
	sf::Shape* shape = nullptr;
	sf::Vector2f direction = sf::Vector2f(x, y);
	float velocity = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	// Time
	Timer timer = Timer();	


	/* Shapes */
	// P1
	sf::Vector2f rectSize(65.f, 8.f);
	shape = new sf::RectangleShape(rectSize);
	shape->setOrigin(rectSize / 2.f);
	shape->setPosition(toCenter(windowSize, rectSize) + sf::Vector2f(0, 150.f));
	shape->setFillColor(sf::Color(250, 180, 180));
	shape->setOutlineColor(sf::Color(180, 180, 180));
	shape->setOutlineThickness(2.f);
	sf::Drawable* p1 = dynamic_cast<sf::RectangleShape*>(shape);
	game.getScreen().addElement(*p1);

	// O1 (Ball)
	shape = new sf::CircleShape(ballSize);
	shape->setOrigin(sf::Vector2f(ballSize, ballSize) / 2.f);
	shape->setPosition(toCenter(windowSize, ballSize));
	shape->setFillColor(sf::Color::White);
	sf::Drawable* o1 = dynamic_cast<sf::CircleShape*>(shape);
	game.getScreen().addElement(*o1);

	// O2 (Obstacle)
	shape = new sf::CircleShape(80.f, 10U);
	shape->setOrigin(rectSize / 2.f);
	shape->setPosition(toCenter(windowSize, rectSize) - sf::Vector2f(70.f, 50.f));
	shape->setFillColor(sf::Color(250,120,160,50));
	game.getScreen().addElement(*(dynamic_cast<sf::CircleShape*>(shape)));

	int counter = 0;
	for (int i = 0; i < 80; i++) {
		addObstacle(game, counter, sf::Vector2f(50.f, 10.f), RECTANGLE);
	}


	/* Window data */
	while (game.isOpen())
	{
		sf::Event event;
		while (game.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				game.close();

			// Events for key presses
			if (event.type == sf::Event::KeyPressed) {
				// Close the game
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					game.close();
				}
			}
		}

		// Keyboard 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
			game.rotate(OBSTACLE, offset);
			velocity *= 1.1f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
			game.rotate(OBSTACLE, -2 * offset);
			velocity /= 1.1f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) | sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			game.move(PLAYER, sf::Vector2f(0, -offset));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) | sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			game.move(PLAYER, sf::Vector2f(0, offset));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) | sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			game.move(PLAYER, sf::Vector2f(-offset, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) | sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			game.move(PLAYER, sf::Vector2f(offset, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		}

		// Mouse logic
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			shape = dynamic_cast<sf::RectangleShape*>(game.getScreen().sceneElements[PLAYER]);
		}

		/* At some point I might get steam controllers to work *
		if (SteamAPI_Init()) {
			if (sf::Joystick::isButtonPressed(0, sf::Joystick::X)) {
			}
		}
		else {
			std::cout << "No steam API\n";
		}/* todo: fix */


		// Test - Rotating in the background, todo remove
		shape = dynamic_cast<sf::CircleShape*>(game.getScreen().sceneElements[OBSTACLE]);
		shape->scale(1.0001f, 1.0001f);
		shape->rotate(1.0f);



		// Ball bounce
		shape = dynamic_cast<sf::CircleShape*>(game.getScreen().sceneElements[BALL]);
		timer.updateElapsedTime();
		while (timer.getElapsedTime() >= timer.getUpdateMs()) {
			const auto pos = shape->getPosition();
			const auto delta = timer.getUpdateMs().asSeconds() * velocity;
			sf::Vector2f new_pos(pos.x + direction.x * delta, pos.y + direction.y * delta);

			if (new_pos.x - ballOrigin < 0) {			// left window edge
				direction.x *= -1;
				new_pos.x = 0 + ballOrigin;
			}
			else if (new_pos.x + ballSize > W_WIDTH - ballOrigin) {	// right window edge
				direction.x *= -1;
				new_pos.x = W_WIDTH - ballSize - ballOrigin;
			}
			else if (new_pos.y - ballOrigin < 0) {	// top window edge
				direction.y *= -1;
				new_pos.y = 0 + ballOrigin;
			}
			else if (new_pos.y + ballSize > W_HEIGHT - ballOrigin) {	// bottom window edge
				direction.y *= -1;
				new_pos.y = W_HEIGHT - ballSize - ballOrigin;
			}
			shape->setPosition(new_pos);
			timer.subtractMsFromElapsed();
		}

		// get the bounding box of the entity
		shape = dynamic_cast<sf::RectangleShape*>(game.getScreen().sceneElements[PLAYER]);
		sf::FloatRect boundingBoxPlayer = shape->getGlobalBounds();
		shape = dynamic_cast<sf::CircleShape*>(game.getScreen().sceneElements[BALL]);
		sf::FloatRect boundingBoxBall = shape->getGlobalBounds();

		std::vector<int> shapeElementId;
		// Collision with player
		if (boundingBoxBall.intersects(boundingBoxPlayer)) {
			direction.y *= -1.01f;
		}

		// Collision with obstacles
		for (int i = 1; i < game.getScreen().sceneElements.size(); i++) {
			if (dynamic_cast<sf::RectangleShape*>(game.getScreen().sceneElements[i]) != nullptr) {
				shape = dynamic_cast<sf::RectangleShape*>(game.getScreen().sceneElements[i]);
				sf::FloatRect box = shape->getGlobalBounds();

				if (boundingBoxBall.intersects(box)) {
					shape->setFillColor(sf::Color::Red);
					direction.y *= -1;
					game.getScreen().sceneElements.erase(game.getScreen().sceneElements.begin() + i);
				}
			}
		}

		game.update();
	}

	return 0;
}
