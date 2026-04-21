#pragma once
#include "Enemy.h"
#include "Platform.h"
#include "Botom.h"

class FlyingFooga : public Enemy, public Botom
{
 private:
	float flyE;    // fly strength
	bool flyingE;     // is flying

public:	
	FlyingFooga(float x, float y);
	void update(Platform platforms[], int count) override;
	void draw(sf::RenderWindow& window) override;
};