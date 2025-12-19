#pragma once

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    const int playerWidth = 75;
    const int playerHeight = 89;
    float playerX{};
    float playerY{};

public:
    explicit Player(sf::Texture &texture, int flag);
    void setPosition(sf::Vector2f playerPos);
    void setRot(float playerRot);
    void draw(sf::RenderWindow &window);
};
