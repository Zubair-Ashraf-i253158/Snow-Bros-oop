#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"
using namespace std;
class HUD
{
private:
	sf::Font f;
	sf::Text levelt;

	// Multiplayer HUD elements
	sf::Text p1scoret;
	sf::Text p1livest;
	sf::Text p1Gemt;
	sf::Text p2scoret;
	sf::Text p2livest;
	sf::Text p2Gemt;
	bool isMultiplayer = false;

public:
	HUD()
	{//setFont() are built in fun that sets the font for the text objects
	//all this are built in functions that set the properties of the text objects like font, size, color and position

		f.loadFromFile("assets/FONT/BubbleBobble-rg3rx.ttf"); //Load a pixelated font for the HUD

		p1scoret.setFont(f);  //Set the font for the score text
		p1scoret.setCharacterSize(30);   //Set the character size for the score text
		p1scoret.setFillColor(sf::Color::White);  //Set the color for the score text
		p1scoret.setPosition(10, 10);  //Set the position for the score text

		p1livest.setFont(f);  //Set the font for the lives text
		p1livest.setCharacterSize(30);  //Set the character size for the lives text
		p1livest.setFillColor(sf::Color::White);  //Set the color for the lives text	
		p1livest.setPosition(10, 40);   //Set the position for the lives text

		levelt.setFont(f);  //Set the font for the level text
		levelt.setCharacterSize(30);  //Set the character size for the level text
		levelt.setFillColor(sf::Color::White);  //Set the color for the level text
		levelt.setPosition(400, 10);  //Set the position for the level text

		p1Gemt.setFont(f);  //Set the font for the gem text
		p1Gemt.setCharacterSize(30);  //Set the character size for the gem text
		p1Gemt.setFillColor(sf::Color::White);  //Set the color for the gem text
		p1Gemt.setPosition(700, 10);  //Set the position for the gem text

		// Always initialize P2 text objects (they will be drawn conditionally)
		p2scoret.setFont(f);  //Set the font for the score text
		p2scoret.setCharacterSize(30);   //Set the character size for the score text
		p2scoret.setFillColor(sf::Color::White);  //Set the color for the score text
		p2scoret.setPosition(400, 40);  //Set the position for the score text

		p2livest.setFont(f);  //Set the font for the lives text
		p2livest.setCharacterSize(30);  //Set the character size for the lives text
		p2livest.setFillColor(sf::Color::White);  //Set the color for the lives text	
		p2livest.setPosition(400, 70);   //Set the position for the lives text

		p2Gemt.setFont(f);  //Set the font for the gem text
		p2Gemt.setCharacterSize(30);  //Set the character size for the gem text
		p2Gemt.setFillColor(sf::Color::White);  //Set the color for the gem text
		p2Gemt.setPosition(700, 40);  //Set the position for the gem text
	}
	// HUD mein dono players ki info dikhao
	void update(int score1, int lives1, int level, int gems1,
		int score2 = 0, int lives2 = 0, int gems2 = 0, bool multiplayer = false)
	{
		this->isMultiplayer = multiplayer;
		//we get score like 15 then using to_string() we convert it to "15" and then concatenate
		//it with Score:  to get Score: 15 which is then set as the string for scoreT
		// P1
		p1scoret.setString("P1 Score: " + to_string(score1));
		p1livest.setString("Lives: " + to_string(lives1));
		p1Gemt.setString("Gems: " + to_string(gems1));
		if (isMultiplayer)
		{
			// P2 
			p2scoret.setString("P2 Score: " + to_string(score2));
			p2livest.setString("Lives: " + to_string(lives2));
			p2Gemt.setString("Gems: " + to_string(gems2));
		}
		// level center mein
		levelt.setString("Level: " + to_string(level));
	}

	void draw(sf::RenderWindow& window)
	{

		window.draw(p1scoret);
		window.draw(p1livest);
		window.draw(p1Gemt);

		if (isMultiplayer)
		{
			window.draw(p2scoret);
			window.draw(p2livest);
			window.draw(p2Gemt);
		}
		// level center mein

		window.draw(levelt);
	}
};