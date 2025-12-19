#pragma once

#include "netWorkManager.h"
#include <SFML/Graphics.hpp>

class GameWindow {
private:
    sf::RenderWindow window;

    int8_t moveDir{0};
    uint8_t jump{0};

    ///////////////// 字体显示 /////////////////
    sf::Font font;
    sf::Text remainingTimeText;
    const float remainingTime = 30.F;
    float remainingTimer{remainingTime};
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
    void gameBegin(NetWorkManager &netWorkManager);
};
