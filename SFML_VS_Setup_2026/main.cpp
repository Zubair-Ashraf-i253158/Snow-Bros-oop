#include <SFML/Graphics.hpp>
#include"Player.h"
#include"Botom.h"
#include"FlyingFooga.h"
#include"Tornado.h"
#include "MOGERA.h"
#include "MogeraBabies.h"
#include "GamaKichi.h"
int main()
{
	
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);
	
    Player player;
    /*
    //ENEMY 1 Botom
    Botom b[5]= { Botom(200, 50), 
                  Botom(300, 50), 
                  Botom(400, 50), 
                  Botom(500, 50), 
                  Botom(600, 50)   };

    //ENEMY 2 FlyingFooga
    FlyingFooga f[2] = { FlyingFooga(150, 100),
                         FlyingFooga(450, 100) };

	//ENEMY 3 Tornado
    Tornado t[2] = { Tornado(250, 100), 
                     Tornado(550, 100) };
    */
    //Boss Mogera
	Mogera m(350, 50);
   //Gama g(350, 50);
 
    //in level one there are 5 enemies we put two to go left
	//and three to go right by default
   
    // b[1].setDirection(-1.0f);  // this one goes left
     //b[2].setDirection(-1.0f);  // this one goes left
    

    
    // Create platforms
    Platform platforms[] = {
    Platform(0, 540, 800, 20),    // ground 
    Platform(0, 420, 220, 15),    // left platform
    Platform(580, 420, 220, 15),  // right platform
    Platform(290, 300, 220, 15),  // middle platform
    Platform(0, 180, 220, 15),    // top left
    Platform(580, 180, 220, 15),  // top right
    };
    int count = 6;
    
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
        for (int i = 0; i < count; i++)
            platforms[i].draw(window);
		window.draw(player);
        /*
        // Enemy display and Calls
        for (int i = 0; i < 5; i++) //BOTOM
        {
            b[i].update(platforms, count);
            b[i].draw(window);
        }
        
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
		m.update(platforms, count, player.getPosition()); //MOGERA
		m.draw(window);

        //g.update(platforms, count);
        //g.draw(window);

        window.display();
    }
}