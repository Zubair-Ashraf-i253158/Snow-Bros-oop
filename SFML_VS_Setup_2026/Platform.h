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
		platform.setFillColor(sf::Color(0, 0, 0, 0)); // fully transparent
		platform.setOutlineColor(sf::Color::Green); // only for debug
		platform.setOutlineThickness(1);
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