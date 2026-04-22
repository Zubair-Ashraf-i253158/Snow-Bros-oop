#include "Botom.h"

Botom::Botom(float x, float y)
{
	enemy.setSize(sf::Vector2f(30, 30));
	enemy.setFillColor(sf::Color::Blue);
	enemy.setPosition(x,y);
	speedE = 2.0f;  
	healthE = 100.0f; //heaalth 
	zindaE = true;
	directionE = 1.0f; // Start moving right
	jumpE = 0;
	groundE = false;	
}

void Botom::update(Platform platforms[], int count )
{
	enemy.move(speedE * directionE, 0); // enemy Move horizontally
    enemy.move(0, jumpE); // Apply vertical movement [jump anddd fall]
	jumpE = jumpE + 0.3f; // this makes falling faster and faster by adding 0.3 to jumpE every frame

	groundE = false; // har time fall

	for (int i = 0; i < count; i++)
	{
		sf::FloatRect pl_bndry = platforms[i].getBounds(); //platform ki boundary
		sf::FloatRect e_bndry = enemy.getGlobalBounds();    //enemy ki boundary
		
		// Check if enemy bottom is hitting platform top
		
		bool side =(e_bndry.left < pl_bndry.left + pl_bndry.width) && (e_bndry.left + e_bndry.width > pl_bndry.left);
		bool top = (e_bndry.top + e_bndry.height >= pl_bndry.top) && (e_bndry.top + e_bndry.height <= pl_bndry.top + 20);
		
		if (side && top)
		{
			enemy.setPosition(enemy.getPosition().x, pl_bndry.top - e_bndry.height);
			jumpE = 0;
			groundE = true;
		}
	}

	//Now change direction if enemy hits the wallss haahahahahaha
	//Zubair kia apkey toothpaste ma namak hy?   bilkul hai 
	//SARA kaam ma kr raha hu and ya bas so raha ha :(
	
	// jhoot nahi ap to foootball khail rahay ho project kn karay ga :D
	if (enemy.getPosition().x < 0)
	{
		enemy.setPosition(0, enemy.getPosition().y);
		directionE = 1.0f; // Move right
	}
	else if (enemy.getPosition().x > 770)  // 800 - 30 (enemy width)
	{
		enemy.setPosition(770, enemy.getPosition().y);
		directionE = -1.0f; // Move left
	}

}

void Botom::draw(sf::RenderWindow& window)
{
	if (zindaE)     // ager enemy zinda hai to hi draw karo warna nahi
	window.draw(enemy);
}