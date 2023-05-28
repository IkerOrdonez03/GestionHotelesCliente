#include <iostream>
#include <winsock2.h>
#include <sstream>
#include <string>
#include "../Clases/Provincias.h"
#include "../Clases/Hoteles.h"

bool recibirProvincias(SOCKET serverSocket, Provincias* provincias){
	// Definir un buffer para almacenar los datos recibidos
	const int bufferSize = 4000;
	char buffer[bufferSize];

	// Recibir los datos del cliente
	int bytesRecibidos = recv(serverSocket, buffer, bufferSize - 1, 0);
	if (bytesRecibidos == SOCKET_ERROR) {
		std::cerr << "Error al recibir los datos del servidor [1]." << std::endl;
		return false;
	}

	// Terminar el buffer con un carácter nulo
	buffer[bytesRecibidos] = '\0';

	// Parsear los datos recibidos separados por comas
	std::string datos(buffer);
	std::stringstream ss(datos);


	int numDatos;
	std::string numDatosS;
	std::getline(ss, numDatosS, ',');
	numDatos = std::stoi(numDatosS);
	provincias->numProvincias = numDatos;
	memset(provincias->provincias, 0, provincias->numProvincias * sizeof(Provincia));
	std::string nombre;
	const char* nombreCons;
	char* nombreChar;
	for (int n = 0; n < numDatos; ++n) {
		std::getline(ss, nombre, ',');
		// Convertir std::string a const char*
		nombreCons = nombre.c_str();
		// Convertir const char* a char* utilizando casting explícito
		nombreChar = const_cast<char*>(nombreCons);
		provincias[n].provincias->setNombre(nombreChar);
	}

	return true;
};
bool recibirHoteles(SOCKET serverSocket, Hoteles* hoteles, Provincia * provincia){
	// Definir un buffer para almacenar los datos recibidos
	const int bufferSize = 4000;
	char buffer[bufferSize];

	// Recibir los datos del cliente
	int bytesRecibidos = recv(serverSocket, buffer, bufferSize - 1, 0);
	if (bytesRecibidos == SOCKET_ERROR) {
		std::cerr << "Error al recibir los datos del servidor [2]." << std::endl;
		return false;
	}

	// Terminar el buffer con un carácter nulo
	buffer[bytesRecibidos] = '\0';

	// Parsear los datos recibidos separados por comas
	std::string datos(buffer);
	std::stringstream ss(datos);


	int numDatos;
	std::string numDatosS;
	std::getline(ss, numDatosS, ',');
	numDatos = std::stoi(numDatosS);
	hoteles->numHoteles = numDatos;
	memset(hoteles->hoteles, 0, hoteles->numHoteles* sizeof(Hotel));
	std::string nombreHotel;
	std::string nombreProvincia;
	const char* nombreHotelCons;
	const char* nombreProvinciaCons;
	char* nombreHotelChar;
	char* nombreProvinciaChar;
	std::string provYhotel;
	for (int n = 0; n < numDatos; ++n) {
		std::getline(ss, provYhotel, ',');
		std::getline(ss, nombreHotel, ':');
		std::getline(ss, nombreProvincia, ':');
		nombreHotelCons = nombreHotel.c_str();
		nombreProvinciaCons = nombreProvincia.c_str();
		nombreHotelChar = const_cast<char*>(nombreHotelCons);
		nombreProvinciaCons = nombreProvincia.c_str();
		nombreProvinciaChar = const_cast<char*>(nombreProvinciaCons);
		hoteles->hoteles[n].setNombre(nombreHotelChar);
		provincia->setNombre(nombreProvinciaChar);
		hoteles->hoteles[n].setProvincia(provincia);
	}
	return true;
};

void mostrarHoteles(Provincias* provincias, Hoteles* hoteles){
	int opcionProv;
	std::cout << "===============\nProvincias\n===============\n" << std::endl;
	for (int n= 0; n < provincias->numProvincias; ++n) {
		std::cout << n + 1 << " " << provincias->provincias[n].getNombre() << std::endl;
	}
	std::cout << "Opcion: ";
	std::cin >> opcionProv;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "===============\nHoteles\n===============\n" << std::endl;
	for (int n = 0; n < hoteles->numHoteles; ++n) {
		if (strcmp(hoteles->hoteles[n].getProvincia().getNombre(), provincias->provincias[opcionProv - 1].getNombre()) == 0) {
			std::cout << n + 1 << " " << hoteles->hoteles[n].getNombre();
		}
	}
}

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

