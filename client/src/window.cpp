#include "head/ball.h"
#include "head/player.h"
#include "head/window.h"
#include <memory>

GameWindow::GameWindow(int windowWidth, int windowHeight, const std::wstring &title)
    : textY(static_cast<float>(windowHeight) * 0.25F) {
    window.create(sf::VideoMode(windowWidth, windowHeight), title, sf::Style::Default);
    window.setFramerateLimit(60);

    font.loadFromFile("resources/fonts/SourceHanSansSC-Normal-2.otf");
    remainingTimeText.setFont(font);
    remainingTimeText.setCharacterSize(fontSize);
    remainingTimeText.setFillColor(sf::Color::Red);
    endText.setFont(font);
    endText.setCharacterSize(fontSize);
    endText.setFillColor(sf::Color::Red);
    endText.setString(L"你失败了!(按enter键重新开始)");
}

GameWindow::~GameWindow() = default;

void GameWindow::gameBegin(NetWorkManager &netWorkManager) {
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("resources/images/background.PNG");
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Texture ballTexture;
    ballTexture.loadFromFile("resources/images/ball.png");
    std::unique_ptr<Ball> ball;
    ball = std::make_unique<Ball>(ballTexture);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("resources/images/blobby.png");
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    player1 = std::make_unique<Player>(playerTexture, 1);
    player2 = std::make_unique<Player>(playerTexture, 2);

    sf::Clock clock;
    bool gameOver = false;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);

        if (!gameOver) {
            netWorkManager.receivePosAndAngle();

            ball->setPosition(netWorkManager.getBallPos());
            ball->setRot(netWorkManager.getBallRot());
            player1->setPosition(netWorkManager.getLeftPlayerPos());
            player1->setRot(netWorkManager.getLeftPlayerRot());
            player2->setPosition(netWorkManager.getRightPlayerPos());
            player2->setRot(netWorkManager.getRightPlayerRot());

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                moveDir = -1;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                moveDir = 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                jump = 1;
            }
            netWorkManager.sendButton(moveDir, jump);
            moveDir = 0;
            jump = 0;

            ball->draw(window);
            player1->draw(window);
            player2->draw(window);

            if ((ball->getPos().x < static_cast<float>(window.getSize().x) / 2.F) &&
                (static_cast<float>(window.getSize().y) - ball->getPos().y) <= 37.F) {
                loser = 1;
            } else if ((ball->getPos().x > static_cast<float>(window.getSize().x) / 2.F) &&
                       (static_cast<float>(window.getSize().y) - ball->getPos().y) <= 37.F) {
                loser = 2;
            }
            float ballX = ball->getPos().x;
            if ((loser == 1 && ballX >= static_cast<float>(window.getSize().x) / 2.F) ||
                (loser == 2 && ballX < static_cast<float>(window.getSize().x) / 2.F)) {
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
                float textX = (static_cast<float>(window.getSize().x) / 2.F -
                               endText.getLocalBounds().width) /
                              2.F;
                if (loser == 2) {
                    textX += static_cast<float>(window.getSize().x) / 2.F;
                }
                remainingTimeText.setPosition(sf::Vector2f(textX, textY));
                window.draw(remainingTimeText);
            } else {
                remainingTimer = remainingTime;
            }
        } else {
            float textX =
                (static_cast<float>(window.getSize().x) / 2.F - endText.getLocalBounds().width) /
                2.F;
            if (loser == 2) {
                textX += static_cast<float>(window.getSize().x) / 2.F;
            }
            endText.setPosition(sf::Vector2f(textX, textY));
            window.draw(endText);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
                netWorkManager.serverWantRestartGame()) {
                gameOver = false;
                netWorkManager.restartGame();
                loser = 0;
                remainingTimer = remainingTime;
                netWorkManager.initRestart(); // 重置重启参数
            }
        }

        window.display();
    }
}
