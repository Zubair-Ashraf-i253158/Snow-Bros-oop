#include "LevelSystem.h"
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
#include <SFML/Graphics.hpp>

Level::Level() : m(0.0, 0.0), g(0.0, 0.0)  // boss default position
{
    currentLevel = 1;
    bCount = 0;
    fCount = 0;
    tCount = 0;

    platformCount = 0;
    loadLevel(1); // level 1 se shuru karo
}


// now ab her level ko uski properties ke saath load karna hai, jaise background, platforms, enemies

void Level::loadLevel(int levelNum)
{
    currentLevel = levelNum;
    bCount = 0;
    fCount = 0;
    tCount = 0;
    invCount = 0;
    platformCount = 0;

    //LEVEL 1 
    //Sirf Botom enemies

    if (levelNum == 1)
    {
        //background load karo
        bgTexture.loadFromFile("assets/lvl1.png");
        background.setTexture(bgTexture);
        background.setScale(
            800.0f / bgTexture.getSize().x,
            600.0f / bgTexture.getSize().y
        );

        //platforms set karo
        platformCount = 10;
        platforms[0] = Platform(0, 524, 800, 10);    //ground floor
        platforms[1] = Platform(0, 450, 190, 10);    //bottom left
        platforms[2] = Platform(320, 450, 180, 10);  //bottom middle
        platforms[3] = Platform(620, 450, 180, 10);  //bottom right
        platforms[4] = Platform(160, 370, 485, 12);  //middle row
        platforms[5] = Platform(0, 290, 340, 10);    //upper left
        platforms[6] = Platform(200, 160, 390, 8);   //upper middle
        platforms[7] = Platform(460, 290, 340, 10);  //upper right
        platforms[8] = Platform(100, 200, 125, 10);  //top left
        platforms[9] = Platform(570, 200, 125, 10);  //top right

        //enemies set karo
        bCount = 5;
        
        b[0] = Botom(50,450);
        b[1] = Botom(50, 400);
        b[2] = Botom(700, 400);
        b[3] = Botom(500, 300);
        b[4] = Botom(600, 50);
       
        b[1].setdirection(-1.0f); //left
        b[2].setdirection(-1.0f); //left

    }


    //LEVEL 2 
    //Botom and FlyingFooga

    else if (levelNum == 2)
    {
        bgTexture.loadFromFile("assets/level2.png");
        background.setTexture(bgTexture);
        background.setScale(
            800.0f / bgTexture.getSize().x,
            600.0f / bgTexture.getSize().y
        );

        platformCount = 9;


        platforms[0] = Platform(0, 569, 800, 10);
        platforms[1] = Platform(100, 483, 247, 10);    //bottom left
        platforms[2] = Platform(460, 483, 243, 10);  //bottom right
        platforms[3] = Platform(0, 397, 347, 10);    //mid left
        platforms[4] = Platform(455, 399, 350, 10);  //mid right
        platforms[5] = Platform(150, 310, 47, 10);    //upper left
        platforms[6] = Platform(354, 310, 307, 10);  //upper long
        platforms[7] = Platform(106, 223, 436, 10);   //top left
        platforms[8] = Platform(255, 137, 437, 10); //top right
        //enemies

        bCount = 3;             //BOTOM
        b[0] = Botom(100, 50);
        b[1] = Botom(400, 50);
        b[2] = Botom(600, 50);
        b[1].setdirection(-1.0f);

        fCount = 2;             //FLY FOOGA
        f[0] = FlyingFooga(200, 50);
        f[1] = FlyingFooga(500, 50);
        f[1].setdirection(-1.0f);
    }


    //LEVEL 3
    //Botom , FlyingFooga and Tornado

    else if (levelNum == 3)
    {
        bgTexture.loadFromFile("assets/level 3.png");
        background.setTexture(bgTexture);
        background.setScale(
            800.0f / bgTexture.getSize().x,
            600.0f / bgTexture.getSize().y
        );



        platformCount = 11;

        //ground
        platforms[0] = Platform(0, 567, 800, 10);
        platforms[1] = Platform(210, 490, 387, 10);
        platforms[2] = Platform(0, 400, 110, 10);
        platforms[3] = Platform(0, 310, 110, 10);
        platforms[4] = Platform(700, 400, 130, 10);
        platforms[5] = Platform(700, 310, 130, 10);
        platforms[6] = Platform(215, 310, 140, 10);
        platforms[7] = Platform(455, 310, 140, 10);
        platforms[8] = Platform(0, 225, 205, 10);
        platforms[9] = Platform(600, 225, 210, 10);
        platforms[10] = Platform(167, 140, 470, 10);

        bCount = 2;
        b[0] = Botom(100, 50);
        b[1] = Botom(400, 50);
        b[1].setdirection(-1.0f);

        fCount = 2;
        f[0] = FlyingFooga(200, 50);
        f[1] = FlyingFooga(500, 50);

        tCount = 2;
        t[0] = Tornado(300, 50);
        t[1] = Tornado(600, 50);
        t[1].setdirection(-1.0f);
    }


    //LEVEL 4
    //Special enemy

    else if (levelNum == 4)
    {
        bgTexture.loadFromFile("assets/Zlevel4.png");
        background.setTexture(bgTexture);
        background.setScale(
            800.0f / bgTexture.getSize().x,
            600.0f / bgTexture.getSize().y
        );

        platformCount = 10;
        platforms[0] = Platform(0, 524, 800, 10);
        platforms[1] = Platform(0, 430, 130, 10);
        platforms[2] = Platform(670, 430, 130, 10);
        platforms[3] = Platform(300, 400, 200, 10);
        platforms[4] = Platform(130, 330, 180, 10);
        platforms[5] = Platform(490, 330, 180, 10);
        platforms[6] = Platform(300, 260, 200, 10);
        platforms[7] = Platform(0, 190, 150, 10);
        platforms[8] = Platform(650, 190, 150, 10);
        platforms[9] = Platform(300, 120, 200, 10);


        //CUSTOMIZED ENEMy
        invCount = 2;

        inV[0] = Invisible(150, 50);
        inV[1] = Invisible(350, 50);


    }


    //LEVEL 5
    //Boss Mogera

    else if (levelNum == 5)
    {
        bgTexture.loadFromFile("assets/Level5.png");
        background.setTexture(bgTexture);
        background.setScale(
            800.0f / bgTexture.getSize().x,
            600.0f / bgTexture.getSize().y
        );

        // open platforms for boss fight
        platformCount = 6;
        platforms[0] = Platform(0, 560, 800, 10);

        platforms[1] = Platform(0, 500, 380, 10);

        platforms[2] = Platform(420, 440, 380, 10);

        platforms[3] = Platform(0, 380, 500, 10);

        platforms[4] = Platform(300, 320, 500, 10);

        platforms[5] = Platform(0, 260, 400, 10);

        // sirf mogera hai
       
        m = Mogera(360,150);
        
    }


    // LEVEL 6 
    // Green Color Variants


    else if (levelNum == 6)
    {

        bgTexture.loadFromFile("assets/Zlevel6.png");
        background.setTexture(bgTexture);
        background.setScale(
            800.0f / bgTexture.getSize().x,
            600.0f / bgTexture.getSize().y
        );

        platformCount = 10;
        platforms[0] = Platform(0, 524, 800, 10);
        platforms[1] = Platform(0, 450, 190, 10);
        platforms[2] = Platform(320, 450, 180, 10);
        platforms[3] = Platform(620, 450, 180, 10);
        platforms[4] = Platform(160, 370, 485, 12);
        platforms[5] = Platform(0, 290, 340, 10);
        platforms[6] = Platform(200, 160, 390, 8);
        platforms[7] = Platform(460, 290, 340, 10);
        platforms[8] = Platform(100, 200, 125, 10);
        platforms[9] = Platform(570, 200, 125, 10);

        //Green variants 
        //faster speed

        bCount = 2;
        b[0] = Botom(200, 50);
        b[1] = Botom(300, 50);
        b[2] = Botom(400, 50);
        b[3] = Botom(500, 50);
        b[4] = Botom(600, 50);
        b[1].setdirection(-1.0f);

        for (int i = 0; i < bCount; i++)
        {
            b[i].setSpeed(3.0f * 1.25f);  //1.25x faster
            b[i].setHealth(3.0f);          //+1 hit to encase
            // b[i].setColor(sf::Color::Green); //green colour
        }

        fCount = 2;
        f[0] = FlyingFooga(200, 50);
        f[1] = FlyingFooga(500, 50);
        for (int i = 0; i < fCount; i++)
        {
            f[i].setSpeed(2.0f * 1.25f);
            f[i].setHealth(3.0f);
            // f[i].setColor(sf::Color::Green);   //Zubair idr error a raaha kiu ka sprite ka shyd setColor nahi hota
                                                // jab hitbox wala system ho ga to phr if else laga de ga sprite and box
        }

        tCount = 2;
        t[0] = Tornado(300, 50);
        t[1] = Tornado(500, 50);
        for (int i = 0; i < tCount; i++)
        {
            t[i].setSpeed(2.0f * 1.25f);
            t[i].setHealth(4.0f);
            // t[i].setColor(sf::Color::Green);
        }
    }


    //LEVEL 7
    //Blue Color Variants

    else if (levelNum == 7)
    {
        bgTexture.loadFromFile("assets/Zlevel7.png");
        background.setTexture(bgTexture);
        background.setScale(
            800.0f / bgTexture.getSize().x,
            600.0f / bgTexture.getSize().y
        );

        platformCount = 10;
        platforms[0] = Platform(0, 524, 800, 10);
        platforms[1] = Platform(100, 440, 150, 10);
        platforms[2] = Platform(550, 440, 150, 10);
        platforms[3] = Platform(300, 380, 200, 10);
        platforms[4] = Platform(0, 300, 200, 10);
        platforms[5] = Platform(600, 300, 200, 10);
        platforms[6] = Platform(250, 240, 300, 10);
        platforms[7] = Platform(0, 160, 150, 10);
        platforms[8] = Platform(650, 160, 150, 10);
        platforms[9] = Platform(300, 100, 200, 10);

        bCount = 5;
        b[0] = Botom(100, 50);
        b[1] = Botom(300, 50);
        b[1].setdirection(-1.0f);

        for (int i = 0; i < bCount; i++)
        {
            b[i].setSpeed(3.0f * 1.5f);   //1.5x faster
            b[i].setHealth(4.0f);          //+2 hits
            // b[i].setColor(sf::Color::Blue);
        }

        fCount = 2;
        f[0] = FlyingFooga(200, 50);
        f[1] = FlyingFooga(600, 50);
        for (int i = 0; i < fCount; i++)
        {
            f[i].setSpeed(2.0f * 1.5f);
            f[i].setHealth(4.0f);
            // f[i].setColor(sf::Color::Blue);
        }

        tCount = 2;
        t[0] = Tornado(300, 50);
        t[1] = Tornado(500, 50);
        for (int i = 0; i < tCount; i++)
        {
            t[i].setSpeed(2.0f * 1.5f);
            t[i].setHealth(5.0f);
            //  t[i].setColor(sf::Color::Blue);
        }
    }


    //LEVEL 8
    //Purple Color Variants

    else if (levelNum == 8)
    {
        bgTexture.loadFromFile("assets/Zlevel8.png");
        background.setTexture(bgTexture);
        background.setScale(
            800.0f / bgTexture.getSize().x,
            600.0f / bgTexture.getSize().y
        );

        platformCount = 10;
        platforms[0] = Platform(0, 524, 800, 10);
        platforms[1] = Platform(0, 440, 160, 10);
        platforms[2] = Platform(640, 440, 160, 10);
        platforms[3] = Platform(280, 400, 240, 10);
        platforms[4] = Platform(100, 320, 200, 10);
        platforms[5] = Platform(500, 320, 200, 10);
        platforms[6] = Platform(280, 240, 240, 10);
        platforms[7] = Platform(0, 160, 180, 10);
        platforms[8] = Platform(620, 160, 180, 10);
        platforms[9] = Platform(280, 80, 240, 10);

        bCount = 5;
        b[0] = Botom(100, 50);
        b[1] = Botom(250, 50);
        b[2] = Botom(400, 50);
        b[3] = Botom(600, 50);
        b[4] = Botom(700, 50);
        b[1].setdirection(-1.0f);

        for (int i = 0; i < bCount; i++)
        {
            b[i].setSpeed(3.0f * 1.75f);      //1.75x faster
            b[i].setHealth(5.0f);              //+3 hits
            // b[i].setColor(sf::Color(128, 0, 128)); //purple
        }

        fCount = 2;
        f[0] = FlyingFooga(200, 50);
        f[1] = FlyingFooga(600, 50);
        for (int i = 0; i < fCount; i++)
        {
            f[i].setSpeed(2.0f * 1.75f);
            f[i].setHealth(5.0f);
            // f[i].setColor(sf::Color(128, 0, 128));
        }

        tCount = 2;
        t[0] = Tornado(300, 50);
        t[1] = Tornado(500, 50);
        for (int i = 0; i < tCount; i++)
        {
            t[i].setSpeed(2.0f * 1.75f);
            t[i].setHealth(6.0f);
            // t[i].setColor(sf::Color(128, 0, 128));
        }
    }


    //LEVEL 9 
    //All Variants Mixed

    else if (levelNum == 9)
    {
        bgTexture.loadFromFile("assets/Zlevel9.png");
        background.setTexture(bgTexture);
        background.setScale(
            800.0f / bgTexture.getSize().x,
            600.0f / bgTexture.getSize().y
        );

        platformCount = 10;
        platforms[0] = Platform(0, 524, 800, 10);
        platforms[1] = Platform(0, 430, 130, 10);
        platforms[2] = Platform(670, 430, 130, 10);
        platforms[3] = Platform(300, 400, 200, 10);
        platforms[4] = Platform(130, 330, 180, 10);
        platforms[5] = Platform(490, 330, 180, 10);
        platforms[6] = Platform(300, 260, 200, 10);
        platforms[7] = Platform(0, 190, 150, 10);
        platforms[8] = Platform(650, 190, 150, 10);
        platforms[9] = Platform(300, 120, 200, 10);

        bCount = 5;
        b[0] = Botom(100, 50);
        b[1] = Botom(250, 50);
        b[1].setdirection(-1.0f);


        //faster speed
        for (int i = 0; i < bCount; i++)
            b[i].setSpeed(4.0f);

        fCount = 2;
        f[0] = FlyingFooga(200, 50);
        f[1] = FlyingFooga(600, 50);
        f[1].setdirection(-1.0f);

        tCount = 2;
        t[0] = Tornado(300, 50);
        t[1] = Tornado(500, 50);

    }


    //LEVEL 10 
    //Boss Gamakichi

    else if (levelNum == 10)
    {
        bgTexture.loadFromFile("assets/Zlevel10boss.png");
        background.setTexture(bgTexture);
        background.setScale(
            800.0f / bgTexture.getSize().x,
            600.0f / bgTexture.getSize().y
        );

        // open platforms for final boss
        platformCount = 3;
        platforms[0] = Platform(0, 524, 800, 10);   // ground
        platforms[1] = Platform(0, 350, 200, 10);   // left
        platforms[2] = Platform(600, 350, 200, 10); // right


        g = Gama(350, 150);

    }
}

