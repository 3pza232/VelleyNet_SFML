#include "head/netWorkManager.h"
#include "head/window.h"
#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(65001);
    std::cout << "请输入服务器IP地址：";
    std::string serverIP{};
    std::cin >> serverIP;
    std::cout << "请输入服务器端口号：";
    unsigned short port{};
    std::cin >> port;
    NetWorkManager netWorkManager(serverIP, port);
    std::cout << "正在连接服务器……" << '\n';
    while (!netWorkManager.connectServer()) {
        sf::sleep(sf::milliseconds(1000));
    }
    GameWindow window(800, 600, L"沙滩排球");
    window.gameBegin(netWorkManager);
}
