#include "head/netWorkManager.h"
#include <iostream>

NetWorkManager::NetWorkManager(unsigned short port) : port(port) {}

NetWorkManager::~NetWorkManager() {
    listener.close();
    std::cout << "侦听停止，服务器关闭" << '\n';
}

sf::Socket::Status NetWorkManager::beginListen() {
    return listener.listen(port);
}

bool NetWorkManager::addPlayer() {
    client = std::make_unique<sf::TcpSocket>();
    sf::Socket::Status status = listener.accept(*client);
    if (status == sf::Socket::Status::Done) {
        client->setBlocking(false);
        return true;
    }
    return false;
}

void NetWorkManager::sendNewState(sf::Vector2f ballPos, sf::Vector2f leftPlayerPos,
                                  sf::Vector2f rightPlayerPos, float ballRot, float leftPlayerRot,
                                  float rightPlayerRot) {
    SEND_PACKET packet;
    packet.ballPosX = static_cast<int16_t>(ballPos.x);
    packet.ballPosY = static_cast<int16_t>(ballPos.y);
    packet.ballRot = static_cast<int16_t>(ballRot);
    packet.leftPlayerPosX = static_cast<int16_t>(leftPlayerPos.x);
    packet.leftPlayerPosY = static_cast<int16_t>(leftPlayerPos.y);
    packet.leftPlayerRot = static_cast<int16_t>(leftPlayerRot);
    packet.rightPlayerPosX = static_cast<int16_t>(rightPlayerPos.x);
    packet.rightPlayerPosY = static_cast<int16_t>(rightPlayerPos.y);
    packet.rightPlayerRot = static_cast<int16_t>(rightPlayerRot);

    client->setBlocking(true);
    sf::Socket::Status status = client->send(&packet, sizeof(packet));
    client->setBlocking(false);

    if (status == sf::Socket::Status::Disconnected) {
        std::cout << "客户端断开连接……" << '\n';
        sf::sleep(sf::milliseconds(1000));
        exit(1);
    }
}

std::pair<int8_t, uint8_t> NetWorkManager::receiveButton() {
    RECEVIED_PACKET packet;
    packet.head = 0xcccc;
    packet.foot = 0xdddd;
    std::size_t recevied = 0;

    sf::Socket::Status status = client->receive(&packet, sizeof(packet), recevied);

    if (status == sf::Socket::Status::Done) {
        rightPlayerMoveDir = packet.moveDirection;
        rightPlayerJump = packet.jump;
    }

    if (status == sf::Socket::Status::Disconnected) {
        std::cout << "客户端断开连接……" << '\n';
        sf::sleep(sf::milliseconds(1000));
        exit(1);
    }

    return {rightPlayerMoveDir, rightPlayerJump};
}

void NetWorkManager::restartGame() {
    SEND_PACKET packet;
    packet.restart = 1;
    client->setBlocking(true);
    sf::Socket::Status status = client->send(&packet, sizeof(packet));
    client->setBlocking(false);

    if (status == sf::Socket::Status::Disconnected) {
        std::cout << "客户端断开连接……" << '\n';
        sf::sleep(sf::milliseconds(1000));
        exit(1);
    }
}

bool NetWorkManager::clientWantRestartGame() {
    RECEVIED_PACKET packet;
    std::size_t recevied{0};
    sf::Socket::Status status = client->receive(&packet, sizeof(packet), recevied);

    if (status == sf::Socket::Status::Done) {
        restart = packet.restart;
    }
    if (status == sf::Socket::Status::Disconnected) {
        std::cout << "客户端断开连接……" << '\n';
        sf::sleep(sf::milliseconds(1000));
        exit(1);
    }

    return restart == 1;
}

void NetWorkManager::initRestart() {
    restart = 0;
}
