#include "Enemy.h"
#include "MOGERA.h"
#include "MogeraBabies.h"


Mchild::Mchild(float x, float y)
{
	//enemy.setSize(sf::Vector2f(15, 15));
	//enemy.setFillColor(sf::Color::Cyan);
	enemy.setPosition(x, y);
	
	speedE = 2.0f;  
	healthE = 1.0f; //health 1 matlub player ki one hit kiya to baby mar jaayega 
	zindaE = true;
	jumpMC = 0;
	groundMC = false;	
}

void Mchild::update(Platform platforms[], int count)
{
	enemy.move(speedE * directionE, 0); // baby Move horizontally
	enemy.move(0, jumpMC); // Apply vertical movement [jump anddd fall]
	jumpMC = jumpMC + 0.3f; // this makes falling faster and faster by adding 0.3 to jumpMC every frame
	groundMC = false; // har time fall
	
	for (int i = 0; i < count; i++)
	{
		sf::FloatRect pl_bndry = platforms[i].getBounds(); //platform ki boundary
		sf::FloatRect e_bndry = enemy.getGlobalBounds();    //baby ki boundary
		
		// Check if baby bottom is hitting platform top
		
		bool side =(e_bndry.left < pl_bndry.left + pl_bndry.width) && (e_bndry.left + e_bndry.width > pl_bndry.left);
		bool top = (e_bndry.top + e_bndry.height >= pl_bndry.top) && (e_bndry.top + e_bndry.height <= pl_bndry.top + 20);
		
		if (side && top)
		{
			enemy.setPosition(enemy.getPosition().x, pl_bndry.top - e_bndry.height);
			jumpMC = 0;
			groundMC = true;
		}
	}
	if (enemy.getPosition().x < 0)
	{
		zindaE = false; // baby dies if it hits the left wall
	}
	else if (enemy.getPosition().x > 785)  // 800 - 15 (baby width)
	{
		zindaE = false; // baby dies if it hits the right wall
	}
	
}

void Mchild::draw(sf::RenderWindow& window)
{
	if (zindaE)     // ager baby zinda hai to hi draw karo warna nahi
		window.draw(enemy);
}