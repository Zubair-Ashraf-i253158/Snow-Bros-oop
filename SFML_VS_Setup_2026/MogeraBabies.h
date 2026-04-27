#pragma once

#include "Enemy.h"
#include "Platform.h"
#include "Botom.h"


class Mchild : public Botom
{
	private:
		float jumpMC;    //falling speed
		bool groundMC;    //it is on the ground or not	

   public:
	   Mchild() : Mchild(0, 0) {}
	   Mchild(float x, float y);
	   void update(Platform platforms[], int count) override;
	   void draw(sf::RenderWindow& window) override;
};