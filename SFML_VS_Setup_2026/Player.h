#pragma once
#include"Platform.h"
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{	
private:
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	float movement = 3.0f;     // left right speed
	float jump = -7.0f;    // jump strength
	float gravity = 0.3f;       // fall speed
	float jumpSpeed = 0.0f;     // current up/down speed
	bool Ground = true;
	// Required override from sf::Drawable
	int animFrame = 0;    // knsa fram ha abhi
	int animTimer = 0;    // time jab frame change hona chahiye
	bool facingRight = true;
	bool jmp = false;
public:

	Player();
	sf::Vector2f getPosition() const {
		return playerSprite.getPosition();
	}
	void update(Platform platforms[], int count);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};