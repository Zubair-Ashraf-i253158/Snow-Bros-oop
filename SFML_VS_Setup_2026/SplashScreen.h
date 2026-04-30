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
        title.setFillColor(sf::Color::Cyan);
        title.setCharacterSize(60);          // size kam karo
        title.setPosition(150, 200);         // center mein

        pressKey.setFont(font);
        pressKey.setString("Press Any Key to Start");
        pressKey.setCharacterSize(25);
        pressKey.setFillColor(sf::Color::White);
        pressKey.setPosition(170, 380);      // theek position
    }

    int update(sf::Event& event)  // & lagao - reference
    {
        if (event.type == sf::Event::KeyPressed ||
            event.type == sf::Event::MouseButtonPressed)
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