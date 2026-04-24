#include <SFML/Graphics.hpp>
#include"Player.h"
#include"Botom.h"
#include"FlyingFooga.h"
#include"Tornado.h"
#include "MOGERA.h"
#include "MogeraBabies.h"
#include "GamaKichi.h"
#include "Platform.h"
#include "Collision.h"
int main()
{
	
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);
	
    Player player;
   
    //ENEMY 1 Botom
    Botom b[5]= { Botom(200, 50), 
                  Botom(300, 50), 
                  Botom(400, 50), 
                  Botom(500, 50), 
                  Botom(600, 50)   };
    /*
    //ENEMY 2 FlyingFooga
    FlyingFooga f[2] = { FlyingFooga(150, 100),
                         FlyingFooga(450, 100) };
    
	//ENEMY 3 Tornado
    Tornado t[2] = { Tornado(250, 100), 
                     Tornado(550, 100) };
    */
    //Boss Mogera
	//Mogera m(350, 50);
   //Gama g(350, 50);
 
    //in level one there are 5 enemies we put two to go left
	//and three to go right by default
   
     b[1].setDirection(-1.0f);  // this one goes left
     b[2].setDirection(-1.0f);  // this one goes left
    

    sf::Texture bgTexture;
    bgTexture.loadFromFile("assets/Zlevel1.png");
    sf::Sprite background(bgTexture);
    background.setScale( 800.0f / bgTexture.getSize().x , 600.0f / bgTexture.getSize().y); //we resisse the pic according to window size
    // Create platforms
    Platform platforms[] = {
		Platform(0, 524, 800, 10),//round floor
        Platform(0, 450, 190, 10),    // Bottom Left
        Platform(310, 450, 180, 10),  // Bottom Middle
        Platform(610, 450, 190, 10),  // Bottom Right
        Platform(160, 370, 485, 12),//middle row
        Platform(0, 290, 340, 10),   // Upper Left
        Platform(200, 160, 390, 8),  // Upper Middle
        Platform(460, 290, 340, 10),  // Upper Right
        Platform(100, 200, 125, 10),     // Top Left
        Platform(570, 200, 125, 10)    // Top Right
    };

    int count = 10;
    
    while (window.isOpen())
    {
        // Close window
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		player.update(platforms, count);
        
        // Draw
        window.clear();
		window.draw(background);//BACKGROUND
        for (int i = 0; i < count; i++)
        {
            
            platforms[i].draw(window);
        }
		window.draw(player);
        
        // Enemy display and Calls
        for (int i = 0; i < 5; i++) //BOTOM
        {
            b[i].update(platforms, count);
            b[i].draw(window);
        }
        /*
		for (int i = 0; i < 2; i++)  //FOOGA
        {
            f[i].update(platforms, count);
            f[i].draw(window);
        }

        
		for (int i = 0; i < 2; i++) //TORNADO
        {
            t[i].update(platforms, count, player.getPosition());
            t[i].draw(window);
        }
        */
		//m.update(platforms, count, player.getPosition()); //MOGERA
		//m.draw(window);

       // g.update(platforms, count);
       // g.draw(window);



        Collision::BotomCollision(player, b, 5);        // botom collision
        //Collision::FlyingFoogaCollision(player, f, 2);  // fooga collision
        //Collision::TornadoCollision(player, t, 2);      // tornado collision
        
        window.display();
    }
}