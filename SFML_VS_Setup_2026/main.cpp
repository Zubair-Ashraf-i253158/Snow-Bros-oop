#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <string>

struct Star {
    sf::CircleShape shape;
    float speed;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 700), "Catch the Stars!");
    window.setFramerateLimit(60);

    
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text scoreText, livesText, gameOverText;
    scoreText.setFont(font); scoreText.setCharacterSize(22);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    livesText.setFont(font); livesText.setCharacterSize(22);
    livesText.setFillColor(sf::Color(255, 100, 100));
    livesText.setPosition(400, 10);

    gameOverText.setFont(font); gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Yellow);
    gameOverText.setString("GAME OVER\nPress R to restart");
    gameOverText.setPosition(100, 280);

    // ── Player Catcher ─────────────────────────
    sf::RectangleShape catcher(sf::Vector2f(100.f, 18.f));
    catcher.setFillColor(sf::Color::Cyan);
    catcher.setPosition(250.f, 640.f);

    // ── Game State ─────────────────────────────
    int score = 0, lives = 3;
    bool gameOver = false;
    std::vector<Star> stars;

    sf::Clock gameClock, spawnClock;
    float spawnInterval = 1.2f;

    auto spawnStar = [&]() {
        Star s;
        s.shape.setRadius(14.f);
        s.shape.setFillColor(sf::Color(255, 220, 50));
        s.shape.setPosition(float(std::rand() % 570), -30.f);
        s.speed = 120.f + std::rand() % 180;
        stars.push_back(s);
        };

    while (window.isOpen()) {
        float dt = gameClock.restart().asSeconds();

        // Events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) window.close();
                if (gameOver && event.key.code == sf::Keyboard::R) {
                    score = 0; lives = 3; gameOver = false;
                    stars.clear(); spawnInterval = 1.2f;
                }
            }
        }

        if (!gameOver) {
            // Move catcher
            float speed = 280.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                catcher.move(-speed * dt, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                catcher.move(speed * dt, 0);

            // Clamp catcher to window
            if (catcher.getPosition().x < 0) catcher.setPosition(0, 640.f);
            if (catcher.getPosition().x > 500) catcher.setPosition(500, 640.f);

            // Spawn stars
            if (spawnClock.getElapsedTime().asSeconds() > spawnInterval) {
                spawnStar();
                spawnClock.restart();
                spawnInterval = std::max(0.4f, spawnInterval - 0.03f);
            }

            // Update stars
            for (auto& s : stars) s.shape.move(0, s.speed * dt);

            // Collision & cleanup
            stars.erase(std::remove_if(stars.begin(), stars.end(),
                [&](Star& s) {
                    if (s.shape.getGlobalBounds().intersects(catcher.getGlobalBounds())) {
                        score += 10; return true;
                    }
                    if (s.shape.getPosition().y > 720.f) {
                        lives--; if (lives <= 0) gameOver = true; return true;
                    }
                    return false;
                }), stars.end());
        }

        // Update HUD text
        scoreText.setString("Score: " + std::to_string(score));
        livesText.setString("Lives: " + std::to_string(lives));

        // Render
        window.clear(sf::Color(10, 10, 30));
        for (auto& s : stars) window.draw(s.shape);
        window.draw(catcher);
        window.draw(scoreText);
        window.draw(livesText);
        if (gameOver) window.draw(gameOverText);
        window.display();
    }
}