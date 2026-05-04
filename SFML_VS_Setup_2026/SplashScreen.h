#pragma once
#include <SFML/Graphics.hpp>

class SplashScreen
{
private:
    sf::Text pressKey;
    float timer = 0;
	sf::Texture bannerTexture;
	sf::Sprite banner;
public:
    SplashScreen()
    {
		bannerTexture.loadFromFile("assets/banner.png");
		banner.setTexture(bannerTexture);
        banner.setScale(
            800.0f / bannerTexture.getSize().x,
            600.0f / bannerTexture.getSize().y
        );
       
    }

    int update(sf::Event& event)  //press any key ka lia
    {
        if (event.type == sf::Event::KeyPressed ||
            event.type == sf::Event::MouseButtonPressed)
            return 1;
        return 0;
    }

    void draw(sf::RenderWindow& window)
    {
		window.draw(banner);
        
    }
};