#pragma once
#include <SFML/Graphics.hpp>

class MainMenu
{
private:
    sf::Font font;
    sf::Text title;
    sf::RectangleShape buttons[6];
    sf::Text btnText[6];
    string options[6] = {
        "STORY MODE",
    "MULTIPLAYER",
    "LEVEL SELECT",
    "SHOP",
    "LEADERBOARD",
    "LOGOUT"
    };

public:
    MainMenu()
    {
        font.loadFromFile("assets/FONT/font.ttf");

        title.setFont(font);
        title.setString("SNOW BROS");
        title.setCharacterSize(60);
        title.setFillColor(sf::Color::Cyan);
        title.setPosition(200, 40);

        for (int i = 0; i < 6; i++)
        {
            buttons[i].setSize(sf::Vector2f(400, 55));
            buttons[i].setPosition(200, 150 + i * 80);
            buttons[i].setFillColor(sf::Color(20, 20, 70));
            buttons[i].setOutlineColor(sf::Color::Cyan);
            buttons[i].setOutlineThickness(2);

            btnText[i].setFont(font);
            btnText[i].setString(options[i]);
            btnText[i].setCharacterSize(28);
            btnText[i].setFillColor(sf::Color::White);
            btnText[i].setPosition(230, 162 + i * 80);
        }

        //logout button red
        buttons[4].setOutlineColor(sf::Color::Red);
        btnText[4].setFillColor(sf::Color::Red);
    }

    //0=stay 1=story 2=levelselect 3=shop 4=leaderboard 5=logout
    int update(sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f click(event.mouseButton.x, event.mouseButton.y);
            for (int i = 0; i < 5; i++)
                if (buttons[i].getGlobalBounds().contains(click))
                    return i + 1;
        }
       
        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mouse(event.mouseMove.x, event.mouseMove.y);
            for (int i = 0; i < 5; i++)
            {
                if (buttons[i].getGlobalBounds().contains(mouse))
                    buttons[i].setFillColor(sf::Color(50, 50, 120));
                else
                    buttons[i].setFillColor(sf::Color(20, 20, 70));
            }
        }
        return 0;
    }

    void draw(sf::RenderWindow& window)
    {
        window.clear(sf::Color(10, 10, 40));
        window.draw(title);
        for (int i = 0; i < 5; i++)
        {
            window.draw(buttons[i]);
            window.draw(btnText[i]);
        }
    }
};