#pragma once

#include <SFML/Graphics.hpp>

class Player
{	
private:
	sf::RectangleShape player;
	float movement = 3.0f;     // left right speed
	float jump = -8.0f;    // jump strength
	float gravity = 0.3f;       // fall speed
	float jumpSpeed = 0.0f;     // current up/down speed
	bool Ground = true;

public:

	Player();
	void update();
	void draw(sf::RenderWindow& window);
};