#pragma once
#include <SFML/Graphics.hpp>

enum ItemType { GEM, STAR };

struct Item {
    sf::Sprite sprite;
    ItemType type;
    bool active = false;

    
    void spawn(float x, float y, ItemType t, sf::Texture& tex) {
        type = t;
        sprite.setTexture(tex);
        sprite.setPosition(x, y);
        active = true;
    }

    sf::FloatRect getBounds() { return sprite.getGlobalBounds(); }
};