#pragma once
#include"Platform.h"
#include <SFML/Graphics.hpp>

class Enemy {

protected:
	sf::Vector2f position;
	float speedE;
	float healthE;
	float zindaE;
	float directionE;

private:
		sf::RectangleShape enemy;

public:

	virtual void update() = 0;
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
		healthE -= amount;
		if (healthE <= 0) {
			zindaE = false;
		}
	}
};
