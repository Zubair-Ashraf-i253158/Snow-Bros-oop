#pragma once
#include "Player.h"
#include "Botom.h"
#include "Enemy.h"
#include "FlyingFooga.h"  
#include "Tornado.h"    

class Collision
{
public:
  
    
    // Botom Collision Check
    
    static void BotomCollision(Player& player, Botom b[], int bCount)
    {
    
        // Snowball hits Botom
     
        for (int i = 0; i < player.getballcount(); i++)
        {
            if (!player.getBallActive(i))
                continue; // inactive ball skip karo

            for (int j = 0; j < bCount; j++)
            {
                if (b[j].getZinda() && !b[j].getCover()) // zinda aur cover be nahi ha
                {
                    if (player.getBallBounds(i).intersects(b[j].getBounds())) // overlap check
                    {
                        b[j].damage(1);                  // botom ko damage do
                        player.setBallActive(i, false);  // ball deactivate karo
                    }
                }
            }
        }

      
        // Player touches Botom
        if (!player.gethit()) // sirf tab check karo jab player hurt na ho
        {
            for (int j = 0; j < bCount; j++)
            {
                if (b[j].getZinda() && !b[j].getCover()) // zinda aur non encased
                {
                    if (player.getBounds().intersects(b[j].getBounds())) // overlap check
                    {
                        player.lifedown(); // player ki life kam karo
                    }
                }
            }
        }
    }


/* Flyfooga Collision Check */

static void FlyingFoogaCollision(Player& player, FlyingFooga f[], int fCount)
{

    // Snowball hits FlyingFooga

    for (int i = 0; i < player.getballcount(); i++)
    {
        if (!player.getBallActive(i))
            continue; // inactive ball skip karo

        for (int j = 0; j < fCount; j++)
        {
            if (f[j].getZinda() && !f[j].getCover()) // zinda aur cover be nahi ha
            {
                if (player.getBallBounds(i).intersects(f[j].getBounds())) // overlap check
                {
                    f[j].damage(1);                  // FlyingFooga ko damage do
                    player.setBallActive(i, false);  // ball deactivate karo
                }
            }
        }
    }


    // Player touches fooga
    if (!player.gethit()) // sirf tab check karo jab player hurt na ho
    {
        for (int j = 0; j < fCount; j++)
        {
            if (f[j].getZinda() && !f[j].getCover()) // zinda aur non encased
            {
                if (player.getBounds().intersects(f[j].getBounds())) // overlap check
                {
                    player.lifedown(); // player ki life kam karo
                }
            }
        }
    }
}

/*Tornado Collision Check */

static void TornadoCollision(Player& player, Tornado t[], int tCount)
{
    // Snowball hits Tornado
    for (int i = 0; i < player.getballcount(); i++)
    {
        if (!player.getBallActive(i)) continue; // inactive ball skip karo

        for (int j = 0; j < tCount; j++)
        {
            if (t[j].getZinda() && !t[j].getCover()) // zinda aur non encased
            {
                if (player.getBallBounds(i).intersects(t[j].getBounds())) // overlap check
                {
                    t[j].damage(1);                 // tornado ko damage do
                    player.setBallActive(i, false); // ball deactivate karo
                }
            }
        }
    }

    //Player touches Tornado
    if (!player.gethit()) // sirf tab check karo jab player hurt na ho
    {
        for (int j = 0; j < tCount; j++)
        {
            if (t[j].getZinda() && !t[j].getCover()) // zinda aur non encased
            {
                if (player.getBounds().intersects(t[j].getBounds())) // overlap check
                {
                    player.lifedown(); // player ki life kam karo
                }
            }
        }
    }

    // Knife hits Player
    if (!player.gethit()) // sirf tab check karo jab player hurt na ho
    {
        for (int j = 0; j < tCount; j++)
        {
            if (t[j].getK_Act() ) 
            {
                if (t[j].getK_Bounds().intersects(player.getBounds())) // overlap check
                {
                    player.lifedown();          // player ki life kam karo
                    t[j].setK_Act(false); // knife deactivate karo
                }
            }
        }
    }
}
};
