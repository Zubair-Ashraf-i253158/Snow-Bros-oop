#include <SFML/Graphics.hpp>
#include"Player.h"
#include"Botom.h"
#include"FlyingFooga.h"
#include"Tornado.h"
int main()
{
	
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);
	
    Player player;
    
    //ENEMY 1 Botom
    Botom b[5]= { Botom(200, 100), 
                  Botom(300, 100), 
                  Botom(400, 100), 
                  Botom(500, 100), 
                  Botom(600, 100)   };
	
    //ENEMY 2 FlyingFooga
    FlyingFooga f[2] = { FlyingFooga(150, 100),
                         FlyingFooga(450, 100) };

	//ENEMY 3 Tornado
    Tornado t[2] = { Tornado(250, 100), 
                     Tornado(550, 100) };
    
    //Boss Mogera

    
    //in level one there are 5 enemies we put two to go left
	//and three to go right by default
    b[1].setDirection(-1.0f);  // this one goes left
    b[2].setDirection(-1.0f);  // this one goes left
    Tornado t[2] = { Tornado(250, 100), Tornado(550, 100) };

    
    // Create platforms
    Platform platforms[] = {
        Platform(0, 540, 800, 20),    // ground
        Platform(100, 400, 200, 15),  // mid left
        Platform(500, 300, 200, 15),  // mid right
        Platform(250, 200, 200, 15)   // top middle
    };
    int count = 4;
    
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

        /* Enemy display and Calls*/
        for (int i = 0; i < 5; i++)
        {
            b[i].update(platforms, count);
            b[i].draw(window);
        }
        for (int i = 0; i < 2; i++)
        {
            f[i].update(platforms, count);
            f[i].draw(window);
        }
        for (int i = 0; i < 2; i++)
        {
            t[i].update(platforms, count, player.getPosition());
            t[i].draw(window);
        }
        window.display();
    }
}