#pragma once
#include <SFML/Graphics.hpp>
class Platform
{
private:

	sf::RectangleShape platform;
public:
	Platform(float x, float y, float width, float height)
	{
		platform.setSize(sf::Vector2f(width, height));
		platform.setFillColor(sf::Color::Green);
		platform.setPosition(x, y);
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(platform);
	}
	sf::FloatRect getBounds() const
	{
		return platform.getGlobalBounds();
	}
};