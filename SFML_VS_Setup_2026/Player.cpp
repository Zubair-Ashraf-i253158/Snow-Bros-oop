#include"Player.h"

Player::Player()
{
	if (!playerTexture.loadFromFile("assets/playerSprites.png"))
	{
		sf::RectangleShape PLAYER;
		PLAYER.setSize(sf::Vector2f(50, 50));	
		PLAYER.setFillColor(sf::Color::Red);
		
				
	}
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(sf::IntRect(0, 0, 50, 50)); // pehla frame
	playerSprite.setPosition(400, 400);
}
void Player::update(Platform platforms[], int count)
{
	animTimer++;
	

	
	// Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		facingRight = false;
		playerSprite.move(-movement, 0);
	}
	// Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		facingRight = true;
		playerSprite.move(movement, 0);
	}
	// flip left/right
	if (!facingRight)
	{
		playerSprite.setScale(-1.0f, 1.0f);
		playerSprite.setOrigin(60, 0); // origin fix for flip
	}
	else
	{
		playerSprite.setScale(1.0f, 1.0f);
		playerSprite.setOrigin(0, 0);
	}
	// walking
	bool moving = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

	if (moving)
	{
		animTimer++;
		if (animTimer > 8) // changing frame 
		{
			animFrame = (animFrame + 1) % 4;
			animTimer = 0;
		}
	}
	else
	{
		animFrame = 0; // idle 
		animTimer = 0;
	}

	// now set the frame
	if (!Ground)
		playerSprite.setTextureRect(sf::IntRect(0, 64, 60, 64)); // jump frame
	else if (moving)
		playerSprite.setTextureRect(sf::IntRect(animFrame * 60, 0, 60, 64)); // walk
	else
		playerSprite.setTextureRect(sf::IntRect(0, 0, 60, 64)); // idle
	

	
	// Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && Ground)
	{
		jumpSpeed = jump;
		Ground = false;
	}
	// Left wall
	if (playerSprite.getPosition().x < 0)
		playerSprite.setPosition(0, playerSprite.getPosition().y);
	// Right wall
	if (playerSprite.getPosition().x > 770)  // 800 - 30 (player width)
		playerSprite.setPosition(770, playerSprite.getPosition().y);
	// Up / Down
	playerSprite.move(0, jumpSpeed);
	jumpSpeed += gravity;
	// Ground
	Ground = false; // har time fall
	for (int i = 0; i < count; i++)
	{
		//FloatRect is builtin sfml that contains 4 values: left, top, width, height
		sf::FloatRect pl_bndry = platforms[i].getBounds();//platform ki boundary
		sf::FloatRect p_bndry = playerSprite.getGlobalBounds();//player ki boundary

		// Check if player bottom is hitting platform top
		bool side =(p_bndry.left < pl_bndry.left + pl_bndry.width) && (p_bndry.left + p_bndry.width > pl_bndry.left);
		bool top = (p_bndry.top + p_bndry.height >= pl_bndry.top) && (p_bndry.top + p_bndry.height <= pl_bndry.top + 10);

		if (side && top)
		{
			playerSprite.setPosition(playerSprite.getPosition().x, pl_bndry.top - p_bndry.height);
			jumpSpeed = 0;
			Ground = true;
		}
	}
}
 void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(playerSprite, states);
	
}