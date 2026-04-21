#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);

    // Player box
    sf::RectangleShape player(sf::Vector2f(30, 30));
    player.setFillColor(sf::Color::Red);
    player.setPosition(400,500);

    // -------- Speeds (change these anytime) --------
    float movement = 3.0f;     // left right speed
    float jump = -8.0f;    // jump strength
    float gravity = 0.3f;       // fall speed

    float jumpSpeed = 0.0f;     // current up/down speed
    bool Ground = true;
    while (window.isOpen())
    {
        // Close window
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

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

        // Draw
        window.clear();
        window.draw(player);
        window.display();
    }
}