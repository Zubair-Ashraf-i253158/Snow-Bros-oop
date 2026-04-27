#pragma once
#include "Tornado.h"



class Invisible : public Tornado
{


public:
	bool see; //player visivle hai ya nahi
	float seeTime; //time jis ke bad player visible hoga
	public:
	Invisible() : Invisible(0, 0) {}
	Invisible(float x, float y);
	void update(Platform platforms[], int count, sf::Vector2f p_pos) override;
	void draw(sf::RenderWindow& window) override;
};
