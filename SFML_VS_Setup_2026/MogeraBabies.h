#pragma once

#include "Enemy.h"
#include "Platform.h"


class Mchild : public Enemy
{
	private:
		float jumpMC;    //falling speed
		bool groundMC;    //it is on the ground or not	

   public:
	   Mchild(float x=0.0f, float y=0.0f);
	   void update(Platform platforms[], int count) override;
	   void draw(sf::RenderWindow& window) override;
};