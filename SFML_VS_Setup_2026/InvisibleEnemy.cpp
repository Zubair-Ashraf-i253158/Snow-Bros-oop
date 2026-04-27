#include "InvisibleEnemy.h"
#include "Tornado.h"

Invisible::Invisible(float x, float y) : Tornado(x, y)
{

    enemyTexture.loadFromFile("assets/invis.png");
    enemy.setTexture(enemyTexture);
    enemy.setScale(
        70.0f / enemyTexture.getSize().x,  // auto fit to 60px wide
        74.0f / enemyTexture.getSize().y   // auto fit to 64px 
    );
	
    

    see = true;    //shuru mein visible hai
    seeTime = 0.0f; //timer zeroo 
    healthE = 3.0f; 
    speedE = 3.0f;  //thora fast

}

void Invisible::update(Platform platforms[], int count, sf::Vector2f p_pos)
{
    
    Tornado::update(platforms, count, p_pos);  //tornado ka pura update call karo
                                               //walk ,fly and knife sab ho jaye ga

   
    if (flyingE) 
    //fly ke sath visibility adding
    //agar fly kar raha hai
    {
        see = false; //gayab GEE
    }
    else // zameen par
    {
        see = true; // wapas visible
    }
}

void Invisible::draw(sf::RenderWindow& window)
{
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
    {
		if (!zindaE)
            return; // agar enemy mar chuka hai to kuch mat draw karo
        
        if (zindaE)
        {
            // yellow outline for the special enemy
            sf::RectangleShape box;

            box.setSize(sf::Vector2f( enemy.getGlobalBounds().width , enemy.getGlobalBounds().height ));
           
            box.setPosition(enemy.getPosition());
            box.setFillColor(sf::Color::Transparent);
           
            box.setOutlineColor(sf::Color::Yellow); // yellow for special enemy

            box.setOutlineThickness(5);
            window.draw(box);
        }
    }
    else
    {
                 // normal game mein
        if (see) // sirf tab draw karo jab visible ho
        {
            if(zindaE)
            Tornado::draw(window); // tornado ka draw use karo
        }
		// agar see = false hai to kuch mat draw karo enemy invisible hai
    }
}

