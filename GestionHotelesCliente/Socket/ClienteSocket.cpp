#include <iostream>
#include <winsock2.h>
#include <vector>
#include <string>

#pragma comment(lib, "ws2_32.lib") // Enlaza con la biblioteca ws2_32.lib

// Definir una estructura para representar un hotel
struct Hotel {
    std::string nombre;
    std::string direccion;
    std::string ciudad;
};

std::vector<Hotel> obtenerHoteles() {
    // Aquí deberías realizar la conexión a la base de datos y obtener los hoteles
    // Puedes simularlo con datos estáticos para este ejemplo
    std::vector<Hotel> hoteles;
    hoteles.push_back({"Hotel A", "Dirección A", "Ciudad A"});
    hoteles.push_back({"Hotel B", "Dirección B", "Ciudad B"});
    hoteles.push_back({"Hotel C", "Dirección C", "Ciudad C"});
    return hoteles;
}

int main() {
    // Inicializar Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error al inicializar Winsock" << std::endl;
        return 1;
    }

    // Crear un socket para el servidor
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error al crear el socket del servidor" << std::endl;
        WSACleanup();
        return 1;
    }

    // Configurar la dirección del servidor
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345); // Puerto a utilizar
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Enlazar el socket con la dirección del servidor
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error al enlazar el socket" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Escuchar conexiones entrantes
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error al escuchar en el socket" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "El servidor está esperando conexiones entrantes..." << std::endl;

    // Aceptar una conexión entrante
    SOCKET clientSocket;
    sockaddr_in clientAddress;
    int clientAddressSize = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error al aceptar la conexión" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Se ha establecido una conexión con un cliente" << std::endl;

    // Obtener los hoteles de la base de datos
    std::vector<Hotel> hoteles = obtenerHoteles();

    // Enviar los hoteles al cliente
    for (const auto& hotel : hoteles) {
        // Convertir la estructura del hotel a una cadena de texto
        std::string hotelStr = hotel.nombre + ";" + hotel.direccion + ";" + hotel.ciudad;

        // Enviar los datos al cliente
        if (send(clientSocket, hotelStr.c_str(), hotelStr.length(), 0) == SOCKET_ERROR) {
            std::cerr << "Error al enviar datos al cliente" << std::endl;
            closesocket(clientSocket);
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }
    }

    // Cerrar los sockets y limpiar Winsock
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}

