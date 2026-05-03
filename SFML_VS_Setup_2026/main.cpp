#include "LevelSystem.h"
#include "Collision.h"
#include "HUD.h"
#include "SplashScreen.h"
#include "LoginScreen.h"
#include "SignupScreen.h"
#include "AuthSystem.h"
#include "LevelSelect.h"
#include "MainMenu.h"
#include "Leaderboard.h"
#include "Shop.h"
#include "Player.h"
#include"item.h"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);

    Player player;
    Player player2;
    Level level;
    HUD h;
    SplashScreen splash;
    LoginScreen loginScreen;
    SignupScreen signupScreen;
    AuthSystem auth;
    MainMenu mainMenu;
    Shop shop;
    LevelSelect levelSelect;
    Leaderboard leaderboard;
    bool multiPl = false;
    bool paused = false;
    Item* items = level.getItems();
    int maxItems = level.getMaxItems();
    player.setPos(500, 400);
    player2.setPlayer2(true);
    player2.setPos(200, 400);

    // 0=splash 1=login 2=signup 3=mainmenu
    // 4=levelselect 5=playing 6=leaderboard
    int gameState = 0;

    while (window.isOpen())
    {
        sf::Event event;
        event.type = sf::Event::Count;

        sf::Event tempEvent;
        while (window.pollEvent(tempEvent))
        {
            if (tempEvent.type == sf::Event::Closed)
                window.close();
            event = tempEvent;
        }

        window.clear();

        if (gameState == 0) //splash
        {
            if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::MouseButtonPressed)
                gameState = 1;
            splash.draw(window);
        }
        else if (gameState == 1) //login
        {
            int result = loginScreen.update(event, auth);
            if (result == 3) gameState = 3;
            if (result == 2) gameState = 2;
            loginScreen.draw(window);
        }
        else if (gameState == 2) //signup
        {
            int result = signupScreen.update(event, auth);
            if (result == 1) gameState = 1;
            signupScreen.draw(window);
        }
        else if (gameState == 3) //main menu
        {
            int result = mainMenu.update(event);
            if (result == 1) //story yani start
            {
                multiPl = false;
                player = Player();
                player.setPos(500, 400);
                level.loadLevel(1);
                gameState = 5;
            }
            if (result == 2) //multiplayer
            {
                multiPl = true;
                player = Player();
                player2 = Player();
                player.setPos(500, 400);
                player2.setPlayer2(true);
                player2.setPos(200, 400);
                level.loadLevel(1);
                gameState = 5;
            }
            if (result == 3) gameState = 4; //level select
            if (result == 4) 
            {
                int result = shop.update(event, player);
                if (result == 3) {
                    gameState = 3; //main menu
                }
                shop.draw(window);
            }
            if (result == 5) gameState = 6; // leaderboard
            if (result == 6) gameState = 1; // logout
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
            //escape

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
                paused = !paused;


            if (!paused)
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

                //alive 
                bool botomAlive[5] = {}, foogaAlive[2] = {},
                    tornadoAlive[2] = {}, invAlive[5] = {};
                bool mogeraAlive = false, gamaAlive = false;

                for (int i = 0; i < level.getBotomCount(); i++)
                    botomAlive[i] = level.getBotoms()[i].getZinda();
                for (int i = 0; i < level.getFoogaCount(); i++)
                    foogaAlive[i] = level.getFoogas()[i].getZinda();
                for (int i = 0; i < level.getTornadoCount(); i++)
                    tornadoAlive[i] = level.getTornados()[i].getZinda();
                for (int i = 0; i < level.getInvCount(); i++)
                    invAlive[i] = level.getInvisibles()[i].getZinda();
                if (level.getCurrentLevel() == 5)
                    mogeraAlive = level.getMogera().getZinda();
                if (level.getCurrentLevel() == 10)
                    gamaAlive = level.getGama().getZinda();

                for (int i = 0; i < maxItems; i++) {
                    // Player 1 Collision
                    if (items[i].active && player.getBounds().intersects(items[i].getBounds())) {
                        items[i].active = false; //Hide item
                        if (items[i].type == GEM) {
                            player.addScore(100);
                            player.addGem(1);
                        }
                        else if (items[i].type == STAR) {
                            player.applyPowerUp();
                        }
                    }
                    if (multiPl && items[i].active && player2.getBounds().intersects(items[i].getBounds())) {
                        items[i].active = false; //Hide item
                        if (items[i].type == GEM) {
                            player2.addScore(100);
                            player2.addGem(1);
                        }
                        else if (items[i].type == STAR) {
                            player2.applyPowerUp();
                        }
                    }
                //update
                        // player update mein ye sab hota hai
        // player movement (left right jump)
        // gravity apply hoti hai
        // platform collision check hoti hai
        // snowball throw hoti hai
        // snowball enemy ko hit karta hai
        // player encased enemy ko kick karta hai
        // rolling snowball chain kill karta hai
        // player enemy ko touch kare to life down
        //hover effect
                player.update(level.getPlatforms(), level.getPlatformCount(), enemies, ecount);
                if (multiPl)
                    player2.update(level.getPlatforms(), level.getPlatformCount(), enemies, ecount);

                level.update(player);

                //score
                for (int i = 0; i < level.getBotomCount(); i++)
                    if (botomAlive[i] && !level.getBotoms()[i].getZinda())
                    {
                        int p = 100 + rand() % 401; player.addScore(p);
                        if (multiPl) player2.addScore(p);
                        //item drop ho jaia
                        float dropX = level.getBotoms()[i].getBounds().left;
                        float dropY = level.getBotoms()[i].getBounds().top;

                        if (level.getBotoms()[i].isChainKilled())
                        {
                            level.spawnItem(dropX, dropY, STAR); //drop
                        }
						//star 20% chance se drop hoga
                        if (rand() % 100 < 20) {
                            level.spawnItem(dropX, dropY, STAR);
                        }
						
                    }

                for (int i = 0; i < level.getFoogaCount(); i++)
                    if (foogaAlive[i] && !level.getFoogas()[i].getZinda())
                    {
                        int p = 200 + rand() % 601; player.addScore(p); 
                        if (multiPl) player2.addScore(p);
                        float dropX = level.getFoogas()[i].getBounds().left;
                        float dropY = level.getFoogas()[i].getBounds().top;

                        if (level.getFoogas()[i].isChainKilled())
                        {
                            level.spawnItem(dropX, dropY, STAR); //drop
                        }
                        //star 20% chance se drop hoga
                        if (rand() % 100 < 20) {
                            level.spawnItem(dropX, dropY, STAR);
                        }
                    }

                for (int i = 0; i < level.getTornadoCount(); i++)
                    if (tornadoAlive[i] && !level.getTornados()[i].getZinda())
                    {
                        int p = 300 + rand() % 901; player.addScore(p); 
                        if (multiPl) player2.addScore(p);
                        float dropX = level.getTornados()[i].getBounds().left;
                        float dropY = level.getTornados()[i].getBounds().top;

                        if (level.getTornados()[i].isChainKilled())
                        {
                            level.spawnItem(dropX, dropY, STAR); //drop
                        }
                        //star 20% chance se drop hoga
                        if (rand() % 100 < 20) {
                            level.spawnItem(dropX, dropY, STAR);
                        }
                    }

                for (int i = 0; i < level.getInvCount(); i++)
                    if (invAlive[i] && !level.getInvisibles()[i].getZinda())
                    {
                        int p = 500 + rand() % 1001; player.addScore(p);
                        if (multiPl) player2.addScore(p);
                         float dropX = level.getInvisibles()[i].getBounds().left;
                        float dropY = level.getInvisibles()[i].getBounds().top;

                        if (level.getInvisibles()[i].isChainKilled())
                        {
                            level.spawnItem(dropX, dropY, STAR); //drop
                        }
                        //star 20% chance se drop hoga
                        if (rand() % 100 < 20) {
                            level.spawnItem(dropX, dropY, STAR);
                        }
                    }

                if (level.getCurrentLevel() == 5 && mogeraAlive && !level.getMogera().getZinda())
                {
                    player.addScore(5000); if (multiPl) player2.addScore(5000);
                }

                if (level.getCurrentLevel() == 10 && gamaAlive && !level.getGama().getZinda())
                {
                    player.addScore(10000); if (multiPl) player2.addScore(10000);
                }

                // real time leaderboard update
                leaderboard.updateScore(auth.getUser(), player.getScore());

                if (level.isComplete()) level.nextLevel();

                h.update(player.getScore(), player.getLive(), level.getLevel(), player.getGem(),
                    player2.getScore(), player2.getLive(), player2.getGem(), multiPl);

                level.draw(window);
                h.draw(window);
                window.draw(player);
                if (multiPl) window.draw(player2);

                // game over check
                bool p1Dead = player.getDead();
                bool p2Dead = !multiPl || player2.getDead();
                if (p1Dead && p2Dead)
                {
                    //save progress and go to main menu
                  
                        level.getCurrentLevel(),
                        player.getScore(),
                        player.getGem(),
                        player.getLive();
                    gameState = 3;
                }
            }
            else //paused
            {
                level.draw(window);
                h.draw(window);
                window.draw(player);
                if (multiPl) window.draw(player2);

                // pause overlay
                sf::RectangleShape overlay(sf::Vector2f(400, 300));
                overlay.setPosition(200, 150);
                overlay.setFillColor(sf::Color(0, 0, 0, 180));
                window.draw(overlay);

                //simple pause text
                sf::Font font;
                font.loadFromFile("assets/font.ttf");
                sf::Text pauseText("PAUSED - Press ESC to continue", font, 25);
                pauseText.setPosition(210, 280);
                pauseText.setFillColor(sf::Color::Cyan);
                window.draw(pauseText);

                sf::Text menuText("Press M to go to Main Menu", font, 22);
                menuText.setPosition(230, 330);
                menuText.setFillColor(sf::Color::Yellow);
                window.draw(menuText);

                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::M)
                {
                   
                        level.getCurrentLevel(),
                        player.getScore(),
                        player.getGem(),
                        player.getLive();
                    paused = false;
                    gameState = 3;
                }
            }
        }
        else if (gameState == 6) //leaderboard
        {
            int result = leaderboard.update(event);
            if (result == 1) gameState = 3;
            leaderboard.draw(window);
        }

        window.display();
    }
}