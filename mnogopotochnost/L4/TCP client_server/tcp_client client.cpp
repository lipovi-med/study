#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib") // линковка с WinSock

using namespace std;

int main() {
    // 1. Инициализация WinSock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed" << endl;
        return 1;
    }

    // 2. Создание сокета
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        cerr << "Error creating socket" << endl;
        WSACleanup();
        return 1;
    }

    // 3. Адрес сервера
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000); // порт сервера
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    // 4. Подключение к серверу
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Failed to connect" << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    cout << "Connected to server!" << endl;

    // 5. Отправка строки
    const char* msg = "Hello, server!";
    send(sock, msg, (int)strlen(msg), 0);

    // 6. Получение ответа
    char buffer[512];
    int bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        cout << "Server reply: " << buffer << endl;
    }

    // 7. Закрытие сокета
    closesocket(sock);
    WSACleanup();

    return 0;
}
