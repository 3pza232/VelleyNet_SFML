#include "head/function.h"
#include "head/player.h"

Player::Player(sf::Texture &texture, int flag) : texture(texture) {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, playerWidth, playerHeight));
    if (flag == 1) {
        sprite.setColor(HEX_TO_COLOR(0xbf1913, 255));
    } else {
        sprite.setColor(HEX_TO_COLOR(0x1942bd, 255));
    }
    sprite.setOrigin(sf::Vector2f(static_cast<float>(playerWidth) / 2.F,
                                  static_cast<float>(playerHeight) / 2.F));
}

void Player::setPosition(sf::Vector2f playerPos) {
    playerX = playerPos.x;
    playerY = playerPos.y - 5;
    sprite.setPosition(sf::Vector2f(playerX, playerY));
}

void Player::setRot(float playerRot) {
    sprite.setRotation(playerRot);
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
