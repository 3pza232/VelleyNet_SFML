#include "head/window.h"
#include <random>

void GameWindow::initB2World() {
    //////////////// 初始化世界 ////////////////
    worldDef.gravity = (b2Vec2){0, 9.8F};
    world = b2CreateWorld(&worldDef);

    //////////////// 地面/顶部 ////////////////
    groundHeight = 10.F;
    groundDef.type = b2_staticBody;
    groundPolygon = b2MakeBox((static_cast<float>(windowWidth) / 2.F) / PIXIVS_PER_METER,
                              (groundHeight / 2.F) / PIXIVS_PER_METER);
    ground = b2CreateBody(world, &groundDef);
    top = b2CreateBody(world, &groundDef);
    b2Body_SetTransform(
        ground,
        (b2Vec2){(static_cast<float>(windowWidth) / 2.F) / PIXIVS_PER_METER,
                 (static_cast<float>(windowHeight) + groundHeight / 2.F) / PIXIVS_PER_METER},
        (b2Rot){1, 0});
    b2Body_SetTransform(top,
                        (b2Vec2){(static_cast<float>(windowWidth) / 2.F) / PIXIVS_PER_METER,
                                 -(groundHeight / 2.F) / PIXIVS_PER_METER},
                        (b2Rot){1, 0});
    b2CreatePolygonShape(ground, &groundShapeDef, &groundPolygon);
    b2CreatePolygonShape(top, &groundShapeDef, &groundPolygon);

    //////////////// 墙 ////////////////
    wallWidth = 10;
    wallDef.type = b2_staticBody;
    leftWall = b2CreateBody(world, &wallDef);
    rightWall = b2CreateBody(world, &wallDef);
    wallPolygon = b2MakeBox((wallWidth / 2.F) / PIXIVS_PER_METER,
                            (static_cast<float>(windowHeight) / 2.F) / PIXIVS_PER_METER);
    b2Body_SetTransform(leftWall,
                        (b2Vec2){((-wallWidth) / 2.F) / PIXIVS_PER_METER,
                                 (static_cast<float>(windowHeight) / 2.F) / PIXIVS_PER_METER},
                        (b2Rot){1, 0});
    b2Body_SetTransform(
        rightWall,
        (b2Vec2){(static_cast<float>(windowWidth) + wallWidth / 2.F) / PIXIVS_PER_METER,
                 (static_cast<float>(windowHeight) / 2.F) / PIXIVS_PER_METER},
        (b2Rot){1, 0});
    b2CreatePolygonShape(leftWall, &wallShapeDef, &wallPolygon);
    b2CreatePolygonShape(rightWall, &wallShapeDef, &wallPolygon);

    //////////////// 球网 ////////////////
    ballNetDef.type = b2_staticBody;
    ballNetWidth = 10;
    ballNetHeight = 322;
    ballNetDef.position =
        (b2Vec2){(static_cast<float>(windowWidth) / 2.F) / PIXIVS_PER_METER,
                 (static_cast<float>(windowHeight) - ballNetHeight / 2.F) / PIXIVS_PER_METER};
    ballNet = b2CreateBody(world, &ballNetDef);
    ballNetPolygon = b2MakeBox((ballNetWidth / 2.F) / PIXIVS_PER_METER,
                               (ballNetHeight / 2.F) / PIXIVS_PER_METER);
    b2CreatePolygonShape(ballNet, &ballNetShapeDef, &ballNetPolygon);

    //////////////// 球 ////////////////
    ballWidth = 64;
    ballHeight = 64;
    ballBeginPosX = static_cast<float>(windowWidth) / 4.F / PIXIVS_PER_METER; // 球初始在左边位置
    ballBeginPosY = static_cast<float>(windowHeight) / 2.F / PIXIVS_PER_METER;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> whichFirst(0, 1);
    int firstOne = whichFirst(gen);
    if (firstOne == 1) {
        ballBeginPosX = static_cast<float>(windowWidth) * 0.75F / PIXIVS_PER_METER;
    }
    ballDef.position = (b2Vec2){ballBeginPosX, ballBeginPosY};
    ballDef.type = b2_dynamicBody;
    ballShapeDef.density = 0.8F;
    ballSurfaceMaterial.friction = 0.3F;
    ballSurfaceMaterial.restitution = 0.8F;
    ballShapeDef.material = ballSurfaceMaterial;
    circle.radius = 32.F / PIXIVS_PER_METER;

    //////////////// 玩家 ////////////////
    playerWidth = 75;
    playerHeight = 89;
    playerDef.type = b2_dynamicBody;
    leftPlayerBeginX = static_cast<float>(windowWidth) / 4.F / PIXIVS_PER_METER;
    rightPlayerBeginX = static_cast<float>(windowWidth) * 0.75F / PIXIVS_PER_METER;
    playerBeginY = (static_cast<float>(windowHeight) - playerHeight - 20.F) / PIXIVS_PER_METER;
    playerShapeDef.density = 1.F;
    playerSurfaceMaterial.friction = 0.3F;
    playerSurfaceMaterial.restitution = 0.4F;
    playerShapeDef.material = playerSurfaceMaterial;
    playerPolygon =
        b2MakeBox((playerWidth / 2.F) / PIXIVS_PER_METER, (playerHeight / 2.F) / PIXIVS_PER_METER);
    leftPlayer = b2CreateBody(world, &playerDef);
    rightPlayer = b2CreateBody(world, &playerDef);
    b2Body_SetTransform(leftPlayer, (b2Vec2){leftPlayerBeginX, playerBeginY}, (b2Rot){1, 0});
    b2Body_SetTransform(rightPlayer, (b2Vec2){rightPlayerBeginX, playerBeginY}, (b2Rot){1, 0});

    //////////////// 字体 ////////////////
    font.loadFromFile("resources/fonts/SourceHanSansSC-Normal-2.otf");
    remainingTimeText.setFont(font);
    remainingTimeText.setCharacterSize(fontSize);
    remainingTimeText.setFillColor(sf::Color::Red);
    remainingTimer = remainingTime;
    loser = 0;
    endText.setFont(font);
    endText.setCharacterSize(fontSize);
    endText.setFillColor(sf::Color::Red);
    endText.setString(L"你失败了!(按空格重新开始)");
    textY = static_cast<float>(windowHeight) * 0.25F;
}

