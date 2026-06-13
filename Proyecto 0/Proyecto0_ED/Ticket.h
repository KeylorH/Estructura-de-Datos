#pragma once
#include <String>
#include <sstream> // Flujos de texto
#include <ctime>
#include <iomanip>

using std::string;
using std::ostream;
using std::time_t;
using std::stringstream;



class Ticket
{
private:
	string tipoUsser;
	string servicio;
	int prioridadFinal;
	string codigo;
	time_t horaTickSolici; // Guardará los componentes de la hora para sacar el tiempo de espera
	tm horaSolicitud; // Especificamente para imprimirlo

public:
	Ticket() {
		prioridadFinal = 50;
	}
	Ticket(string codigo, string tipoUsser, string servicio, int prioridadFinal) {
		this->codigo = codigo;
		this->tipoUsser = tipoUsser;
		this->servicio = servicio;
		this->prioridadFinal = prioridadFinal;
		this->horaTickSolici = time(0); // Saca la hora
		localtime_s(&horaSolicitud, &horaTickSolici); // Guarda la hora en un formato aceptable para la posterior impresion
		
	}
	void operator=(const Ticket& other) {
		tipoUsser = other.tipoUsser;
		servicio = other.servicio;
		prioridadFinal = other.prioridadFinal;
		codigo = other.codigo;
	}

	// Operadores de comparación ------------------------
	bool operator==(const Ticket& other) {
		return codigo == other.codigo;
	}

	bool operator<(const Ticket& other) {
		return prioridadFinal < other.prioridadFinal;
	}

	bool operator<=(const Ticket& other) {
		return prioridadFinal <= other.prioridadFinal;
	}

	bool operator>(const Ticket& other) {
		return prioridadFinal > other.prioridadFinal;
	}

	bool operator>=(const Ticket& other) {
		return prioridadFinal >= other.prioridadFinal;
	}

	// Metodos get -------------------------------------------
	int getPrioridadFinal() const {
		return prioridadFinal;
	}
	string getTipoUsser() const {
		return tipoUsser;
	}
	string getServicio() const {
		return servicio;
	}
	string getCodigo() const {
		return codigo;
	}
	time_t gethoraTicketSolici() const{
		return horaTickSolici;
	}
	string getHoraTickSolicitud() const{
		stringstream ss; // Para que almacene los string que componen la hora
		ss << std::put_time(&horaSolicitud, "%c"); // put_time formatea la hora con el formato del sistema
		return ss.str(); // str invoca todo lo que se guardó en ss
		// Idea inspirado en https://en.cppreference.com/w/cpp/io/manip/put_time
	}

};

ostream& operator <<(ostream& os, const Ticket& ticket) {
	os << "Codigo: " << ticket.getCodigo() << "\n";
	os << "Fecha y hora: " << ticket.getHoraTickSolicitud() << "\n";
	os << "Prioridad final: " << ticket.getPrioridadFinal() << "\n";
	os << "Tipo de usuario: " << ticket.getTipoUsser() << "\n";
	os << "Servicio: " << ticket.getServicio() << "\n";
	return os;
}

