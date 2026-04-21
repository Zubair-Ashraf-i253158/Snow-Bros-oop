#include <SFML/Graphics.hpp>
#include"Player.h"
#include"Botom.h"

int main()
{
	
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);
	
    Player player;
    Botom b[5]= { Botom(200, 100), 
                  Botom(300, 100), 
                  Botom(400, 100), 
                  Botom(500, 100), 
                  Botom(600, 100)   };

    //in level one there are 5 enemies we put two to go left
	//and three to go right by default
    b[1].setDirection(-1.0f);  // this one goes left
    b[2].setDirection(-1.0f);  // this one goes left
    
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
		

        window.display();
    }
}