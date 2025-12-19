#pragma once

#include <SFML/Network.hpp>
#include <memory>

struct SEND_PACKET {
    uint16_t head = 0xaaaa;

    // 球
    int16_t ballPosX{};
    int16_t ballPosY{};
    int16_t ballRot{};
    // 左玩家
    int16_t leftPlayerPosX{};
    int16_t leftPlayerPosY{};
    int16_t leftPlayerRot{};
    // 右玩家
    int16_t rightPlayerPosX{};
    int16_t rightPlayerPosY{};
    int16_t rightPlayerRot{};

    // 是否按下重新开始游戏按键
    uint16_t restart{0};

    uint16_t foot = 0xbbbb;
};

struct RECEVIED_PACKET {
    uint16_t head = 0xcccc;

    // 右玩家按键
    int8_t moveDirection{0}; // -1 左 , 0 没横向移动 , 1 右
    uint8_t jump{0};         // 0 没 , 1 跳
    uint8_t restart{0};

    uint16_t foot = 0xdddd;
};

class NetWorkManager {
private:
    sf::TcpListener listener;
    unsigned short port;
    std::unique_ptr<sf::TcpSocket> client;

    // 右玩家按键缓存
    int8_t rightPlayerMoveDir{0};
    uint16_t rightPlayerJump{0};
    uint8_t restart{0};

public:
    NetWorkManager(const NetWorkManager &) = delete;
    NetWorkManager(NetWorkManager &&) = delete;
    NetWorkManager &operator=(const NetWorkManager &) = delete;
    NetWorkManager &operator=(NetWorkManager &&) = delete;
    explicit NetWorkManager(unsigned short port);
    ~NetWorkManager();
    sf::Socket::Status beginListen();
    bool addPlayer();
    void sendNewState(sf::Vector2f ballPos, sf::Vector2f leftPlayerPos, sf::Vector2f rightPlayerPos,
                      float ballRot, float leftPlayerRot, float rightPlayerRot);
    std::pair<int8_t, uint8_t> receiveButton();
    void restartGame();
    bool clientWantRestartGame();
    void initRestart();
};
