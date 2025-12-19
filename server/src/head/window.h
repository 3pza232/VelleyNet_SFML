#pragma once

#include "ball.h"
#include "netWorkManager.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

const float PIXIVS_PER_METER = 60.F;

class GameWindow {
private:
    // 窗口显示
    sf::RenderWindow window;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    int windowWidth{};
    int windowHeight{};

    ///////////////// 世界/////////////////
    b2WorldDef worldDef = b2DefaultWorldDef();
    b2WorldId world{};
    float timeStep = 1.F / 60.F;
    int subStepCount = 8;

    ///////////////// 地面/顶端 /////////////////
    float groundHeight{};
    b2BodyDef groundDef = b2DefaultBodyDef();
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2Polygon groundPolygon{};
    b2BodyId ground{};
    b2BodyId top{};

    ///////////////// 墙 /////////////////
    float wallWidth{};
    b2BodyDef wallDef = b2DefaultBodyDef();
    b2ShapeDef wallShapeDef = b2DefaultShapeDef();
    b2Polygon wallPolygon{};
    b2BodyId leftWall{};
    b2BodyId rightWall{};

    ///////////////// 球网 /////////////////
    float ballNetWidth{};
    float ballNetHeight{};
    b2BodyDef ballNetDef = b2DefaultBodyDef();
    b2ShapeDef ballNetShapeDef = b2DefaultShapeDef();
    b2Polygon ballNetPolygon{};
    b2BodyId ballNet{};

    ///////////////// 球 /////////////////
    float ballWidth{};
    float ballHeight{};
    float ballBeginPosX{};
    float ballBeginPosY{};
    b2BodyDef ballDef = b2DefaultBodyDef();
    b2ShapeDef ballShapeDef = b2DefaultShapeDef();
    b2BodyId ball{};
    b2Circle circle{};
    b2Polygon ballPolygon{};
    b2SurfaceMaterial ballSurfaceMaterial = b2DefaultSurfaceMaterial();

    sf::Texture ballTexture;

    float bounceTimer;
    const float bounceTime = 5.F; // 增加一段时间内若是球一直在地上，则可以自动弹起来

    ///////////////// 玩家 /////////////////
    float playerWidth{};
    float playerHeight{};
    float leftPlayerBeginX{};
    float rightPlayerBeginX{};
    float playerBeginY{};
    b2BodyDef playerDef = b2DefaultBodyDef();
    b2ShapeDef playerShapeDef = b2DefaultShapeDef();
    b2Polygon playerPolygon{};
    b2SurfaceMaterial playerSurfaceMaterial = b2DefaultSurfaceMaterial();
    b2BodyId leftPlayer{};
    b2BodyId rightPlayer{};

    sf::Texture playerTexture;

    ///////////////// 可动实体 /////////////////
    std::unique_ptr<Ball> volleyball;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;

    ///////////////// 字体显示 /////////////////
    sf::Font font;
    sf::Text remainingTimeText;
    const float remainingTime = 30.F;
    float remainingTimer{};
    sf::Text endText;
    int loser{0};
    const int fontSize = 26;
    float textY{};

public:
    GameWindow(const GameWindow &) = delete;
    GameWindow(GameWindow &&) = delete;
    GameWindow &operator=(const GameWindow &) = delete;
    GameWindow &operator=(GameWindow &&) = delete;
    explicit GameWindow(int windowWidth, int windowHeight, const std::wstring &title);
    ~GameWindow();
    void initB2World();
    void gameBegin(NetWorkManager &NetWorkManager);
};
