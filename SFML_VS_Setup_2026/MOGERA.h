#pragma once


#include "Enemy.h"	
#include "Platform.h"
#include "MogeraBabies.h"

//khud asan tornado bana kr zubair bhai ne boss merey mathey mardia 
//rona nahi -Call karu bacha :D

class Mogera : public Enemy
{
protected:
	Mchild babies[10]; //mogera ke 10 babies hongee;
	int babyCount; //mogera ke kitne babies zinda hain
	
	sf::RectangleShape Hbar; //health bar
	sf::RectangleShape HbarBack; //health bar background 

	float Health; //mogera ki health
	float timeB; //time jis ke bad baby phainkni hai

public:
	Mogera(float x, float y);
	
	// base class ka update override karo - ZARURI HAI
	void update(Platform platforms[], int count) override
	{
		// khali rehne do ya playerPos ke bagair call karo
	}

	void update(Platform platforms[], int count, sf::Vector2f playerPos);
	void draw(sf::RenderWindow& window) override;
	float getHealth() const;

};
