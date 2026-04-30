#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "AuthSystem.h"

class LoginScreen
{
private:
    sf::Font font;
    sf::Text titleText, userLabel, passLabel;
    sf::Text userInput, passInput;
    sf::Text loginBtn, signupBtn, errorText;
    sf::RectangleShape userBox, passBox;

    std::string username = "";
    std::string password = "";
    bool typingUser = true; // true=username box active
    std::string error = "";

public:
    LoginScreen()
    {
        font.loadFromFile("assets/FONT/font.ttf");

        // title
        titleText.setFont(font);
        titleText.setString("LOGIN");
        titleText.setCharacterSize(50);
        titleText.setFillColor(sf::Color::Cyan);
        titleText.setPosition(330, 80);

        // username box
        userBox.setSize(sf::Vector2f(400, 45));
        userBox.setPosition(200, 200);
        userBox.setFillColor(sf::Color(30, 30, 30));
        userBox.setOutlineColor(sf::Color::White);
        userBox.setOutlineThickness(2);

        userLabel.setFont(font);
        userLabel.setString("Username:");
        userLabel.setCharacterSize(25);
        userLabel.setFillColor(sf::Color::White);
        userLabel.setPosition(200, 170);

        userInput.setFont(font);
        userInput.setCharacterSize(25);
        userInput.setFillColor(sf::Color::White);
        userInput.setPosition(210, 208);

        // password box
        passBox.setSize(sf::Vector2f(400, 45));
        passBox.setPosition(200, 310);
        passBox.setFillColor(sf::Color(30, 30, 30));
        passBox.setOutlineColor(sf::Color::White);
        passBox.setOutlineThickness(2);

        passLabel.setFont(font);
        passLabel.setString("Password:");
        passLabel.setCharacterSize(25);
        passLabel.setFillColor(sf::Color::White);
        passLabel.setPosition(200, 280);

        passInput.setFont(font);
        passInput.setCharacterSize(25);
        passInput.setFillColor(sf::Color::White);
        passInput.setPosition(210, 318);

        // buttons
        loginBtn.setFont(font);
        loginBtn.setString("[ LOGIN ]");
        loginBtn.setCharacterSize(30);
        loginBtn.setFillColor(sf::Color::Green);
        loginBtn.setPosition(250, 400);

        signupBtn.setFont(font);
        signupBtn.setString("[ SIGNUP ]");
        signupBtn.setCharacterSize(30);
        signupBtn.setFillColor(sf::Color::Yellow);
        signupBtn.setPosition(450, 400);

        errorText.setFont(font);
        errorText.setCharacterSize(22);
        errorText.setFillColor(sf::Color::Red);
        errorText.setPosition(200, 460);
    }

    // returns: 0=stay, 3=go to levelselect, 2=go to signup
    int update(sf::Event event, AuthSystem& auth)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f click(event.mouseButton.x, event.mouseButton.y);
            if (userBox.getGlobalBounds().contains(click))  typingUser = true;
            if (passBox.getGlobalBounds().contains(click))  typingUser = false;
            if (loginBtn.getGlobalBounds().contains(click))
            {
                if (auth.login(username, password))
                    return 3; // level select
                else
                    error = "Wrong username or password!";
            }
            if (signupBtn.getGlobalBounds().contains(click))
                return 2; // go to signup
        }

        if (event.type == sf::Event::TextEntered)
        {
            char c = event.text.unicode;
            if (c == 8) // backspace
            {
                if (typingUser && !username.empty()) username.pop_back();
                if (!typingUser && !password.empty()) password.pop_back();
            }
            else if (c >= 32 && c < 127) // normal character
            {
                if (typingUser && username.size() < 20) username += c;
                if (!typingUser && password.size() < 20) password += c;
            }
        }
        return 0;
    }

    void draw(sf::RenderWindow& window)
    {
        window.clear(sf::Color(20, 20, 60));

        // highlight active box
        userBox.setOutlineColor(typingUser ? sf::Color::Cyan : sf::Color::White);
        passBox.setOutlineColor(!typingUser ? sf::Color::Cyan : sf::Color::White);

        userInput.setString(username);
        // show stars for password
        std::string stars(password.size(), '*');
        passInput.setString(stars);
        errorText.setString(error);

        window.draw(titleText);
        window.draw(userBox);
        window.draw(userLabel);
        window.draw(userInput);
        window.draw(passBox);
        window.draw(passLabel);
        window.draw(passInput);
        window.draw(loginBtn);
        window.draw(signupBtn);
        window.draw(errorText);
    }
};