bool enviarReservaACancelar(SOCKET clientSocket, const std::string& id_res) {
    // Enviar los datos al servidor
    int bytesEnviados = send(clientSocket, id_res.c_str(), id_res.length(), 0);
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

int menuPrincipal(){
	int opcionSeleccionada;
	std::cout << "===============\nPAGINA PRINCIPAL\n===============\n";
	std::cout << "Seleccione una opción:\n";
	std::cout << "1. Iniciar sesión\n";
	std::cout << "2. Registrar nuevo cliente\n";
	std::cout << "Opción: ";
	std::cin >> opcionSeleccionada;
	return opcionSeleccionada;
}

void menuIniciarSesion(std::string& usuario, std::string& contrasena) {
    std::cout << "===============\nINICIO SESION\n===============\n";
    std::cout << "Ingrese el usuario: ";
    std::cin >> usuario;
    std::cout << "Ingrese la contraseña: ";
    std::cin >> contrasena;
}

int menuGestion(){
	int opcionSeleccionada;
	std::cout << "===============================\nGESTIÓN DE GRAN RESORT FERRET\n===============================\n";
	std::cout << "Seleccione una opción:\n";
	std::cout << "1. Mostrar hotel\n";
	std::cout << "2. Hacer Reserva\n";
	std::cout << "3. Cancelar Reserva\n";
	std::cout << "4. Cerrar\n";
	std::cout << "Opción: ";
	std::cin >> opcionSeleccionada;
	return opcionSeleccionada;
}

void menuReserva(std::string& id_res, std::string& dia_ini, std::string& mes_ini, std::string& ano_ini, std::string& dia_fin, std::string& mes_fin,
		std::string& ano_fin, std::string& id_hab, std::string& dni){
	std::cout << "================\nREALIZAR RESERVA\n================\n";
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
}

void menuCancelarReserva(std::string& id_res){
	std::cout << "================\nCANCELAR RESERVA\n================\n";
	std::cout << "Introduzca el id de la reserva: ";
	std::cin >> id_res;
}

void menuRegistroCliente( std::string& dni, std::string& nombre,std::string& direccion ,std::string& telefono, std::string& usuario, std::string& contrasena){
	std::cout << "=========\nREGISTRO\n=========\n";
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
}

int main() {
	// INICIAR PROVINCIAS Y HOTELES

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
    int opcion = menuPrincipal();

    //OPTION 1
    if (opcion == 1) {
    	if(enviarOpcion(clientSocket, opcion)){
    		std::cout << "Opcion enviada al servidor." << std::endl;
		} else {
			std::cerr << "Error al enviar la opcion al servidor." << std::endl;
		}
        // Iniciar sesión

        std::string usuario, contrasena;
        menuIniciarSesion(usuario, contrasena);

        // Enviar credenciales al servidor
        if (enviarCredenciales(clientSocket, usuario, contrasena)) {
            std::cout << "Credenciales enviadas al servidor." << std::endl;

            // Menú después de iniciar sesión
            int opcion = menuGestion();

            //FUNCIONALIDAD
            if (opcion == 1) {
            	if(enviarOpcion(clientSocket, opcion)){
            		std::cout << "Opcion enviada al servidor." << std::endl;
            		Provincias* provincias;
            		Hoteles* hoteles;
            		Provincia* provincia;
            		if (recibirProvincias(clientSocket, provincias) && recibirHoteles(clientSocket, hoteles, provincia)){
            			mostrarHoteles(provincias, hoteles);
            		}
            	} else {
            		std::cerr << "Error al enviar la opcion al servidor." << std::endl;
            	}
            } else if (opcion == 2) {
            	if(enviarOpcion(clientSocket, opcion)){
        		std::cout << "Opcion enviada al servidor." << std::endl;
        		// Menú reserva
        		std::string id_res, dia_ini, mes_ini, ano_ini, dia_fin, mes_fin, ano_fin, id_hab, dni;
        		menuReserva(id_res, dia_ini, mes_ini, ano_ini, dia_fin, mes_fin, ano_fin, id_hab, dni);

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
        		std::string id;
        		menuCancelarReserva(id);
        		//enviar datos al servidor
				if ( enviarReservaACancelar(clientSocket, id) ) {
					std::cout << "Credenciales enviadas al servidor." << std::endl;


				} else {
					std::cerr << "Error al enviar la opcion al servidor." << std::endl;
				}

        	} else {
        		std::cerr << "Error al enviar la opcion al servidor." << std::endl;
        	}
        } else if (opcion == 4){
    		return 0;
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
        std::string dni, nombre, direccion, telefono, usuario, contrasena;
        menuRegistroCliente(dni, nombre, direccion, telefono, usuario, contrasena);

        // Enviar datos al servidor
        if (registrarCliente(clientSocket, dni, nombre, direccion, telefono, usuario, contrasena)) {
            std::cout << "Cliente registrado correctamente." << std::endl;

            // Menú después de iniciar sesión
			int opcion = menuGestion();

			//FUNCIONALIDAD
			if (opcion == 1) {
				if(enviarOpcion(clientSocket, opcion)){
					std::cout << "Opcion enviada al servidor." << std::endl;
					Provincias* provincias;
					Hoteles* hoteles;
					Provincia* provincia;
					if (recibirProvincias(clientSocket, provincias) && recibirHoteles(clientSocket, hoteles, provincia)){
						mostrarHoteles(provincias, hoteles);
					}
				} else {
					std::cerr << "Error al enviar la opcion al servidor." << std::endl;
				}
			} else if (opcion == 2) {
				if(enviarOpcion(clientSocket, opcion)){
				std::cout << "Opcion enviada al servidor." << std::endl;
				// Menú reserva
				std::string id_res, dia_ini, mes_ini, ano_ini, dia_fin, mes_fin, ano_fin, id_hab, dni;
				menuReserva(id_res, dia_ini, mes_ini, ano_ini, dia_fin, mes_fin, ano_fin, id_hab, dni);

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
				std::string id;
				menuCancelarReserva(id);
				//enviar datos al servidor
				if ( enviarReservaACancelar(clientSocket, id) ) {
					std::cout << "Credenciales enviadas al servidor." << std::endl;


				} else {
					std::cerr << "Error al enviar la opcion al servidor." << std::endl;
				}

			} else {
				std::cerr << "Error al enviar la opcion al servidor." << std::endl;
			}
		} else if (opcion == 4){
			return 0;
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
