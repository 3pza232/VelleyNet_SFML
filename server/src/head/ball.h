#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Ball {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    const int ballWidth = 64;
    const int ballHeight = 64;
    float ballX{}, ballY{};

    b2BodyId ballId{};

    const float UPWARD_IMPULSE = 9.F; // 向上的冲量

public:
    explicit Ball(sf::Texture &texture, b2WorldId worldId, b2BodyDef &ballDef,
                  b2ShapeDef &ballShapeDef, b2Circle &circle);
    void updateAndDraw(sf::RenderWindow &window);
    sf::Vector2f getPos() const;
    float getRot();
    void bounceUp();
};
