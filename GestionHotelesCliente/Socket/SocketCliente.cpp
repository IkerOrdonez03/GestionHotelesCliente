#include <iostream>
#include <winsock2.h>

bool enviarCredenciales(SOCKET clientSocket, const std::string& usuario, const std::string& contrasena) {
    // Construir el mensaje a enviar al servidor
    std::string mensaje = usuario + "," + contrasena;

    // Enviar los datos al servidor
    int bytesEnviados = send(clientSocket, mensaje.c_str(), mensaje.length(), 0);
    if (bytesEnviados == SOCKET_ERROR) {
        std::cerr << "Error al enviar los datos al servidor." << std::endl;
        return false;
    }
    return true;
}

bool enviarReserva(SOCKET clientSocket, const std::string&id_res, const std::string&dia_ini, const std::string&mes_ini, const std::string&ano_ini,
		const std::string&dia_fin, const std::string&mes_fin, const std::string&ano_fin, const std::string&id_hab, const std::string&dni) {
    // Construir el mensaje a enviar al servidor
    std::string mensaje = id_res + "," + dia_ini + "," + mes_ini + "," + ano_ini + "," + dia_fin + "," + mes_ini +
    		+ "," + ano_ini + "," + dia_fin + "," + mes_fin + "," + ano_fin + "," + id_hab + "," + dni;
    // Enviar los datos al servidor
    int bytesEnviados = send(clientSocket, mensaje.c_str(), mensaje.length(), 0);
    if (bytesEnviados == SOCKET_ERROR) {
        std::cerr << "Error al enviar los datos al servidor." << std::endl;
        return false;
    }
    return true;
}

bool enviarOpcion(SOCKET clientSocket, int opcion) {
    // Construir el mensaje a enviar al servidor
	std::string mensaje = std::to_string(opcion);

    // Enviar los datos al servidor
    int bytesEnviados = send(clientSocket, mensaje.c_str(), mensaje.length(), 0);
    if (bytesEnviados == SOCKET_ERROR) {
        std::cerr << "Error al enviar los datos al servidor." << std::endl;
        return false;
    }

    return true;
}

