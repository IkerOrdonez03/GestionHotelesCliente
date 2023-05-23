/*
 * SocketCliente.cpp
 *
 *  Created on: 23 may 2023
 *      Author: iker2
 */

#include <iostream>
#include <winsock2.h>

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error al inicializar winsock." << std::endl;
        return 1;
    }

    // Crear un socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error al crear el socket." << std::endl;
        WSACleanup();
        return 1;
    }

    // Configurar la dirección del servidor
    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Puerto del servidor
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Dirección IP del servidor

    // Conectar al servidor
    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) != 0) {
        std::cerr << "Error al conectar al servidor." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Envío y recepción de datos
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    // Enviar datos al servidor
    const char* message = "Hola, servidor!";
    send(clientSocket, message, strlen(message), 0);
    std::cout << "Mensaje enviado al servidor." << std::endl;

    // Recibir datos del servidor
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "Mensaje recibido del servidor: " << buffer << std::endl;
    }

    // Cerrar el socket y limpiar winsock
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}

