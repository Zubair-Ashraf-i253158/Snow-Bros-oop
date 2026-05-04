#pragma once
#include "Platform.h"
#include "Player.h"
#include "Botom.h"
#include "FlyingFooga.h"
#include "Tornado.h"
#include "MOGERA.h"
#include "MogeraBabies.h"
#include "GamaKichi.h"
#include "Collision.h"
#include "InvisibleEnemy.h"
#include "HUD.h"
#include <SFML/Graphics.hpp>
#include"item.h"
const int maxItems = 50;
//zubair bahi asey banatey hien level ,to bas 4 ghantey me 2 pictures he dal sakhta ha//
// bhai expository ka pura kaam kia ha mana , abhi is ka bhi kr raha
class Level
{
private:
    
	int currentLevel;  // this tell which level is currently active, start from 0 and increase by 1 for each level

    sf::Texture bgTexture;
    sf::Sprite background;

   
    Platform platforms[20];  // ek background ma max 20 platforms ho sakhtey hien
    int platformCount;

    
    Botom b[5];
    int bCount;

    FlyingFooga f[2];
    int fCount;

    Tornado t[2];
    int tCount;

    Invisible inV[5];   // 5 invisible enemies
    int invCount;
	
    Mogera m;
    Gama g; 
    Item items[maxItems]; 
    sf::Texture gemTexture; 
    sf::Texture starTexture;
public:
    
    Level();

    /* Fun For Levels */
    void loadLevel(int levelNum);            // level load karo
    void update(Player& player);             // enemies update karo
    void draw(sf::RenderWindow& window);     // draw karo
    bool isComplete();                       // sare enemies mare?
    void nextLevel();                        // agla level load karo

    // getters 
    Platform* getPlatforms()
    {
        return platforms; 
    }
    int getPlatformCount() 
    {
        return platformCount; 
    }
    int getCurrentLevel() 
    {
        return currentLevel; 
    }

    // getters for collision
    Botom* getBotoms()        // b[] array ka pehla address do
    { return b; }
    
    int getBotomCount()         // kitne botom hain
    { return bCount; }
    
    FlyingFooga* getFoogas()
    { return f; }
    
    int getFoogaCount()
    { return fCount; }
    
    Tornado* getTornados()
    { return t; }
    
    int getTornadoCount() 
    { return tCount; }
    
    Mogera& getMogera()
    { return m; }
    
    Gama& getGama()
    { return g; }
    
    Invisible* getInvisibles() 
    { return inV; }
    
    int getInvCount() 
    { return invCount; }
   
    //for items
    Item* getItems() { return items; }
    int getMaxItems() { return maxItems; }
    void spawnItem(float x, float y, ItemType type) {
        for (int i = 0; i < maxItems; i++) {
            if (!items[i].active) {
                if (type == GEM) {
                    items[i].sprite.setScale(
                        60.0f / gemTexture.getSize().x,
                        64.0f / gemTexture.getSize().y
                    );
                    items[i].spawn(x, y, GEM, gemTexture);
                }
                else if (type == STAR) {
                    items[i].sprite.setScale(
                        60.0f / starTexture.getSize().x,
                        64.0f / starTexture.getSize().y
                    );
                    items[i].spawn(x, y, STAR, starTexture);
                }
                break; 
            }
        }
    }
    void drawItems(sf::RenderWindow& window) {
        for (int i = 0; i < maxItems; i++) {
            if (items[i].active) {
                window.draw(items[i].sprite);
            }
        }
	}

    //HUD GETTER FOR LEVEL

    int getLevel() const
    {
        return currentLevel; // current level do
    }

};
