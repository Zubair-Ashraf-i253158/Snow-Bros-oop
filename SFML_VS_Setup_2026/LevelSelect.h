#pragma once
#include <SFML/Graphics.hpp>

class LevelSelect
{
private:
    sf::Font font;
    sf::Text title;
    sf::RectangleShape boxes[10];
    sf::Text numbers[10];
    sf::Text instruction;
    int selectedLevel = 1;

public:
    LevelSelect()
    {
        font.loadFromFile("assets/FONT/font.ttf");

        title.setFont(font);
        title.setString("SELECT LEVEL");
        title.setCharacterSize(50);
        title.setFillColor(sf::Color::Cyan);
        title.setPosition(230, 40);

        instruction.setFont(font);
        instruction.setString("Click a level to start!");
        instruction.setCharacterSize(25);
        instruction.setFillColor(sf::Color::White);
        instruction.setPosition(250, 520);

		//10 level boxes 
        for (int i = 0; i < 10; i++)
        {
            int row = i / 5;
            int col = i % 5;

            boxes[i].setSize(sf::Vector2f(110, 80));
            boxes[i].setPosition(80 + col * 130, 180 + row * 150);
            boxes[i].setFillColor(sf::Color(30, 30, 80));
            boxes[i].setOutlineColor(sf::Color::Cyan);
            boxes[i].setOutlineThickness(2);

            numbers[i].setFont(font);
            numbers[i].setString(std::to_string(i + 1));
            numbers[i].setCharacterSize(35);
            numbers[i].setFillColor(sf::Color::White);
            //box ka center
            numbers[i].setPosition(
                80 + col * 130 + 40,
                180 + row * 150 + 20
            );
        }

        //boss levels  different color
        boxes[4].setFillColor(sf::Color(80, 20, 20)); //level 5
        boxes[9].setFillColor(sf::Color(80, 20, 20)); //level 10
    }

    // returns selected level (1-10), 0 = stay
    int update(sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f click(event.mouseButton.x, event.mouseButton.y);
            for (int i = 0; i < 10; i++)
            {
                if (boxes[i].getGlobalBounds().contains(click))
                    return i + 1; //return level number
            }
        }
        return 0;
    }

    void draw(sf::RenderWindow& window)
    {
        window.clear(sf::Color(10, 10, 40));
        window.draw(title);
        window.draw(instruction);

        for (int i = 0; i < 10; i++)
        {
            window.draw(boxes[i]);
            window.draw(numbers[i]);
        }

        //label boss levels
        sf::Text boss5, boss10;
        boss5.setFont(font);
        boss5.setString("BOSS");
        boss5.setCharacterSize(15);
        boss5.setFillColor(sf::Color::Red);
        boss5.setPosition(608, 245);

        boss10.setFont(font);
        boss10.setString("BOSS");
        boss10.setCharacterSize(15);
        boss10.setFillColor(sf::Color::Red);
        boss10.setPosition(608, 395);

        window.draw(boss5);
        window.draw(boss10);
    }
};
