#pragma once

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{	
private:
	sf::RectangleShape player;
	float movement = 3.0f;     // left right speed
	float jump = -8.0f;    // jump strength
	float gravity = 0.3f;       // fall speed
	float jumpSpeed = 0.0f;     // current up/down speed
	bool Ground = true;
	// Required override from sf::Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(player, states);
	}
public:

	Player();
	void update();

};