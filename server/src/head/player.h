#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    const int playerWidth = 75;
    const int playerHeight = 89;
    float playerX{}, playerY{};

    b2BodyId playerId;

    enum class JUMP_STATE : uint8_t { JUMPING, STANDING };
    JUMP_STATE jumpState;

    const float JUMP_IMPULSE = 6.5F; // 跳跃冲量
    const float MOVE_FORCE = 22.5F;  // 横向移动力

public:
    explicit Player(sf::Texture &texture, b2BodyId playerId, b2ShapeDef &playerShapeDef,
                    b2Polygon &playerPolygon, int flag);
    void updateAndDraw(sf::RenderWindow &window);
    void playerJump();
    void playerMoveToLeft();
    void playerMoveToRight();
    sf::Vector2f getPos() const;
    float getRot();
};
