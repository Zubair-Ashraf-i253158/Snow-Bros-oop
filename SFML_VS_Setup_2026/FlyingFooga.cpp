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
        60.0f / enemyTexture.getSize().x,  // auto fit to 60px wide
        64.0f / enemyTexture.getSize().y   // auto fit to 64px tall
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
    if (state == 2 || state == 3 || state == 4)
    {
        Botom::update(platforms, count);
        return;
    }

    flyTime++;

    if (!flyingE)
    {
        Botom::update(platforms, count);
        if (groundE && flyTime > 180)
        {
            flyingE = true;
            flyTime = 0;
            jumpE = 0;
        }
    }
    else //flying
    {
        enemy.move(flyx, flyy);

        //left right
        if (enemy.getPosition().x < 0 || enemy.getPosition().x > 770)
            flyx = -flyx;

        //top 
        if (enemy.getPosition().y < 30)
            flyy = 2.0f; //DOWN JAO

        //ground se neeche bilkul nahi
        if (enemy.getPosition().y > 480)
        {
            flyy = -2.0f; //UPAR JA
            enemy.setPosition(enemy.getPosition().x, 480);
        }

        if (flyTime > 300) //land
        {
            flyingE = false;
            flyTime = 0;
            jumpE = 5.0f; //PLATFORM PA LAND

            // nearest platform dhundo aur wahan rakh do
            float bestY = 524; // default ground
            for (int i = 0; i < count; i++)
            {
                sf::FloatRect pl = platforms[i].getBounds();
                //platform jo enemy ke neeche ho
                if (pl.top > enemy.getPosition().y &&
                    pl.top < bestY)
                    bestY = pl.top;
            }
            //enemy ko platform ke upar rakh do
            enemy.setPosition(
                enemy.getPosition().x,
                bestY - enemy.getGlobalBounds().height
            );
            groundE = true;
        }
    }
}
void FlyingFooga::draw(sf::RenderWindow& window)
{
    Botom::draw(window);
    //inheritance ha to is lyie botom ka draw function call kar raha hu taki 
    // tornado bhi draw ho jai aur uska flying behavior bhi work kare

}
