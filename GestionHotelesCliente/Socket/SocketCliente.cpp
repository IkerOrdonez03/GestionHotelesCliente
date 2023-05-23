#include <iostream>
#include <winsock2.h>

bool enviarCredenciales(SOCKET clientSocket, const std::string& usuario, const std::string& contrasena) {
    // Construir el mensaje a enviar al servidor
    std::string mensaje = usuario + "," + contrasena;

    // Enviar los datos al servidor
    int bytesEnviados = send(clientSocket, mensaje.c_str(), mensaje.length(), 0);
    if (bytesEnviados == SOCKET_ERROR) {
        std::cerr << "Error al enviar los datos al servidor." << std::endl;
        return false;    }

    return true;
}

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

    // Solicitar usuario y contraseña al usuario
    std::string usuario, contrasena;
    std::cout << "Ingrese el usuario: ";
    std::cin >> usuario;
    std::cout << "Ingrese la contrasena: ";
    std::cin >> contrasena;

    // Enviar credenciales al servidor
    if (enviarCredenciales(clientSocket, usuario, contrasena)) {
        std::cout << "Credenciales enviadas al servidor." << std::endl;
    } else {
        std::cerr << "Error al enviar las credenciales al servidor." << std::endl;
    }

    // Cerrar el socket y limpiar winsock
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
