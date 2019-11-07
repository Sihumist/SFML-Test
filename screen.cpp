#include "screen.h"

Screen::Screen()
{
	this->backgroundSprite = sf::Sprite(sf::Texture());
}

Screen::~Screen()
{
}

void Screen::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
	for (const auto& e : sceneElements)
		rt.draw(*e, states);
}

void Screen::addElement(sf::Drawable& element)
{
	this->sceneElements.push_back(&element);
}
