#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Shop {
private:
    sf::Font font;
    sf::Text titleText;
	sf::Text item1Text; //extra life
	sf::Text item2Text; //power up
    sf::Text exitText;
    sf::Text gemDisplay;
    int selectedItem = 1;

public:
    Shop() {
        font.loadFromFile("assets/FONT/font.ttf");

        titleText.setFont(font);
        titleText.setString("SHOP");
        titleText.setCharacterSize(40);
        titleText.setPosition(350, 50);

        item1Text.setFont(font);
        item1Text.setString("1. Buy Extra Life (50 Gems)");
        item1Text.setPosition(250, 200);

        item2Text.setFont(font);
        item2Text.setString("2. Speed Boots (30 Gems)");
        item2Text.setPosition(250, 300);

        exitText.setFont(font);
        exitText.setString("Press ESC to Return to Menu");
        exitText.setPosition(250, 500);

        gemDisplay.setFont(font);
        gemDisplay.setPosition(50, 50);
    }

    //Returns 0 to stay in shop, 3 to go back to main menu
    int update(sf::Event& event, Player& p1) {
        gemDisplay.setString("Gems: " + std::to_string(p1.getGem()));

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                return 3; //main meny
            }
            if (event.key.code == sf::Keyboard::Num1) {
                if (p1.getGem() >= 50) {
                    p1.addGem(-50); 
                    p1.addLive(1);  
                }
            }
            if (event.key.code == sf::Keyboard::Num2) {
                if (p1.getGem() >= 30) {
                    p1.addGem(-30);
                    p1.applyPowerUp();
                }
            }
        }
        return 0; 
    }

    void draw(sf::RenderWindow& window) {
        window.draw(titleText);
        window.draw(item1Text);
        window.draw(item2Text);
        window.draw(exitText);
        window.draw(gemDisplay);
    }
};