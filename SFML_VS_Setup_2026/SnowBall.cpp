#include "SnowBall.h"

SnowBall::SnowBall()
{
	ball.setRadius(10); // snowball size
	ball.setFillColor(sf::Color::White); // snowball color
	speed = 4.0f; // snowball speed
}

void SnowBall::setact(bool active)  //setter
{
	this->active = false; // snowball active status set karo
}

void SnowBall::setfire(float x, float y)
{
	ball.setPosition(x, y); // snowball ki starting position set karo
}

void SnowBall::shoot(float dirX)
{
	directionX = dirX;  //if -1 go left if 1 go right
	active = true;
}

bool SnowBall::act() const      //getter
{
	return active; // batao ki snowball active hai ya nahi
}

void SnowBall::update()
{
	if (active)
	{
		ball.move(directionX * speed, 0); // move horizontally

		if (directionX > 0 && ball.getPosition().x > 800) // right boundary check
			active = false;
		else if (directionX < 0 && ball.getPosition().x < 0) // left boundary check
			active = false;
	}
}

void SnowBall::draw(sf::RenderTarget& target) const
{
	if (active)
		target.draw(ball);
}

sf::FloatRect SnowBall::getBounds() const
{
	return ball.getGlobalBounds();
}