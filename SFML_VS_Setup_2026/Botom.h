#pragma once
#include "Enemy.h"
#include "Platform.h"

class Botom : public Enemy
{	
   private: 
	   float jumpE;    // jump strength
	   bool groundE;     // fall speed

   public:

	   Botom(float x, float y);
	   void update(Platform platforms[],int count) override;
	   void draw(sf::RenderWindow& window) override;
};
