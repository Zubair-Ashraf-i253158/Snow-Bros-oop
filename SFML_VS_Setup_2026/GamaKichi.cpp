#include "Enemy.h"
#include "GamaKichi.h"

Gama::Gama(float x, float y)
{
    
    enemy.setSize(sf::Vector2f(100, 100));      // 100x100 ka bara boss
    enemy.setFillColor(sf::Color(128, 0, 128)); // Purple colour
    enemy.setPosition(x, y);                   

    // Health setup
    MaxH = 1000.0f;    // maximum health 1000
    healthE = MaxH;    // shuru mein full health
    zindaE = true;     

    // Gama halta nahi hai isliye direction 0
    directionE = 0.0f;

    // Timer aur phase setup
    rocketTime = 0.0f; // rocket fire karne ka timer
    attackP = 0;       // shuru mein phase 1

    
    // Front Health Bar
    
    Ghealthbar.setSize(sf::Vector2f(200, 50));     
    Ghealthbar.setPosition(300, 50);                // screen ke top centre mein
    Ghealthbar.setFillColor(sf::Color(200, 200, 200)); // grey colour

    
    GhealthBack.setSize(sf::Vector2f(200, 50));    // same size
    GhealthBack.setFillColor(sf::Color::Black);    // kala background
    GhealthBack.setPosition(300, 50);              // same position

   
    // Rockets set
    
    for (int i = 0; i < 5; i++)
    {
        rocket[i].setSize(sf::Vector2f(15, 15));    
        rocket[i].setFillColor(sf::Color::Yellow);  // yellow colour
        rocketactive[i] = false;                    // shuru mein sab inactive
    }
}

void Gama::update(Platform platforms[], int count)
{
    // ager gama mar gaya to kuch mat karo
    if (!zindaE) return;

   
    // Attack Phase Check
    // health ke hisaab se phase badalta hai
   
    if (healthE > 666)      
       attackP = 0; // phase 1 slow fire
    
    else if (healthE > 333) 
        attackP = 1; // phase 2 medium fire
    
    else                   
        attackP = 2; // phase 3 fast fire

    
    rocketTime++;

    
    //Phase Ke Hisaab Se Fire Karo
   
    if ((attackP == 0 && rocketTime > 120) ||
        (attackP == 1 && rocketTime > 80) ||
        (attackP == 2 && rocketTime > 40))
    {
        // har rocket ko activate karo
        for (int i = 0; i < 5; i++)
        {
            // sirf tab set karo jab rocket inactive ho
            // warna rocket reset ho jata hai beech mein
            if (!rocketactive[i])
            {
                RocketPosition(i);      // rocket ki starting position set karo
                rocketactive[i] = true; // rocket ko active karo
            }
        }

       
        // har rocket ko alag direction do
        speedX[0] = 0;   speedY[0] = -5; // rocket 0 upar jaye ga
        speedX[1] = 0;   speedY[1] = 5;  // rocket 1 neeche jaye ga
        speedX[2] = -5;  speedY[2] = 0;  // rocket 2 left jaye ga
        speedX[3] = 5;   speedY[3] = 0;  // rocket 3 right jaye ga
        speedX[4] = 4;   speedY[4] = -4; // rocket 4 diagonal jaye ga

        // timer reset karo agla fire ke liye
        rocketTime = 0;
    }

    for (int i = 0; i < 5; i++)
    {
        if (rocketactive[i]) // sirf active rockets move karo
        {
            // rocket ko uski speed se move karo
            rocket[i].move(speedX[i], speedY[i]);

            // ager rocket screen se bahar chala gaya to deactivate karo
            if (rocket[i].getPosition().x < 0 ||    
                rocket[i].getPosition().x > 800 || 
                rocket[i].getPosition().y < 0 ||    
                rocket[i].getPosition().y > 600)    
                rocketactive[i] = false;
        }
    }

    float percent = healthE / MaxH;                         
    Ghealthbar.setSize(sf::Vector2f(200.0f * percent, 20)); // bar choti karo
}

void Gama::draw(sf::RenderWindow& window)
{
    // ager gama mar gaya to kuch mat draw karo
    if (!zindaE) return;

    //Gama draw karo
    window.draw(enemy);

    // health bar ka kala background draw karo
    window.draw(GhealthBack);

    // actual health bar draw karo upar se
    window.draw(Ghealthbar);

    // Step 4 - sare active rockets draw karo
    for (int i = 0; i < 5; i++)
    {
        if (rocketactive[i])        // sirf active rockets draw karo
            window.draw(rocket[i]);
    }
}