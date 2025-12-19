#include "head//function.h"
#include "head/player.h"
#include "head/window.h"

Player::Player(sf::Texture &texture, b2BodyId playerId, b2ShapeDef &playerShapeDef,
               b2Polygon &playerPolygon, int flag)
    : texture(texture)
    , playerX(b2Body_GetTransform(playerId).p.x * PIXIVS_PER_METER)
    , playerY(b2Body_GetTransform(playerId).p.y * PIXIVS_PER_METER)
    , playerId(playerId)
    , jumpState(JUMP_STATE::JUMPING) {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, playerWidth, playerHeight));
    sprite.setOrigin(static_cast<float>(playerWidth) / 2.F, static_cast<float>(playerHeight) / 2.F);
    sprite.setPosition(sf::Vector2f(playerX, playerY));

    if (flag == 1) {
        sprite.setColor(HEX_TO_COLOR(0xbf1913, 255));
    } else {
        sprite.setColor(HEX_TO_COLOR(0x1942bd, 255));
    }

    b2CreatePolygonShape(playerId, &playerShapeDef, &playerPolygon);
}

void Player::updateAndDraw(sf::RenderWindow &window) {
    b2Transform playerTransform = b2Body_GetTransform(playerId);

    b2Vec2 playerPos = playerTransform.p;
    b2Rot playerRot = playerTransform.q;
    float playerAngle = b2Rot_GetAngle(playerRot);

    playerX = playerPos.x * PIXIVS_PER_METER;
    playerY = playerPos.y * PIXIVS_PER_METER;

    if (static_cast<float>(window.getSize().y) - playerY <=
        static_cast<float>(playerWidth) / 2.F + 15.F) {
        jumpState = JUMP_STATE::STANDING;
    } // 重置跳跃状态

    sprite.setPosition(sf::Vector2f(playerX, playerY));
    sprite.setRotation(playerAngle * 180.F / B2_PI);

    window.draw(sprite);
}

void Player::playerJump() {
    if (jumpState == JUMP_STATE::STANDING) {
        jumpState = JUMP_STATE::JUMPING;
        b2Body_ApplyLinearImpulseToCenter(playerId, (b2Vec2){0.F, -JUMP_IMPULSE}, true);
    }
}

void Player::playerMoveToLeft() {
    b2Body_ApplyForceToCenter(playerId, (b2Vec2){-MOVE_FORCE, 0.F}, true);
}

void Player::playerMoveToRight() {
    b2Body_ApplyForceToCenter(playerId, (b2Vec2){MOVE_FORCE, 0.F}, true);
}

sf::Vector2f Player::getPos() const {
    return {playerX, playerY};
}

float Player::getRot() {
    return sprite.getRotation();
}
