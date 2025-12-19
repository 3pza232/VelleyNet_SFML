#pragma once

#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    const int ballWidth = 64;
    const int ballHeight = 64;
    float ballX{};
    float ballY{};

public:
    explicit Ball(sf::Texture &texture);
    void setPosition(sf::Vector2f ballPos);
    void setRot(float ballRot);
    sf::Vector2f getPos();
    void draw(sf::RenderWindow &window);
};
