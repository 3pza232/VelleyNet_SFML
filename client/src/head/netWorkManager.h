#pragma once

#include <SFML/Network.hpp>
#include <cstdint>

struct SEND_PACKET {
    uint16_t head = 0xcccc;

    // 右玩家按键
    int8_t moveDirection{0}; // -1 左 , 0 没横向移动 , 1 右
    uint8_t jump{0};         // 0 没 , 1 跳
    uint8_t restart{0};

    uint16_t foot = 0xdddd;
};

struct RECEVIED_PACKET {
    uint16_t head = 0xaaaa;

    // 球
    int16_t ballPosX{};
    int16_t ballPosY{};
    int16_t ballAngle{};
    // 左玩家
    int16_t leftPlayerPosX{};
    int16_t leftPlayerPosY{};
    int16_t leftPlayerAngle{};
    // 右玩家
    int16_t rightPlayerPosX{};
    int16_t rightPlayerPosY{};
    int16_t rightPlayerAngle{};

    // 服务器是否按下重新开始游戏按键
    uint16_t restart{0};

    uint16_t foot = 0xbbbb;
};

class NetWorkManager {
private:
    sf::TcpSocket client;
    sf::IpAddress serverIP;
    unsigned short port;

    sf::Vector2f ballPos;
    float ballRot{};
    sf::Vector2f leftPlayerPos;
    float leftPlayerRot{};
    sf::Vector2f rightPlayerPos;
    float rightPlayerRot{};
    uint8_t restart{0};

public:
    NetWorkManager(const NetWorkManager &) = delete;
    NetWorkManager(NetWorkManager &&) = delete;
    NetWorkManager &operator=(const NetWorkManager &) = delete;
    NetWorkManager &operator=(NetWorkManager &&) = delete;
    explicit NetWorkManager(sf::IpAddress serverIP, unsigned short port);
    ~NetWorkManager();
    bool connectServer();
    void receivePosAndAngle();
    sf::Vector2f getBallPos();
    [[nodiscard]] float getBallRot() const;
    sf::Vector2f getLeftPlayerPos();
    [[nodiscard]] float getLeftPlayerRot() const;
    sf::Vector2f getRightPlayerPos();
    [[nodiscard]] float getRightPlayerRot() const;
    void sendButton(int8_t moveDir, uint8_t jump);
    bool serverWantRestartGame();
    void restartGame();
    void initRestart();
};
