#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
class HUD
{
private:
	sf::Font f;
	sf::Text scoreT;
	sf::Text livesT;
	sf::Text levelt;
	sf::Text gemT;

	

public :
	HUD()
	{//setFont() are built in fun that sets the font for the text objects
	//all this are built in functions that set the properties of the text objects like font, size, color and position

		f.loadFromFile("assets/FONT/BubbleBobble-rg3rx.ttf"); //Load a pixelated font for the HUD

		scoreT.setFont(f);  //Set the font for the score text
		scoreT.setCharacterSize(30);   //Set the character size for the score text
		scoreT.setFillColor(sf::Color::White);  //Set the color for the score text
		scoreT.setPosition(10, 10);  //Set the position for the score text
		
		livesT.setFont(f);  //Set the font for the lives text
		livesT.setCharacterSize(30);  //Set the character size for the lives text
		livesT.setFillColor(sf::Color::White);  //Set the color for the lives text	
		livesT.setPosition(10,40);   //Set the position for the lives text
		
		levelt.setFont(f);  //Set the font for the level text
		levelt.setCharacterSize(30);  //Set the character size for the level text
		levelt.setFillColor(sf::Color::White);  //Set the color for the level text
		levelt.setPosition(400, 10);  //Set the position for the level text
		
		gemT.setFont(f);  //Set the font for the gem text
		gemT.setCharacterSize(30);  //Set the character size for the gem text
		gemT.setFillColor(sf::Color::White);  //Set the color for the gem text
		gemT.setPosition(700, 10);  //Set the position for the gem text
	}

	void update(int score, int lives, int level, int gems)
	{

		//we get score like 15 then using to_string() we convert it to "15" and then concatenate
		//it with Score:  to get Score: 15 which is then set as the string for scoreT

		scoreT.setString("Score: " + to_string(score));  //Update the score text with the current score
		livesT.setString("Lives: " + to_string(lives));  //Update the lives text with the current lives
		levelt.setString("Level: " + to_string(level));  //Update the level text with the current level
		gemT.setString("Gems: " + to_string(gems));  //Update the gem text with the current gems collected
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(scoreT);  //Draw the score text on the window
		window.draw(livesT);  //Draw the lives text on the window
		window.draw(levelt);  //Draw the level text on the window
		window.draw(gemT);  //Draw the gem text on the window
	}
};