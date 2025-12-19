#include "head/ball.h"

Ball::Ball(sf::Texture &texture) : texture(texture) {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, ballWidth, ballHeight));
    sprite.setOrigin(
        sf::Vector2f(static_cast<float>(ballWidth) / 2.F, static_cast<float>(ballHeight) / 2.F));
}

void Ball::setPosition(sf::Vector2f ballPos) {
    ballX = ballPos.x;
    ballY = ballPos.y - 5;
    sprite.setPosition(sf::Vector2f(ballX, ballY));
}

void Ball::setRot(float ballRot) {
    sprite.setRotation(ballRot);
}

sf::Vector2f Ball::getPos() {
    return sprite.getPosition();
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
