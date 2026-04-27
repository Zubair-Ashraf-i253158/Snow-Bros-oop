#include "Botom.h"
#include"Collision.h"

Botom::Botom(float x, float y)
{ 
    // texture load karo agar nahi mila to rectangle use karo
    if (!enemyTexture.loadFromFile("assets/enemy.png"))
    {
        // texture nahi mila to phr rectangle use karo
        // sprite transparent
        enemy.setColor(sf::Color::Transparent);
    }
    else
    {
        // texture mil gaya to sprite set karo
        enemy.setTexture(enemyTexture);
        enemy.setScale(
            60.0f / enemyTexture.getSize().x,
            64.0f / enemyTexture.getSize().y
        );
    }
	
    enemy.setPosition(400, 400);
    
    snowcover.setFillColor(sf::Color::White);
	enemy.setPosition(x, y);
	
    speedE = 2.0f;  
	healthE = 2.0f; //heaalth 
	zindaE = true;
	directionE = 1.0f; // Start moving right
	jumpE = 0;
	groundE = false;            
}

void Botom::update(Platform platforms[], int count)
{
    if (state == 0 ) // normal ya half encased can walk
    {
        enemy.move(speedE * directionE, 0);
        enemy.move(0, jumpE);
        jumpE += 0.3f;
        groundE = false;
        
        for (int i = 0; i < count; i++)
        {
            sf::FloatRect pl = platforms[i].getBounds();
            sf::FloatRect eb = enemy.getGlobalBounds();
           
            bool side = (eb.left < pl.left + pl.width) && (eb.left + eb.width > pl.left);
            bool top = (eb.top + eb.height >= pl.top) && (eb.top + eb.height <= pl.top + 30);
            
            if (side && top) 
            { 
                enemy.setPosition(enemy.getPosition().x, pl.top - eb.height);
                jumpE = 0; 
                groundE = true; 
            }
        }
        if (enemy.getPosition().x < 0) 
        { 
            enemy.setPosition(0, enemy.getPosition().y);
            directionE = 1.0f; 
        }
        else if (enemy.getPosition().x > 770)
        {
            enemy.setPosition(770, enemy.getPosition().y); 
            directionE = -1.0f;
        }
    }
   
    else if (state == 2 || state == 1) // full snow ma cover ha to still rahay 
    {
        enemy.move(0, jumpE);
        jumpE += 0.3f;
       
        for (int i = 0; i < count; i++)
        {
            sf::FloatRect pl = platforms[i].getBounds();
            sf::FloatRect eb = enemy.getGlobalBounds();
           
            bool side = (eb.left < pl.left + pl.width) && (eb.left + eb.width > pl.left);
            bool top = (eb.top + eb.height >= pl.top) && (eb.top + eb.height <= pl.top + 30);
            
            if (side && top) 
            {
                enemy.setPosition(enemy.getPosition().x, pl.top - eb.height);
                jumpE = 0;
            }
        }
        meltTime++;
        if (meltTime > 300)
        { 
            state = 4; 
            meltTime = 0; 
        } //snow melt hona shuru 
    }
    
    else if (state == 3) // rolling ,fast move karay and wall ka sath takrai to mar jai
    {
        enemy.move(roll * 5.0f, 0);
        enemy.move(0, jumpE);
        jumpE += 0.3f;
        
        for (int i = 0; i < count; i++)
        {
            
            sf::FloatRect pl = platforms[i].getBounds();
            sf::FloatRect eb = enemy.getGlobalBounds();
            
            bool side = (eb.left < pl.left + pl.width) && (eb.left + eb.width > pl.left);
            bool top = (eb.top + eb.height >= pl.top) && (eb.top + eb.height <= pl.top + 30);
            
            if (side && top) 
            {
                enemy.setPosition(enemy.getPosition().x, pl.top - eb.height); 
                jumpE = 0; 
            }
        }
        if (enemy.getPosition().x <= 0 || enemy.getPosition().x >= 770)
			zindaE = false; // wall hit karay to mar jai
    }
    else if (state == 4) // melt hona shuru 
    {
        meltTime++;
        if (meltTime > 200) 
        {
            state = 0;
            meltTime = 0; 
            healthE = 2.0f; 
        }
    }
}

