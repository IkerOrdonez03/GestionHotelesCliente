#include <iostream>
#include "../bd/sqlite3.h"
#include "../bd/base_datos.h"
#include <winsock2.h>
#include <sstream>
static int opcionElegida;

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

bool registrarCliente(SOCKET clientSocket, const std::string& dni, const std::string& nombre, const std::string& direccion, const std::string& telefono, const std::string& usuario, const std::string& contrasena, sqlite3* db) {
	// Insertar cliente en la base de datos
    int result = insertarCliente(dni, nombre, direccion, telefono, usuario, contrasena, db);
    if (result != SQLITE_OK) {
        std::cerr << "Error al registrar el cliente en la base de datos." << std::endl;
        return false;
    }

    // Enviar respuesta al cliente
    std::string respuesta = "Cliente registrado correctamente.";
    int bytesEnviados = send(clientSocket, respuesta.c_str(), respuesta.length(), 0);
    if (bytesEnviados == SOCKET_ERROR) {
        std::cerr << "Error al enviar la respuesta al cliente." << std::endl;
        return false;
    }
    return true;
}

bool recibirOpcion(SOCKET clientSocket, int opcion) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    // Enviar los datos al servidor
	int bytesRecibidos = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRecibidos == SOCKET_ERROR) {
        std::cerr << "Error al recibir los datos del cliente." << std::endl;
        return false;
    }

    std::string datosRecibidos(buffer);

    sscanf(datosRecibidos.c_str(), "%d", &opcion);
    opcionElegida = opcion;
    return true;
}

bool recibirCliente(SOCKET serverSocket, std::string& dni, std::string& nombre, std::string& direccion, std::string& telefono, std::string& usuario, std::string& contrasena) {
    // Definir un buffer para almacenar los datos recibidos
    const int bufferSize = 3000;
    char buffer[bufferSize];

    // Recibir los datos del cliente
    int bytesRecibidos = recv(serverSocket, buffer, bufferSize - 1, 0);
    if (bytesRecibidos == SOCKET_ERROR) {
        std::cerr << "Error al recibir los datos del cliente." << std::endl;
        return false;
    }

    // Terminar el buffer con un carácter nulo
    buffer[bytesRecibidos] = '\0';

    // Parsear los datos recibidos separados por comas
    std::string datos(buffer);
    std::stringstream ss(datos);

    std::getline(ss, dni, ',');
    std::getline(ss, nombre, ',');
    std::getline(ss, direccion, ',');
    std::getline(ss, telefono, ',');
    std::getline(ss, usuario, ',');
    std::getline(ss, contrasena, ',');

    return true;
}



int main() {
	//INICIALIZACION DE LA BD
	sqlite3 * db;
	int result = sqlite3_open("bd/hotel.sqlite", &db);
	if (result != SQLITE_OK) {
		std::cout << "Error opening database";
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

    std::cout << "Servidor iniciado. Esperando conexiones..." << std::endl;

    while (true) {
        // Aceptar una conexión entrante
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error al aceptar la conexión entrante." << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }
        if (recibirOpcion(clientSocket, opcionElegida)){
        	std::cout << "Opcion: " << opcionElegida << std::endl;
        	if (opcionElegida == 1){
        		// Recibir credenciales del cliente
				std::string usuario, contrasena;
				if (recibirCredenciales(clientSocket, usuario, contrasena)) {
					// Convertir std::string a const char*
					const char* usuarioCharCons = usuario.c_str();
					const char* contrasenaCharCons = contrasena.c_str();
					// Convertir const char* a char* utilizando casting explícito
					char* usuarioChar = const_cast<char*>(usuarioCharCons);
					char* contrasenaChar = const_cast<char*>(contrasenaCharCons);
					std::cout << "Credenciales recibidas del cliente:" << std::endl;
					std::cout << "Usuario: " << usuario << std::endl;
					std::cout << "Contraseña: " << contrasena << std::endl;

					// lógica de autenticación del usuario
					int value = validaCliente(usuarioChar, contrasenaChar, db);
					if (value == 0){
						// Ejemplo de respuesta al cliente
						std::string respuesta = "Autenticación exitosa"; // Cambia esto según tu lógica de autenticación
						std::cout << respuesta << std::endl;
					} else {
						std::string respuesta = "Autenticación erronea";
						std::cout << respuesta << std::endl;
					}
					// ...

				} else {
					std::cerr << "Error al recibir las credenciales del cliente." << std::endl;
				}
        	} else if (opcionElegida == 2){
        		std::string dni, nombre, direccion, telefono, usuario, contrasena;
        		//Recibir datos servidor
        		if (recibirCliente(clientSocket, dni, nombre, direccion, telefono, usuario, contrasena)){
					if (registrarCliente(clientSocket, dni, nombre, direccion, telefono, usuario, contrasena, db)){
						std::cout << "Usuario: " << dni << ", " << nombre << ", " << usuario << ". " << "Registrado correctamente" << std::endl;
					} else {
						std::cout << "Usuario: " << dni << ", " << nombre << ", " << usuario << ". " << "Registrado incorrectamente" << std::endl;
					}
        		} else {
        			std::cout << "Registro incorrecto de Usuario: " << usuario << std::endl;
        		}
        	}
        else {}
        }



        // Cerrar el socket del cliente
        closesocket(clientSocket);
    }
    //CERRAR LA BD
	result = sqlite3_close(db);
	if (result != SQLITE_OK) {
		logMensaje(strcat("\nError closing database", sqlite3_errmsg(db)));
		return result;
	}
	logMensaje("\nDatabase closed");
    // Cerrar el socket del servidor y limpiar winsock
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
