#pragma once
#include <SFML/Graphics.hpp>

class SplashScreen
{
private:
    sf::Texture bgTexture;
    sf::Sprite bg;
    sf::Font font;
    sf::Text title;
    sf::Text pressKey;
    float timer = 0;

public:
    SplashScreen()
    {
        font.loadFromFile("assets/FONT/font.ttf");

        title.setFont(font);
        title.setString("SNOW BROS");
        title.setCharacterSize(80);
        title.setFillColor(sf::Color::Cyan);
        title.setPosition(180, 180);

        pressKey.setFont(font);
        pressKey.setString("Press Any Key to Start");
        pressKey.setCharacterSize(30);
        pressKey.setFillColor(sf::Color::White);
        pressKey.setPosition(220, 400);
    }

    int update(sf::Event event) // returns 1 if should go to login
    {
        if (event.type == sf::Event::KeyPressed)
            return 1;
        return 0;
    }

    void draw(sf::RenderWindow& window)
    {
        window.clear(sf::Color(20, 20, 80));
        window.draw(title);
        window.draw(pressKey);
    }
};