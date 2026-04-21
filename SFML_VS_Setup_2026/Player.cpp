#include"Player.h"

Player::Player()
{
	player.setSize(sf::Vector2f(30, 30));
	player.setFillColor(sf::Color::Red);
	player.setPosition(400, 500);
}

void Player::update()
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
	if (player.getPosition().y >= 500)
	{
		player.setPosition(player.getPosition().x, 500);
		jumpSpeed = 0;
		Ground = true;
	}
}