#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "AuthSystem.h"

class SignupScreen
{
private:
    sf::Font font;
    sf::Text titleText, userLabel, passLabel;
    sf::Text userInput, passInput;
    sf::Text signupBtn, backBtn, errorText, successText;
    sf::RectangleShape userBox, passBox;
    std::string username = "";
    std::string password = "";
    bool typingUser = true;
    std::string error = "";

public:
    SignupScreen()
    {
        font.loadFromFile("assets/FONT/font.ttf");

        titleText.setFont(font);
        titleText.setString("SIGNUP");
        titleText.setCharacterSize(50);
        titleText.setFillColor(sf::Color::Cyan);
        titleText.setPosition(310, 80);

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

        signupBtn.setFont(font);
        signupBtn.setString("[ CREATE ACCOUNT ]");
        signupBtn.setCharacterSize(28);
        signupBtn.setFillColor(sf::Color::Green);
        signupBtn.setPosition(220, 400);

        backBtn.setFont(font);
        backBtn.setString("[ BACK TO LOGIN ]");
        backBtn.setCharacterSize(25);
        backBtn.setFillColor(sf::Color::Yellow);
        backBtn.setPosition(230, 450);

        errorText.setFont(font);
        errorText.setCharacterSize(22);
        errorText.setFillColor(sf::Color::Red);
        errorText.setPosition(200, 510);
    }

    // returns: 0=stay, 1=go to login
    int update(sf::Event event, AuthSystem& auth)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f click(event.mouseButton.x, event.mouseButton.y);
            if (userBox.getGlobalBounds().contains(click))  typingUser = true;
            if (passBox.getGlobalBounds().contains(click))  typingUser = false;
            if (signupBtn.getGlobalBounds().contains(click))
            {
                if (username.empty() || password.empty())
                    error = "Fields cant be empty";
                else if (auth.signup(username, password))
                    return 1; //go to login
                else
                    error = "Username taken!";
            }
            if (backBtn.getGlobalBounds().contains(click))
                return 1; //back to login
        }

        if (event.type == sf::Event::TextEntered)
        {
            char c = event.text.unicode;
            if (c == 8)
            {
                if (typingUser && !username.empty()) username.pop_back();
                if (!typingUser && !password.empty()) password.pop_back();
            }
            else if (c >= 32 && c < 127)
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
        userBox.setOutlineColor(typingUser ? sf::Color::Cyan : sf::Color::White);
        passBox.setOutlineColor(!typingUser ? sf::Color::Cyan : sf::Color::White);
        userInput.setString(username);
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
        window.draw(signupBtn);
        window.draw(backBtn);
        window.draw(errorText);
    }
};