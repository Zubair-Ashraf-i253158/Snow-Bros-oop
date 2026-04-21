#pragma once
#include"Platform.h"
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{	
private:
	sf::RectangleShape player;
	float movement = 3.0f;     // left right speed
	float jump = -11.0f;    // jump strength
	float gravity = 0.3f;       // fall speed
	float jumpSpeed = 0.0f;     // current up/down speed
	bool Ground = true;
	// Required override from sf::Drawable
	
public:

	Player();
	sf::Vector2f getPosition() const {
		return player.getPosition();
	}
	void update(Platform platforms[], int count);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};