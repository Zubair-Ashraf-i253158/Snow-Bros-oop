#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"

class Enemy {

protected:
	sf::Vector2f position;
	float speedE;
	float healthE;
	bool zindaE;
	float directionE;

	sf::RectangleShape enemy;

public:
	//this is abstract class matlub ke is class ke object nahi ban sakta, iske sirf derived class ke object ban sakta hai
	virtual void update(Platform platforms[], int count) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	void setPosition(float x, float y) {
		enemy.setPosition(x, y);
	}
	void setSpeed(float speed) {
		speedE = speed;
	}
	void setHealth(float health) {
		healthE = health;
	}
	void setDirection(float direction) {
		directionE = direction;
	}
	void setZinda(bool zinda) {
		zindaE = zinda;
	}
	
	bool getZinda() const {
		return zindaE;
	}

	sf::FloatRect getBounds() const {
		return enemy.getGlobalBounds();
	}
	sf::Vector2f getPosition() const {
		return enemy.getPosition();
	}	

	void damage(float amount) {
		healthE = healthE - amount;
		if (healthE <= 0) {
			zindaE = false;
		}
	}
};


