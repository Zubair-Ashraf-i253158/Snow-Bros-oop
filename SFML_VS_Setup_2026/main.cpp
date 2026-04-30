#include "LevelSystem.h"
#include "Collision.h"
#include "HUD.h"
#include "SplashScreen.h"
#include "LoginScreen.h"
#include "SignupScreen.h"
#include "AuthSystem.h"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);

    Player player;
    Level level;
    HUD h;
    SplashScreen splash;
    LoginScreen loginScreen;
    SignupScreen signupScreen;
    AuthSystem auth;

    int gameState = 0; // 0=splash 1=login 2=signup 3=playing
        while (window.isOpen())
        {
            sf::Event event;
            bool hasEvent = false;

            while (window.pollEvent(event))
            {
                hasEvent = true;
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();

            if (gameState == 0) // splash
            {
                if (hasEvent && splash.update(event) == 1)
                    gameState = 1;
                splash.draw(window);
            }
            else if (gameState == 1) // login
            {
                if (hasEvent)
                {
                    int result = loginScreen.update(event, auth);
                    if (result == 3) gameState = 3;
                    if (result == 2) gameState = 2;
                }
                loginScreen.draw(window);
            }
            else if (gameState == 2) // signup
            {
                if (hasEvent)
                {
                    int result = signupScreen.update(event, auth);
                    if (result == 1) gameState = 1;
                }
                signupScreen.draw(window);
            }
        else if (gameState == 3) // playing
        {
            Enemy* enemies[20];
            int ecount = 0;
            for (int i = 0; i < level.getBotomCount(); i++)
                enemies[ecount++] = &level.getBotoms()[i];
            for (int i = 0; i < level.getFoogaCount(); i++)
                enemies[ecount++] = &level.getFoogas()[i];
            for (int i = 0; i < level.getTornadoCount(); i++)
                enemies[ecount++] = &level.getTornados()[i];
            for (int i = 0; i < level.getInvCount(); i++)
                enemies[ecount++] = &level.getInvisibles()[i];
            if (level.getCurrentLevel() == 5)
                enemies[ecount++] = &level.getMogera();
            if (level.getCurrentLevel() == 10)
                enemies[ecount++] = &level.getGama();

            player.update(level.getPlatforms(), level.getPlatformCount(), enemies, ecount);
            level.update(player);
            if (level.isComplete()) level.nextLevel();
            h.update(player.getScore(), player.getLive(), level.getLevel(), player.getGem());

            level.draw(window);
            h.draw(window);
            window.draw(player);
        }

        window.display();
    }
}