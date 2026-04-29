#include "FlyingFooga.h"

//IISE SET KRLE ZUBAIR 
//isse ma comment kr raha hu to wasee error ai ga isse comment kr kr run kr phr ya variable dame and sara system dakh le

FlyingFooga::FlyingFooga(float x, float y) : Botom(x, y)
{
	//enemy.setSize(sf::Vector2f(30, 30));
	//enemy.setFillColor(sf::Color::Yellow);
    enemyTexture.loadFromFile("assets/ff.png");
    enemy.setTexture(enemyTexture);
    enemy.setScale(
        70.0f / enemyTexture.getSize().x,  // auto fit to 60px wide
        74.0f / enemyTexture.getSize().y   // auto fit to 64px tall
    );
    speedE = 2.0f;  
	healthE = 2.0f;   //health 2 means need two hits to kill
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
    if (state == 2 || state == 3 || state == 4) // encased states  botom handle kare
    {
        Botom::update(platforms, count);
        return;
    }

    flyTime++;

    if (!flyingE)
    {
        Botom::update(platforms, count); // normal walk
        if (groundE && flyTime > 180)
        {
            flyingE = true;
            flyTime = 0;
            jumpE = 0; // reset before flying
        }
    }
    else // flying mode
    {
        enemy.move(flyx, flyy);

        // screen boundaries - bounce
        if (enemy.getPosition().x < 0 || enemy.getPosition().x > 770)
            flyx = -flyx;
        if (enemy.getPosition().y < 10) // top boundary
            flyy = -flyy;
        if (enemy.getPosition().y > 500) //bottom boundary ground se upar rakho
        {
            flyy = -2.0f; // force upward
            enemy.setPosition(enemy.getPosition().x, 500); // ground se neeche na jaye
        }

        if (flyTime > 300) // land karo
        {
            flyingE = false;
            flyTime = 0;
            jumpE = 0; // IMPORTANT reset jumpE landing par
        }
    }
}
void FlyingFooga::draw(sf::RenderWindow& window)
{
    Botom::draw(window);
    //inheritance ha to is lyie botom ka draw function call kar raha hu taki 
    // tornado bhi draw ho jai aur uska flying behavior bhi work kare

}
