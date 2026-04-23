#include "FlyingFooga.h"

//IISE SET KRLE ZUBAIR 
//isse ma comment kr raha hu to wasee error ai ga isse comment kr kr run kr phr ya variable dame and sara system dakh le

FlyingFooga::FlyingFooga(float x, float y) : Botom(x, y)
{
	//enemy.setSize(sf::Vector2f(30, 30));
	//enemy.setFillColor(sf::Color::Yellow);
	speedE = 2.0f;  //health 2 means need two hits to kill
	healthE = 100.0f;
	zindaE = true;
    groundE = false;
	directionE = 1.0f; // Start moving right
	
	flyingE = false;     // is flying
	flyy = -2.0f; //fly ki speed vertical
	flyx = 3.0f; //fly ki speed horizonatal
	flyTime = 0.0f;//time jab tak enemy fly karega
}
void FlyingFooga::update(Platform platforms[], int count)
{
    flyTime++;

    if (!flyingE)
    {
        Botom::update(platforms, count); // normal walk on ground

        if (groundE && flyTime > 180) // 3 seconds on ground then fly
        {
            flyingE = true;
            flyTime = 0;
        }
    }
    else // flying
    {
        enemy.move(flyx, flyy); // fly movement

        // boundary
        if (enemy.getPosition().x < 0 || enemy.getPosition().x > 770)
            flyx = -flyx;
        if (enemy.getPosition().y < 0 || enemy.getPosition().y > 540)
            flyy = -flyy;

        if (flyTime > 300) // land after 5 sec 
        {
            flyingE = false;
            flyTime = 0;
        }
    }
	
}
void FlyingFooga::draw(sf::RenderWindow& window)
{
	if (zindaE)     // ager enemy zinda hai to hi draw karo warna nahi
		window.draw(enemy);
}