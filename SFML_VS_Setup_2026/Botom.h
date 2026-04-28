#pragma once
#include "Enemy.h"
#include "Platform.h"

class Botom : public Enemy
{	
protected:

	   float jumpE;    // jump strength
	   bool groundE;     // fall speed
	  // int animFrame = 0;
	  // int animTimer = 0;


	   //botom alsoi jump randomly
	   int jumpT; // ya count kre ga ka kitna time guuzar gaya after jump 
	   float jumpD;  //kitne time baad jummp krni ha 

   public:
	   Botom() : Botom(0, 0) {}
	   Botom(float x, float y);
	   void update(Platform platforms[],int count) override;
	   void draw(sf::RenderWindow& window) override;
};
