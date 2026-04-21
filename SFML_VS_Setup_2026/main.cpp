#include <SFML/Graphics.hpp>
#include"Player.h"

int main()
{
	
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);
	
    Player player;

    
    while (window.isOpen())
    {
        // Close window
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		player.update();
        
        // Draw
        window.clear();
		
		window.draw(player);
        window.display();
    }
}