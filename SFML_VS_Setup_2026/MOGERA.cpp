
#include "MOGERA.h"
#include "MogeraBabies.h"
#include "Platform.h"


Mogera::Mogera(float x, float y)
{
	//enemy.setSize(sf::Vector2f(80, 80));
	//enemy.setFillColor(sf::Color::Magenta);
	enemy.setPosition(x, y);
	
	Health = 10.0f; //mogera ki health
	zindaE = true;
	directionE = 0.0f;    // Mogera does not move it is stationary boss
	timeB = 0.0f;      //time jis ke bad baby phainkni hai
	babyCount =0;       //in array 0 matlub phala batcha 
	
	Hbar.setSize(sf::Vector2f(200, 20));
	Hbar.setPosition(300, 20); //set it to top centre of the screen
	Hbar.setFillColor(sf::Color(200, 200, 200)); // Ya grey colour ha for health bar
	
	HbarBack.setSize(sf::Vector2f(200, 20));
	HbarBack.setFillColor(sf::Color::Black); //Black color for the bar health bar background
	HbarBack.setPosition(300, 20); //set it to top centre of the screen
}

void Mogera::update(Platform platforms[], int count, sf::Vector2f playerPos)
{
	timeB++;

	if (!zindaE)  // ager mogera mar jaata hai to update function se return kar jao aur baaki code execute mat karo
		return;


	if (timeB > 120 && babyCount < 50) // every 2 seconds baby phainkni hai jab tak 50 babies zinda hain
	{
		babies[babyCount] = Mchild(enemy.getPosition().x + 40, enemy.getPosition().y + 30); //child constructor call karo aur uska position set karo to be near mogera




		// set direction toward player
		if (playerPos.x < enemy.getPosition().x)
			babies[babyCount].setdirection(-1.0f);  // player left mein hai
		else
			babies[babyCount].setdirection(1.0f);   // player right mein hai


		babyCount++;
		timeB = 0;
	}

	for (int i = 0; i < babyCount; i++)
	{
		babies[i].update(platforms, count);
	}

		// health bar update karo   //abhii iska koi kaam nahi haaaaaa
	//float percent = healthE / Health;//
	//Hbar.setSize(sf::Vector2f(200.0f * percent, 20));
}

void Mogera::draw(sf::RenderWindow& window)
{
	if (zindaE) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) 
		{
			window.draw(enemy); //NORMAL enemy sprite ko pehle draw karo
			window.draw(HbarBack); // health bar background draw karo
			window.draw(Hbar); // health bar draw karo

			// MOGERA HITBOX 
			sf::RectangleShape box;

			// enemy sprite ke height aur width ke hisab se box ka size set karo
			box.setSize(sf::Vector2f(
				enemy.getGlobalBounds().width,
				enemy.getGlobalBounds().height
			));

			box.setPosition(enemy.getPosition()); // enemy sprite ke position par box set karo
			box.setFillColor(sf::Color::Transparent); // box transparent
			box.setOutlineColor(sf::Color::Red); // red color enemy ke liye
			box.setOutlineThickness(5); // box ka outline thickness

			window.draw(box); // hitbox ko sprite ke upar draw karo
		}
		else
		{
			window.draw(enemy); 
			window.draw(HbarBack); 
			window.draw(Hbar); 
		}
	}

	// sari zinda babies draw karo
	for (int i = 0; i < babyCount; i++) 
	{
		if (babies[i].getZinda()) 
			babies[i].draw(window); // baby sprite draw karo
	}
}