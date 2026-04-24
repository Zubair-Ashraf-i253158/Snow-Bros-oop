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

	sf::Texture enemyTexture;
    sf::Sprite enemy;

	/*hitting and collision code*/

	bool cover = false; //enemy snow ma band naahi ha


public:
	//this is abstract class matlub ke is class ke object nahi ban sakta, iske sirf derived class ke object ban sakta hai
	virtual void update(Platform platforms[], int count) = 0;
	
	virtual void update(Platform platforms[], int count, sf::Vector2f playerPos)
	{
		
		update(platforms, count);
	}
	
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
	
	bool getZinda() const {    //return ka zinda ha ya mar gaya
		return zindaE;
	}

	bool getCover() const {      //return ka cover ha ya nahi
		return cover;
	}

	void damage(float howmuch) {
		
		healthE =healthE - howmuch;
		
		if (healthE <= 0) 
		{
			zindaE = false;
		}
	}

	sf::FloatRect getBounds() const {
		return enemy.getGlobalBounds();
	}
	sf::Vector2f getPosition() const {
		return enemy.getPosition();
	}	

};


