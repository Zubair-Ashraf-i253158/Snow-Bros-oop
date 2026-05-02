#pragma once
#include"Platform.h"
#include <SFML/Graphics.hpp>
#include "SnowBall.h"
#include "Botom.h"
#include "Enemy.h"
#include "HUD.h"
class Player : public sf::Drawable
{	
private:

	/* Snowball */
	SnowBall ball[10]; // player ka snowball
	int ballcount = 10;
	bool fire=false;     // kya player fire kar raha hai ya nahi
	sf::Texture playerTexture;   //idle
	sf::Texture jumpTexture;     //jump
	sf::Sprite playerSprite;
	
	float movement = 3.0f;     // left right speed
	float jump = -7.0f;    // jump strength
	float gravity = 0.3f;       // fall speed
	float jumpSpeed = 0.0f;     // current up/down speed
	bool Ground = true;
	
	
	int animFrame = 0;    // knsa fram ha abhi
	int animTimer = 0;    // time jab frame change hona chahiye
	bool facingRight = true;
	bool jmp = false;

	/*Life Health and Collosion code  */
	int lives = 2;
	bool hit = false; // player hit hua hai ya nahi
	int hitTimer = 0; // hit ke baad invincibility time
	
	//for hud 
	int score = 0; // player ka score
	int gems = 0; // player ke paas gems

public:

	Player();
	sf::Vector2f getPosition() const {
		return playerSprite.getPosition();
	}
	//void update(Platform platforms[], int count);
	void update(Platform platforms[], int count, Enemy* enemy[], int ecount);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	/*Life Health and Collosion code  */
	
	void lifedown();   //life kam ho ge is fun maa
	bool gethit();    //getter for hit status
	int getlives() const; //getter for lives count

	sf::FloatRect getBounds() const;   //it give four things left, top, width, height of player boundary 
	int getballcount() const;

	sf::FloatRect getBallBounds(int index) const; // it gives the boundary of the snowball at the given index	
	bool getBallActive(int i) const;
	void setBallActive(int i, bool a);




	/*======GETTERS FOR HUD ======*/
	int getScore() const
	{
		return score; // current score do
	}

	int getLive() const
	{
		return lives; // current lives do
	}

	int getGem() const
	{
		return gems; // current gems do
	}


};