void Botom::draw(sf::RenderWindow& window)
{ /*
    if (!zindaE) 
        return;
    
    window.draw(enemy); // pehle enemy draw karo
    sf::FloatRect e = enemy.getGlobalBounds();

    if (state == 1) // half snow ma cover
    {
        sf::CircleShape snow;
        snow.setFillColor(sf::Color(255, 255, 255, 180));
        snow.setRadius(e.width / 3); // sirf neeche half
        snow.setPosition(e.left, e.top + e.height / 2);
        window.draw(snow);
    }
    else if (state == 2 || state == 3) // full snow
    {
        sf::CircleShape snow;
        snow.setFillColor(sf::Color(255, 255, 255, 220));//full cover
        snow.setRadius(e.width / 2);
        snow.setPosition(e.left, e.top);
        window.draw(snow);
    }
    else if (state == 4) // snow melt ho rahi ha 
    {
        sf::CircleShape snow;
		float meltPercent = 1.0f - (meltTime / 200.0f); //melt time ka hisab sa size kam karo
        snow.setFillColor(sf::Color(255, 255, 255, 150));
        snow.setRadius(e.width / 2 * meltPercent);
        snow.setPosition(e.left ,e.top);
        window.draw(snow);
    }*/

    /*SAME CODE JUST ADDING HITBOX THING */
   
    if (!zindaE) 
        return; 

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) 
    {
        window.draw(enemy); //NORMAL enemy sprite
        sf::RectangleShape box;// ENEMY HITBOX 

        // enemy sprite ke height aur width ke hisab se box ka size set karo
        box.setSize(sf::Vector2f( enemy.getGlobalBounds().width, enemy.getGlobalBounds().height));

        box.setPosition(enemy.getPosition()); // enemy sprite ke position par box set karo
        box.setFillColor(sf::Color::Transparent); // box transparent 
        box.setOutlineColor(sf::Color::Red); // red color enemy ke liye
        box.setOutlineThickness(5); // box ka outline thickness

        window.draw(box); // hitbox ko sprite ke upar draw karo


        // SNOW EFFECT
        sf::FloatRect e = enemy.getGlobalBounds(); // enemy ka bounds store karo

        if (state == 1) // half snow
        {
            sf::CircleShape snow;

            snow.setFillColor(sf::Color(255, 255, 255, 180)); // halka transparent snow
            snow.setRadius(e.width / 3); // half snow
            snow.setPosition(e.left, e.top + e.height / 2); // niche side par position

            window.draw(snow); // snow draw karo
        }
        else if (state == 2 || state == 3) // full snow
        {
            sf::CircleShape snow;

            snow.setFillColor(sf::Color(255, 255, 255, 220)); // zyada visible snow
            snow.setRadius(e.width / 2); // full size snow
            snow.setPosition(e.left, e.top); // upar se cover 

            window.draw(snow); // snow draw karo
        }
        else if (state == 4) // melting
        {
            sf::CircleShape snow;   

            float meltPercent = 1.0f - (meltTime / 200.0f); // melt hone ka percent calculate karo

            snow.setFillColor(sf::Color(255, 255, 255, 150)); // halka fade snow
            snow.setRadius(e.width / 2 * meltPercent); // dheere dheere size kam ho
            snow.setPosition(e.left, e.top);

            window.draw(snow); // melting snow draw karo
        }
    }
    else
    {
        window.draw(enemy); //NORMAL enemy draw karo

        sf::FloatRect e = enemy.getGlobalBounds(); // enemy bounds

        if (state == 1) // half snow
        {
            sf::CircleShape snow;
            snow.setFillColor(sf::Color(255, 255, 255, 180));
            snow.setRadius(e.width / 3);
            snow.setPosition(e.left, e.top + e.height / 2);
            window.draw(snow);
        }
        else if (state == 2 || state == 3) // full snow
        {
            sf::CircleShape snow;
            snow.setFillColor(sf::Color(255, 255, 255, 220));
            snow.setRadius(e.width / 2);
            snow.setPosition(e.left, e.top);
            window.draw(snow);
        }
        else if (state == 4) // melting
        {
            sf::CircleShape snow;
            float meltPercent = 1.0f - (meltTime / 200.0f);
            snow.setFillColor(sf::Color(255, 255, 255, 150));
            snow.setRadius(e.width / 2 * meltPercent);
            snow.setPosition(e.left, e.top);
            window.draw(snow);
        }
    }
}
