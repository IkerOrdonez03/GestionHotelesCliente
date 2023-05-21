#ifndef CLASES_RESERVA_H_
#define CLASES_RESERVA_H_

class Reserva {
	int id;
	int dia_ini;
	int mes_ini;
	int ano_ini;
	int dia_fin;
	int mes_fin;
	int ano_fin;
	int id_hab;
	int dni_cliente;

public:
	Reserva(int id, int dia_ini, int mes_ini, int ano_ini, int dia_fin, int mes_fin, int ano_fin, int id_hab, int dni_cliente);
	Reserva(const Reserva &r);
	virtual ~Reserva();

	int getId();
	int getDia_Ini();
	int getMes_Ini();
	int getAno_Ini();
	int getDia_Fin();
	int getMes_Fin();
	int getAno_Fin();
	int getIdHab();
	int getDniCliente();
};

#endif
