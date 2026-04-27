#include "LevelSystem.h"
#include "Collision.h"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);

    Player player;
    Level level;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

         // ENEMY ARRAY BANAO
          // hum Enemy* (base class pointer) use kar rahe hain
         // kyunki Botom, FlyingFooga, Tornado sab Enemy se inherit karte hain
         // iska faida ye hai ke ek hi array mein sab enemy types aa jaate hain
         // ye POLYMORPHISM hai 
         //
         // Enemy* matlab mujhe nahi pata ye Botom hai ya Tornado
         // bas itna pata hai ke ye Enemy hai
        
        Enemy* enemies[20]; // max 20 enemies ek waqt mein
        int ecount = 0;     // abhi kitne enemies hain

        // Botom enemies array mein daalo
        // & matlab address do anddd copy mat banao
        for (int i = 0; i < level.getBotomCount(); i++)
            enemies[ecount++] = &level.getBotoms()[i]; 

        // FlyingFooga enemies array mein daalo
        for (int i = 0; i < level.getFoogaCount(); i++)
            enemies[ecount++] = &level.getFoogas()[i];

        // Tornado enemies array mein daalo
        for (int i = 0; i < level.getTornadoCount(); i++)
            enemies[ecount++] = &level.getTornados()[i];
		
        // Invisible enemies array mein daalo
        for (int i = 0; i < level.getInvCount(); i++)
        enemies[ecount++] = &level.getInvisibles()[i];

        // Level 5 par sirf Mogera hai - use bhi daalo
        if (level.getCurrentLevel() == 5)
            enemies[ecount++] = &level.getMogera();

        // Level 10 par sirf Gamakichi hai - use bhi daalo
        if (level.getCurrentLevel() == 10)
            enemies[ecount++] = &level.getGama();

       
        
        // player update mein ye sab hota hai
        // player movement (left right jump)
        // gravity apply hoti hai
        // platform collision check hoti hai
        // snowball throw hoti hai
        // snowball enemy ko hit karta hai
        // player encased enemy ko kick karta hai
        // rolling snowball chain kill karta hai
        // player enemy ko touch kare to life down
        
        player.update(  level.getPlatforms()  , level.getPlatformCount()     ,    enemies   ,       ecount   );

        level.update(player);

        // level complete check
        if (level.isComplete())
            level.nextLevel();

       

        // draw
        window.clear();
        level.draw(window);
        window.draw(player);
       
        window.display();
    }
}