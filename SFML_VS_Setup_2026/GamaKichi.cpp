#include"Enemy.h"
#include "GamaKichi.h"

Gama::Gama(float x, float y)
{
	enemy.setSize(sf::Vector2f(100, 100));
	enemy.setFillColor(sf::Color(128,0,128));  //Purple
	enemy.setPosition(x, y);
	
	MaxH =1000.0f; //gamay ki max health
	healthE = MaxH; //gamay ki health
	zindaE = true;
	
	directionE = 0.0f;    // Gama does not move it is stationary boss
	rocketTime = 0.0f;      //time jis ke bad rocket nikle ga
	attackP = 0; //gamay ke attack phase
	
	/* Front health bar */
	Ghealthbar.setSize(sf::Vector2f(200, 20));
	Ghealthbar.setPosition(300, 50); //set it to top centre of the screen
	Ghealthbar.setFillColor(sf::Color(200, 200, 200)); // Ya grey colour ha for health bar
	
	/* Back health bar */
	GhealthBack.setSize(sf::Vector2f(200, 20));
	GhealthBack.setFillColor(sf::Color::Black); //Black color for the bar health bar background
	GhealthBack.setPosition(300, 50); //set it to top centre of the screen
	
	
	for (int i = 0; i < 5; i++)
	{
		rocket[i].setSize(sf::Vector2f(10, 10));   
		rocket[i].setFillColor(sf::Color::Yellow);
		rocketactive[i] = false;              //sab rockets initially inactive hain
	}
} 

void Gama::update(Platform platforms[], int count)
{
	if (!zindaE)  // ager gama mar jaata hai to update function se return kar jao aur baaki code execute mat karo
		return;

	if (healthE > 666)
	{
		attackP = 0; // phase 1
	}
	else if (healthE > 333)
	{
		attackP = 1; // phase 2
	}
	else
	{
		attackP = 2; // phase 3
	}

	rocketTime++;

	if ((attackP == 0 && rocketTime > 120) ||
		(attackP == 1 && rocketTime > 80) ||
		(attackP == 2 && rocketTime > 40))
	{
		// har rocket ki position aur direction set karo
		for (int i = 0; i < 5; i++)
		{
			RocketPosition(i);       // position set karo
			rocketactive[i] = true;  // activate karo
		}

		// directions set karo - speedX speedY mein
		speedX[0] = 0;   speedY[0] = -5; // upar
		speedX[1] = 0;   speedY[1] = 5;  // neeche
		speedX[2] = -5;  speedY[2] = 0;  // left
		speedX[3] = 5;   speedY[3] = 0;  // right
		speedX[4] = 4;   speedY[4] = -4; // diagonal

		// rockets move karo
		for (int i = 0; i < 5; i++)
		{
			if (rocketactive[i])
			{
				rocket[i].move(speedX[i], speedY[i]);

				if (rocket[i].getPosition().x < 0 || rocket[i].getPosition().x > 800 || rocket[i].getPosition().y < 0 || rocket[i].getPosition().y > 600)
					rocketactive[i] = false;
			}
		}

		// health bar update karo
		float percent = healthE / MaxH;
		Ghealthbar.setSize(sf::Vector2f(200.0f * percent, 20));
	}

}
	void Gama::draw(sf::RenderWindow & window)
	{
		// ager gama zinda hai to hi draw karo
		if (!zindaE) return;

		// gama draw karo
		window.draw(enemy);

		// health bar background draw karo
		window.draw(GhealthBack);

		//health bar draw karo
		window.draw(Ghealthbar);

		//sare active rockets draw karo
		for (int i = 0; i < 5; i++)
		{
			if (rocketactive[i])        // sirf active rockets draw karo
				window.draw(rocket[i]);
		}
	}