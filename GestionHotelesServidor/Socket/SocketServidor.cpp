#include <iostream>
#include <winsock2.h>
#include "../bd/base_datos.h"


bool recibirCredenciales(SOCKET clientSocket, std::string& usuario, std::string& contrasena) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    // Recibir los datos del cliente
    int bytesRecibidos = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRecibidos == SOCKET_ERROR) {
        std::cerr << "Error al recibir los datos del cliente." << std::endl;
        return false;
    }

    // Parsear los datos recibidos (usuario,contrasena)
    std::string datosRecibidos(buffer);
    size_t comaPos = datosRecibidos.find(",");
    if (comaPos == std::string::npos) {
        std::cerr << "Datos recibidos inválidos." << std::endl;
        return false;
    }

    usuario = datosRecibidos.substr(0, comaPos);
    contrasena = datosRecibidos.substr(comaPos + 1);

    return true;
}

int main() {
	//INICIALIZACION DE LA BD
	sqlite3 * db;
	int result = sqlite3_open("bd/hotel.sqlite", &db);
	if (result != SQLITE_OK) {
		std::cout << "Error opening database\n";
	} else {
		std::cout << "Opened database\n";
	}

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error al inicializar winsock." << std::endl;
        return 1;
    }

    // Crear un socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error al crear el socket." << std::endl;
        WSACleanup();
        return 1;
    }

    // Configurar la dirección del servidor
    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Puerto del servidor
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Dirección IP del servidor (se aceptan conexiones en todas las interfaces)

    // Vincular el socket a la dirección del servidor
    if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error al vincular el socket." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Escuchar conexiones entrantes
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error al escuchar conexiones entrantes." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Aceptar una conexión entrante
    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error al aceptar la conexión entrante." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Recibir credenciales del cliente
    std::string usuario, contrasena;
    // Convertir std::string a const char*
    const char* usuarioCharCons = usuario.c_str();
    const char* contrasenaCharCons = contrasena.c_str();
    // Convertir const char* a char* utilizando casting explícito
    char* usuarioChar = const_cast<char*>(usuarioCharCons);
    char* contrasenaChar = const_cast<char*>(contrasenaCharCons);

    if (recibirCredenciales(clientSocket, usuario, contrasena)) {

    	if(validadAdmin(usuarioChar, contrasenaChar, db) == 0) {
    		std::cout << "Credenciales recibidas del cliente:" << std::endl;
    		std::cout << "Usuario: " << usuario << std::endl;
    		std::cout << "Contrasena: " << contrasena << std::endl;
    	}

    } else {
        std::cerr << "Error al recibir las credenciales del cliente." << std::endl;
    }


    // Cerrar los sockets y limpiar winsock
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    //CERRAR LA BD
    result = sqlite3_close(db);
    if (result != SQLITE_OK) {
    	std::cout << "Error closing database";
    	return result;
    }
    std::cout << "\nDatabase closed";

    return 0;
}
