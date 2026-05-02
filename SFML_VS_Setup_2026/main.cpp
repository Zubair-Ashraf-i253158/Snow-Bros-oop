#include "LevelSystem.h"
#include "Collision.h"
#include"HUD.h"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);

    Player player;
    Level level;
    HUD h;
	Player player2; //multiplayer
    bool multiPl = false;
  
    player.setPos(500, 400);      // player 1 position
    player2.setPlayer2(true);     // player 2 keys set karo
    player2.setPos(200, 400);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // M press karo to multiplayer toggle karo
            
        }
        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::M)
            multiPl = !multiPl;
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
        if (multiPl)
            player2.update(level.getPlatforms(), level.getPlatformCount(), enemies, ecount);

        level.update(player);

        // level complete check
        if (level.isComplete())
            level.nextLevel();
       
       //Display hud 
	   //player se score, lives, level and gems ki value leke update karo hud ko
        h.update(player.getScore(), player.getLive(), level.getLevel(), player.getGem(),
            player2.getScore(), player2.getLive(), player2.getGem(), multiPl);

        // draw
        window.clear();
        
		level.draw(window); //level ka draw function background, platforms, enemies sab draw karega
        h.draw(window);   //HUD draw karo
		window.draw(player);  //player draw karo
        if (multiPl)
            window.draw(player2); //player 2 draw karo
        bool p1Dead = player.getDead();
        bool p2Dead = !multiPl || player2.getDead();
        if (p1Dead && p2Dead)
			exit(0); //game over jab dono players mar jaaye to
        window.display();
    }
}