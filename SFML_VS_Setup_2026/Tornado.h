#pragma once
#include "FlyingFooga.h"

class Tornado : public FlyingFooga
{
private:
    sf::RectangleShape knife;  // knife
    float knifeTime;      // time jis ka bad knife phainkni ha
    bool zindaK;  //knife zinda
    float knifex;     // knife horizontal 
    float knifey;     // knife vertical

public:

    Tornado(float x, float y);
	void update(Platform platforms[], int count, sf::Vector2f p_pos); // player position takay nishana lagay
    void draw(sf::RenderWindow& window) override;

	/*Knife related functions for collision*/

    
    void setK_Act(bool a);
    bool getK_Act() const;
    sf::FloatRect getK_Bounds() const;
        
      
};