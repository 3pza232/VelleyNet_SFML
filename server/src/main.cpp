#include "head/netWorkManager.h"
#include "head/window.h"
#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(65001);
    std::cout << "请输入一个空闲的端口号以进行游戏：";
    unsigned short port{};
    std::cin >> port;
    NetWorkManager netWorkManager(port);
    std::cout << "！客户端输入本机IP和端口号来进行游戏……" << port << '\n';
    std::cout << "开始侦听端口：" << port << '\n';
    if (netWorkManager.beginListen() != sf::Socket::Status::Done) {
        std::cout << "侦听端口：" << port << " 失败，端口可能被占用" << '\n';
        return -1;
    }
    while (!netWorkManager.addPlayer()) {
        sf::sleep(sf::milliseconds(1000));
    }

    GameWindow window(800, 600, L"沙滩排球");
    window.gameBegin(netWorkManager);
}
