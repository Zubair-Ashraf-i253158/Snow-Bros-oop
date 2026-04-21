#include <SFML/Graphics.hpp>
#include"Player.h"

int main()
{
	
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);
	
    Player player;
    
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
        window.display();
    }
}