bool registrarCliente(SOCKET clientSocket, const std::string& dni, const std::string& nombre, const std::string& direccion, const std::string& telefono, const std::string& usuario, const std::string& contrasena) {
    // Construir el mensaje a enviar al servidor
    std::string mensaje = dni + "," + nombre + "," + direccion + "," + telefono + "," + usuario + "," + contrasena;

    // Enviar los datos al servidor
    int bytesEnviados = send(clientSocket, mensaje.c_str(), mensaje.length(), 0);
    if (bytesEnviados == SOCKET_ERROR) {
        std::cerr << "Error al enviar los datos al servidor." << std::endl;
        return false;
    }
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

    // Menú de opciones
    int opcion;
    std::cout << "===============\nPAGINA PRINCIPAL\n===============\n";

    std::cout << "Seleccione una opción:\n";
    std::cout << "1. Iniciar sesión\n";
    std::cout << "2. Registrar nuevo cliente\n";
    std::cout << "Opción: ";
    std::cin >> opcion;

    //OPTION 1
    if (opcion == 1) {
    	if(enviarOpcion(clientSocket, opcion)){
    		std::cout << "Opcion enviada al servidor." << std::endl;
		} else {
			std::cerr << "Error al enviar la opcion al servidor." << std::endl;
		}
        // Iniciar sesión
    	std::cout << "===============\nINICIO SESION\n===============\n";
        std::string usuario, contrasena;
        std::cout << "Ingrese el usuario: ";
        std::cin >> usuario;
        std::cout << "Ingrese la contraseña: ";
        std::cin >> contrasena;

        // Enviar credenciales al servidor
        if (enviarCredenciales(clientSocket, usuario, contrasena)) {
            std::cout << "Credenciales enviadas al servidor." << std::endl;

            // Menú después de iniciar sesión
            std::cout << "===============================\nGESTIÓN DE GRAN RESORT FERRET\n===============================\n";
            std::cout << "Seleccione una opción:\n";
            std::cout << "1. Mostrar hotel\n";
            std::cout << "2. Hacer Reserva\n";
            std::cout << "3. Cancelar Reserva\n";
            std::cout << "Opción: ";
            std::cin >> opcion;

            //FUNCIONALIDAD
            if (opcion == 1) {
            	if(enviarOpcion(clientSocket, opcion)){
            		std::cout << "Opcion enviada al servidor." << std::endl;
//            		mostrarHoteles();
            	} else {
            		std::cerr << "Error al enviar la opcion al servidor." << std::endl;
            	}
            } else if (opcion == 2) {
            	if(enviarOpcion(clientSocket, opcion)){
        		std::cout << "Opcion enviada al servidor." << std::endl;
        		// Menú reserva
        		std::cout << "================\nREALIZAR RESERVA\n================\n";
        		std::string id_res, dia_ini, mes_ini, ano_ini, dia_fin, mes_fin, ano_fin, id_hab, dni;
        		std::cout << "Introduzca el id de la reserva: ";
				std::cin >> id_res;
				std::cout << "Introduzca el dia inicio: ";
				std::cin >> dia_ini;
				std::cout << "Introduzca el mes inicio: ";
				std::cin >> mes_ini;
				std::cout << "Introduzca el ano inicio: ";
				std::cin >> ano_ini;
				std::cout << "Introduzca el dia final: ";
				std::cin >> dia_fin;
				std::cout << "Introduzca el mes final: ";
				std::cin >> mes_fin;
				std::cout << "Introduzca el ano final: ";
				std::cin >> ano_fin;
				std::cout << "Introduzca el id de la habitacion: ";
				std::cin >> id_hab;
				std::cout << "Introduzca su dni: ";
				std::cin >> dni;

				//enviar datos al servidor
				if ( enviarReserva(clientSocket, id_res, dia_ini, mes_ini, ano_ini,
						dia_fin, mes_fin, ano_fin, id_hab, dni) ) {
					std::cout << "Credenciales enviadas al servidor." << std::endl;

				} else {
					std::cerr << "Error al enviar la opcion al servidor." << std::endl;
				}
            }
        } else if (opcion == 3) {
        	if(enviarOpcion(clientSocket, opcion)){
        		std::cout << "Opcion enviada al servidor." << std::endl;
//        		eliminarReserva();
        	} else {
        		std::cerr << "Error al enviar la opcion al servidor." << std::endl;
        	}
        } else {
        	std::cerr << "Opción inválida." << std::endl;
        }

    } else {
    	std::cerr << "Error al enviar las credenciales al servidor." << std::endl;
    }

    //OPTION 2
    } else if (opcion == 2) {
    	if(enviarOpcion(clientSocket, opcion)){
			std::cout << "Opcion enviada al servidor." << std::endl;
		} else {
			std::cerr << "Error al enviar la opcion al servidor." << std::endl;
		}
        // Registrar un nuevo cliente
    	std::cout << "=========\nREGISTRO\n=========\n";
        std::string dni, nombre, direccion, telefono, usuario, contrasena;
        std::cin.ignore();
        std::cout << "Ingrese el DNI: ";
        std::getline(std::cin, dni);
        std::cout << "Ingrese el nombre: ";
        std::getline(std::cin, nombre);
        std::cout << "Ingrese la dirección: ";
        std::getline(std::cin, direccion);
        std::cout << "Ingrese el teléfono: ";
        std::getline(std::cin, telefono);
        std::cout << "Ingrese el nombre de usuario: ";
        std::getline(std::cin, usuario);
        std::cout << "Ingrese la contrasena de usuario: ";
        std::getline(std::cin, contrasena);

        // Enviar datos al servidor
        if (registrarCliente(clientSocket, dni, nombre, direccion, telefono, usuario, contrasena)) {
            std::cout << "Cliente registrado correctamente." << std::endl;

            // Menú después de registrarse
            std::cout << "===============================\nGESTIÓN DE GRAN RESORT FERRET\n===============================\n";
            std::cout << "Seleccione una opción:\n";
            std::cout << "1. Mostrar hotel\n";
            std::cout << "2. Hacer Reserva\n";
            std::cout << "3. Cancelar Reserva\n";
            std::cout << "Opción: ";
            std::cin >> opcion;

//            FUNCIONALIDAD
			if (opcion == 1) {
//				mostrarHoteles();
			} else if (opcion == 2) {
//				hacerReserva();
			} else if (opcion == 3) {
//				cancelarReserva();
			} else {
				std::cerr << "Opción inválida." << std::endl;
			}

        } else {
            std::cerr << "Error al registrar el cliente." << std::endl;
        }
    } else {
        std::cerr << "Opción inválida." << std::endl;
    }

    // Cerrar el socket y limpiar winsock
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
