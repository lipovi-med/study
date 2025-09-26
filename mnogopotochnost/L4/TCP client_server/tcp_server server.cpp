#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

void handle_client(SOCKET clientSocket) {
    char buffer[512];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        cout << "Received from client: " << buffer << endl;

        // Отправка ответа
        const char* reply = "Hello, client!";
        send(clientSocket, reply, (int)strlen(reply), 0);
    }
    closesocket(clientSocket);
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(listenSocket, SOMAXCONN);

    cout << "Server listening on port 54000..." << endl;

    while (true) {
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket != INVALID_SOCKET) {
            // Создаём поток для каждого клиента
            thread t(handle_client, clientSocket);
            t.detach(); // отделяем поток
        }
    }

    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
