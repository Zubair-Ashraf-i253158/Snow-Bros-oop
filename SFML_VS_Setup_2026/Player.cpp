#include"Player.h"

Player::Player()
{
	player.setSize(sf::Vector2f(30, 30));
	player.setFillColor(sf::Color::Red);
	player.setPosition(400, 500);
}

void Player::update(Platform platforms[], int count)
{
	// Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player.move(-movement, 0);
	// Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		player.move(movement, 0);
	// Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && Ground)
	{
		jumpSpeed = jump;
		Ground = false;
	}
	// Left wall
	if (player.getPosition().x < 0)
		player.setPosition(0, player.getPosition().y);
	// Right wall
	if (player.getPosition().x > 770)  // 800 - 30 (player width)
		player.setPosition(770, player.getPosition().y);
	// Up / Down
	player.move(0, jumpSpeed);
	jumpSpeed += gravity;
	// Ground
	Ground = false; // har time fall
	for (int i = 0; i < count; i++)
	{
		//FloatRect is builtin sfml that contains 4 values: left, top, width, height
		sf::FloatRect pl_bndry = platforms[i].getBounds();//platform ki boundary
		sf::FloatRect p_bndry = player.getGlobalBounds();//player ki boundary

		// Check if player bottom is hitting platform top
		bool side =(p_bndry.left < pl_bndry.left + pl_bndry.width) && (p_bndry.left + p_bndry.width > pl_bndry.left);
		bool top = (p_bndry.top + p_bndry.height >= pl_bndry.top) && (p_bndry.top + p_bndry.height <= pl_bndry.top + 10);

		if (side && top)
		{
			player.setPosition(player.getPosition().x, pl_bndry.top - p_bndry.height);
			jumpSpeed = 0;
			Ground = true;
		}
	}
}
 void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(player, states);
}