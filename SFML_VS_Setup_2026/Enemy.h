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
	sf::CircleShape snowcover;
	sf::Texture enemyTexture;
    sf::Sprite enemy;
	int state = 0;
	int meltTime = 0;
	float roll = 1.0f;
	/*hitting and collision code*/

	bool cover = false; //enemy snow ma band naahi ha


public:
	//this is abstract class matlub ke is class ke object nahi ban sakta, iske sirf derived class ke object ban sakta hai
	virtual void update(Platform platforms[], int count) = 0;
	//state 0 ka meaning ha normal, 1 ka meaning ha half encased, 2 ka meaning ha fully encased, 3 ka meaning ha rolling, 4 ka meaning ha melting

	void hitByBall()
	{
		if (state == 0 || state == 1)
		{
			healthE--;
			if (healthE <= 0)
				state = 2; // fully covered snow ma
			else
				state = 1; // half covered snow ma
		}
	}

	void kick(float kik)
	{
		if (state == 2) { state = 3; roll = kik; }
	}

	int getState() const { return state; }
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
	void setdirection(float direction) {
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


