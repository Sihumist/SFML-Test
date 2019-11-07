#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class Screen : public sf::Drawable
{
public:
	std::vector<sf::Drawable*> sceneElements;
	sf::Sprite backgroundSprite;
	Screen();
	virtual ~Screen();
	virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	void addElement(sf::Drawable& element);

protected:
	sf::Texture backgroundTexture;
};