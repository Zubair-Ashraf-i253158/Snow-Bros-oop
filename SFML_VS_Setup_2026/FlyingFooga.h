#pragma once
#include "Enemy.h"
#include "Platform.h"
#include "Botom.h"

class FlyingFooga :public Botom
{
protected:
	
	bool flyingE;     // is flying
	float flyx; //fly ki speed horizonatal
	float flyy; //fly ki speed vertical
	float flyTime;//time jab tak enemy fly karega
public:	
	FlyingFooga(float x, float y);
	void update(Platform platforms[], int count) override;
	void draw(sf::RenderWindow& window) override;
};