#pragma once
#include <SFML/Graphics.hpp>
class Platform
{
private:

	sf::RectangleShape platform;
public:
	Platform() : platform() {}
	
	Platform(float x, float y, float width, float height)
	{
		platform.setSize(sf::Vector2f(width, height));
		platform.setFillColor(sf::Color(0, 0, 0, 0)); // fully transparent
		//platform.setOutlineColor(sf::Color::Green); // only for debug
		//platform.setOutlineThickness(5);
		platform.setPosition(x, y);
	}
	void draw(sf::RenderWindow& window)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			// BLUE rectangle platform hitbox
			sf::RectangleShape box;
           
			box.setSize(sf::Vector2f( platform.getGlobalBounds().width   ,   platform.getGlobalBounds().height));
			box.setPosition(platform.getPosition());
			box.setFillColor(sf::Color::Transparent);
			box.setOutlineColor(sf::Color::Blue); // blue platform ke liye
			box.setOutlineThickness(5);
			window.draw(box);
		}
		else
			window.draw(platform); // normal draw
	}
	sf::FloatRect getBounds() const
	{
		return platform.getGlobalBounds();
	}
};