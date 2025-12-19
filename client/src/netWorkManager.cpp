#include "head/netWorkManager.h"
#include <iostream>

NetWorkManager::NetWorkManager(sf::IpAddress serverIP, unsigned short port)
    : serverIP(serverIP)
    , port(port) {}

NetWorkManager::~NetWorkManager() = default;

bool NetWorkManager::connectServer() {
    sf::Socket::Status status = client.connect(serverIP, port);
    if (status == sf::Socket::Status::Done) {
        client.setBlocking(false);
        return true;
    }
    return false;
}

void NetWorkManager::receivePosAndAngle() {
    RECEVIED_PACKET packet;
    std::size_t recevied{0};
    sf::Socket::Status status = client.receive(&packet, sizeof(packet), recevied);
    if (status == sf::Socket::Status::Done) {
        ballPos.x = packet.ballPosX;
        ballPos.y = packet.ballPosY;
        ballRot = packet.ballAngle;
        leftPlayerPos.x = packet.leftPlayerPosX;
        leftPlayerPos.y = packet.leftPlayerPosY;
        leftPlayerRot = packet.leftPlayerAngle;
        rightPlayerPos.x = packet.rightPlayerPosX;
        rightPlayerPos.y = packet.rightPlayerPosY;
        rightPlayerRot = packet.rightPlayerAngle;
    } else if (status == sf::Socket::Disconnected) {
        std::cout << "服务器已断开连接……" << '\n';
        sf::sleep(sf::milliseconds(1000));
        exit(1);
    }
}

sf::Vector2f NetWorkManager::getBallPos() {
    return ballPos;
}
float NetWorkManager::getBallRot() const {
    return ballRot;
}
sf::Vector2f NetWorkManager::getLeftPlayerPos() {
    return leftPlayerPos;
}
float NetWorkManager::getLeftPlayerRot() const {
    return leftPlayerRot;
}
sf::Vector2f NetWorkManager::getRightPlayerPos() {
    return rightPlayerPos;
}
float NetWorkManager::getRightPlayerRot() const {
    return rightPlayerRot;
}

void NetWorkManager::sendButton(int8_t moveDir, uint8_t jump) {
    SEND_PACKET packet;
    packet.moveDirection = moveDir;
    packet.jump = jump;
    client.setBlocking(true);
    sf::Socket::Status status = client.send(&packet, sizeof(packet));
    client.setBlocking(false);
    if (status == sf::Socket::Disconnected) {
        std::cout << "服务器已断开连接……" << '\n';
        sf::sleep(sf::milliseconds(1000));
        exit(1);
    }
}

bool NetWorkManager::serverWantRestartGame() {
    RECEVIED_PACKET packet;
    std::size_t recevied{0};
    sf::Socket::Status status = client.receive(&packet, sizeof(packet), recevied);
    if (status == sf::Socket::Status::Done) {
        restart = packet.restart;
    }
    if (status == sf::Socket::Disconnected) {
        std::cout << "服务器已断开连接……" << '\n';
        sf::sleep(sf::milliseconds(1000));
        exit(1);
    }
    return restart == 1;
}

void NetWorkManager::restartGame() {
    SEND_PACKET packet;
    packet.restart = 1;
    client.setBlocking(true);
    sf::Socket::Status status = client.send(&packet, sizeof(packet));
    client.setBlocking(false);
    if (status == sf::Socket::Disconnected) {
        std::cout << "服务器已断开连接……" << '\n';
        sf::sleep(sf::milliseconds(1000));
        exit(1);
    }
}

void NetWorkManager::initRestart() {
    restart = 0;
}
