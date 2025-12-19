#include "head/ball.h"
#include "head/window.h"

Ball::Ball(sf::Texture &texture, b2WorldId worldId, b2BodyDef &ballDef, b2ShapeDef &ballShapeDef,
           b2Circle &circle)
    : texture(texture)
    , ballX(ballDef.position.x * PIXIVS_PER_METER)
    , ballY(ballDef.position.y * PIXIVS_PER_METER) {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, ballWidth, ballHeight));
    sprite.setOrigin(static_cast<float>(ballWidth) / 2.F, static_cast<float>(ballHeight) / 2.F);
    sprite.setPosition(ballX, ballY);

    ballId = b2CreateBody(worldId, &ballDef);
    b2CreateCircleShape(ballId, &ballShapeDef, &circle);
}

void Ball::updateAndDraw(sf::RenderWindow &window) {
    b2Transform ballTransform = b2Body_GetTransform(ballId);

    b2Vec2 ballPos = ballTransform.p;
    b2Rot ballRot = ballTransform.q;
    float ballAngle = b2Rot_GetAngle(ballRot);

    ballX = ballPos.x * PIXIVS_PER_METER;
    ballY = ballPos.y * PIXIVS_PER_METER;

    sprite.setPosition(sf::Vector2f(ballX, ballY));
    sprite.setRotation(ballAngle * 180.F / B2_PI);

    window.draw(sprite);
}

sf::Vector2f Ball::getPos() const {
    return {ballX, ballY};
}

float Ball::getRot() {
    return sprite.getRotation();
}

void Ball::bounceUp() {
    b2Body_ApplyLinearImpulse(ballId, (b2Vec2){0.F, -UPWARD_IMPULSE}, b2Body_GetPosition(ballId),
                              true);
}