GameWindow::GameWindow(int windowWidth, int windowHeight, const std::wstring &title)
    : windowWidth(windowWidth)
    , windowHeight(windowHeight)
    , bounceTimer(0) {
    window.create(sf::VideoMode(windowWidth, windowHeight), title, sf::Style::Default);
    window.setFramerateLimit(60);

    if (!backgroundTexture.loadFromFile("resources/images/background.PNG")) {
        throw "背景材质加载出错";
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setTextureRect(sf::IntRect(0, 0, windowWidth, windowHeight));

    initB2World(); // 初始化物理世界

    //////////////// 建立实体 ////////////////
    if (!ballTexture.loadFromFile("resources/images/ball.png")) {
        throw "球体材质加载失败";
    }
    volleyball = std::make_unique<Ball>(ballTexture, world, ballDef, ballShapeDef, circle);

    if (!playerTexture.loadFromFile("resources/images/blobby.png")) {
        throw "玩家材质加载失败";
    }
    player1 = std::make_unique<Player>(playerTexture, leftPlayer, playerShapeDef, playerPolygon, 1);
    player2 =
        std::make_unique<Player>(playerTexture, rightPlayer, playerShapeDef, playerPolygon, 2);
}

GameWindow::~GameWindow() = default;

void GameWindow::gameBegin(NetWorkManager &netWorkManager) {

    bool gameOver = false;

    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);

        if (!gameOver) {
            // 左侧玩家
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                player1->playerMoveToLeft();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                player1->playerMoveToRight();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                player1->playerJump();
            }

            // 右侧玩家
            std::pair<int8_t, uint8_t> rightPlayerButton = netWorkManager.receiveButton();
            if (rightPlayerButton.first == -1) {
                player2->playerMoveToLeft();
            } else if (rightPlayerButton.first == 1) {
                player2->playerMoveToRight();
            }
            if (rightPlayerButton.second == 1) {
                player2->playerJump();
            }

            b2World_Step(world, timeStep, subStepCount);

            if (bounceTimer >= bounceTime) {
                volleyball->bounceUp();
                bounceTimer = 0;
            }
            float ballY = volleyball->getPos().y;
            if (static_cast<float>(windowHeight) - ballY <= ballHeight / 2.F + 5.F) {
                bounceTimer += deltaTime;
                if (volleyball->getPos().x > static_cast<float>(windowWidth) / 2.F) {
                    loser = 2;
                } else {
                    loser = 1;
                }
            } else {
                bounceTimer = 0;
            }
            float ballX = volleyball->getPos().x;
            if ((loser == 1 && ballX >= static_cast<float>(windowWidth) / 2.F) ||
                (loser == 2 && ballX < static_cast<float>(windowWidth) / 2.F)) {
                loser = 0;
            }
            if (loser != 0) {
                remainingTimer -= deltaTime;
                if (remainingTimer < 0) {
                    gameOver = true;
                }
                std::wstring remainTimeString =
                    std::to_wstring(static_cast<int>(remainingTimer)) + L"s 后将会失败";
                remainingTimeText.setString(remainTimeString);
                float textX =
                    (static_cast<float>(windowWidth) / 2.F - endText.getLocalBounds().width) / 2.F;
                if (loser == 2) {
                    textX += static_cast<float>(windowWidth) / 2.F;
                }
                remainingTimeText.setPosition(sf::Vector2f(textX, textY));
                window.draw(remainingTimeText);
            } else {
                remainingTimer = remainingTime;
            }

            volleyball->updateAndDraw(window);
            player1->updateAndDraw(window);
            player2->updateAndDraw(window);

            netWorkManager.sendNewState(volleyball->getPos(), player1->getPos(), player2->getPos(),
                                        volleyball->getRot(), player1->getRot(), player2->getRot());
        } else {
            float textX =
                (static_cast<float>(windowWidth) / 2.F - endText.getLocalBounds().width) / 2.F;
            if (loser == 2) {
                textX += static_cast<float>(windowWidth) / 2.F;
            }
            endText.setPosition(sf::Vector2f(textX, textY));
            window.draw(endText);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
                netWorkManager.clientWantRestartGame()) {
                gameOver = false;
                netWorkManager.initRestart(); // 重置重启参数
                netWorkManager.restartGame(); // 通知客户端重启游戏

                initB2World(); // 初始化物理世界

                //////////////// 建立实体 ////////////////
                if (!ballTexture.loadFromFile("resources/images/ball.png")) {
                    throw "球体材质加载失败";
                }
                volleyball =
                    std::make_unique<Ball>(ballTexture, world, ballDef, ballShapeDef, circle);

                if (!playerTexture.loadFromFile("resources/images/blobby.png")) {
                    throw "玩家材质加载失败";
                }
                player1 = std::make_unique<Player>(playerTexture, leftPlayer, playerShapeDef,
                                                   playerPolygon, 1);
                player2 = std::make_unique<Player>(playerTexture, rightPlayer, playerShapeDef,
                                                   playerPolygon, 2);
            }
        }

        window.display();
    }

    b2DestroyWorld(world);
}
