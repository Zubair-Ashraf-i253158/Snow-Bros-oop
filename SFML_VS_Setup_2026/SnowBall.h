#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"

class SnowBall
{
private:
	sf::CircleShape ball; // snowball shape
	bool active; // is snowball active
	float directionX; // snowball horizontal direction
	float directionY; // snowball vertical direction
	float speed; // snowball speed

public:
	SnowBall();
	void setfire(float x, float y);
	void shoot(float dirX); // shoot the snowball in a direction
	void update(); // update the snowball position
	
	void setact(bool active);             // setter
	bool act() const;                   //getter
	
 void draw(sf::RenderTarget& target) const; // draw the snowball
	sf::FloatRect getBounds() const; // get the bounding box of the snowball
};