// UPDATE 
//enemies update karo

void Level::update(Player& player)
{
    // botom update karo
    for (int i = 0; i < bCount; i++)
        b[i].update(platforms, platformCount);

    // flyingfooga update karo
    for (int i = 0; i < fCount; i++)
        f[i].update(platforms, platformCount);

    // tornado update karo
    for (int i = 0; i < tCount; i++)
        t[i].update(platforms, platformCount, player.getPosition());

    //invisible update karo
    for (int i = 0; i < invCount; i++)
        inV[i].update(platforms, platformCount, player.getPosition());

    // sirf level 5 par mogera update karo
    if (currentLevel == 5)
        m.update(platforms, platformCount, player.getPosition());

    // sirf level 10 par gama update karo
    if (currentLevel == 10)
        g.update(platforms, platformCount);
}


// DRAW
// sab draw karo

void Level::draw(sf::RenderWindow& window)
{
    // background draw karo
    window.draw(background);

    // platforms draw karo
    for (int i = 0; i < platformCount; i++)
        platforms[i].draw(window);

    // botom draw karo
    for (int i = 0; i < bCount; i++)
        b[i].draw(window);

    // flyingfooga draw karo
    for (int i = 0; i < fCount; i++)
        f[i].draw(window);

    // tornado draw karo
    for (int i = 0; i < tCount; i++)
        t[i].draw(window);

    // invisible draw karo
    for (int i = 0; i < invCount; i++)
        inV[i].draw(window);


    // sirf level 5 par mogera draw karo
    if (currentLevel == 5)
        m.draw(window);

    // sirf level 10 par gama draw karo
    if (currentLevel == 10)
        g.draw(window);
}



// sare enemies mare mar gae to level complete, check karo

bool Level::isComplete()
{
    // botom check karo
    for (int i = 0; i < bCount; i++)
        if (b[i].getZinda())
            return false;

    // flyingfooga check karo
    for (int i = 0; i < fCount; i++)
        if (f[i].getZinda())
            return false;

    // tornado check karo
    for (int i = 0; i < tCount; i++)
        if (t[i].getZinda())
            return false;

    // invisible enemies check karo
    for (int i = 0; i < invCount; i++)
        if (inV[i].getZinda())
            return false;

    // sirf level 5 par mogera check karo
    if (currentLevel == 5 && m.getZinda())
        return false;

    // sirf level 10 par gama check karo
    if (currentLevel == 10 && g.getZinda())
        return false;


    return true; // sab mar gaye level complete
}


// NEXT LEVEL 
// agla level load karo

void Level::nextLevel()
{
    currentLevel++;

    if (currentLevel > 10)
    {
        // game complete!
        currentLevel = 10; // abhi ke liye 10 par roko
        return;
    }
    loadLevel(currentLevel);
}

