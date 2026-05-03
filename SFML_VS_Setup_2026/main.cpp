#include "LevelSystem.h"
#include "Collision.h"
#include "HUD.h"
#include "SplashScreen.h"
#include "LoginScreen.h"
#include "SignupScreen.h"
#include "AuthSystem.h"
#include"LevelSelect.h"
#include "MainMenu.h"
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


    MainMenu mainMenu;
    LevelSelect levelSelect;
    int gameState = 0; // 0=splash 1=login 2=signup 3=main menu 4=level select 5=playing
    while (window.isOpen())
    {
        sf::Event event;
        event.type = sf::Event::Count; // default - koi event nahi

        sf::Event tempEvent;
        while (window.pollEvent(tempEvent))
        {
            if (tempEvent.type == sf::Event::Closed)
                window.close();
            event = tempEvent; // last event save karo
        }

        window.clear();

        if (gameState == 0) // splash
        {
            if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::MouseButtonPressed)
                gameState = 1;
            splash.draw(window);
        }
        else if (gameState == 1) // login
        {
            int result = loginScreen.update(event, auth);
            if (result == 3) gameState = 3; // go to main menu
            if (result == 2) gameState = 2;
            loginScreen.draw(window);
        }
        else if (gameState == 2) // signup
        {
            int result = signupScreen.update(event, auth);
            if (result == 1) gameState = 1;
            signupScreen.draw(window);
        }
        else if (gameState == 3) // main menu
        {
            int result = mainMenu.update(event);
            if (result == 1) // story mode - level 1 se start
            {
                level.loadLevel(1);
                gameState = 5;
            }
            if (result == 2) gameState = 4; // level select
            if (result == 3) { /* shop - baad mein */ }
            if (result == 4) { /* leaderboard - baad mein */ }
            if (result == 5) gameState = 1; // logout - back to login
            mainMenu.draw(window);
        }
        else if (gameState == 4) // level select
        {
            int lvl = levelSelect.update(event);
            if (lvl > 0)
            {
                level.loadLevel(lvl);
                gameState = 5;
            }
            levelSelect.draw(window);
        }
        else if (gameState == 5) // playing
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

       
        
        // player update mein ye sab hota hai
        // player movement (left right jump)
        // gravity apply hoti hai
        // platform collision check hoti hai
        // snowball throw hoti hai
        // snowball enemy ko hit karta hai
        // player encased enemy ko kick karta hai
        // rolling snowball chain kill karta hai
        // player enemy ko touch kare to life down
       
        player.update(  level.getPlatforms()  , level.getPlatformCount()     ,    enemies   ,       ecount   );

        level.update(player);

        // level complete check
        if (level.isComplete())
            level.nextLevel();
       
       //Display hud 
	   //player se score, lives, level and gems ki value leke update karo hud ko
        h.update(player.getScore(), player.getLive(), level.getLevel(), player.getGem());

            level.draw(window);
            h.draw(window);
            window.draw(player);
        }
        window.display();
    }
}