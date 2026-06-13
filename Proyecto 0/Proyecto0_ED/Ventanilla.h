#pragma once
#include <String>
#include <ctime> // Para poder almacenar y manipular el tiempo
#include <iomanip>
#include "Ticket.h" //Para poder enseñar la info de los tickets
#include "DLinkedList.h"  // Clase creada por el profe en clases
using std::ostream;
using std::string;
using std::time_t;
using std::put_time;
using std::stringstream;

class Ventanilla
{
private:
	string nombre;
	Ticket* ticketActual; // Obtendrá la información del ticket por referencia
	int cantTicketsAtendidos;
	DLinkedList<int>* duracionesAtencion;  // Almacena las duraciones de atención para luego sacar el promedio
public:
	Ventanilla() {
		// Inicializar los miembros de Ventanilla según sea necesario
		nombre = "";
		ticketActual = nullptr;
		cantTicketsAtendidos = 0;
		duracionesAtencion = new DLinkedList<int>;
	}
	Ventanilla(string nombre) {
		this->nombre = nombre;
		this->ticketActual = nullptr;
		cantTicketsAtendidos = 0;
		duracionesAtencion = new DLinkedList<int>;
	}
	Ventanilla(const Ventanilla& other) { // Constructor de copia
		nombre = other.nombre;
		ticketActual = other.ticketActual;
		cantTicketsAtendidos = other.cantTicketsAtendidos;
	}
	~Ventanilla() {
		if (cantTicketsAtendidos != 0) {
			delete duracionesAtencion;
			delete ticketActual;
		}
	}
	void operator =(const Ventanilla other) { // Constructor de asignación
		nombre = other.nombre;
		if (other.ticketActual != nullptr)
			ticketActual = new Ticket(*other.ticketActual); // Copia profunda de Ticket, para que también apunte al dato;
		else
			ticketActual = nullptr;
		cantTicketsAtendidos = other.cantTicketsAtendidos;
		duracionesAtencion = new DLinkedList<int>;
	}

	// Recibe un ticket por referencia de Area y lo asigna a la ventanilla
	void asignarNuevoTicket(Ticket* nuevoTicket) {
		delete ticketActual;
		ticketActual = nuevoTicket;
		nuevoRegistroTiempEsper(ticketActual->gethoraTicketSolici());
		cantTicketsAtendidos++;
	}

	// Recibe el tiempo de solictud del ticket, saca la duracion de espera y la almacena para el futuro 
	void nuevoRegistroTiempEsper(time_t tiempoTickSolici) {
		time_t horaTickAtencion = time(0);
		time_t duracionEspera = horaTickAtencion - tiempoTickSolici;
		duracionesAtencion->append(duracionEspera);
	}

	// Borra el ticket de la ventanilla si coincide con el tipo de usuario borrado
	void  borrarTicketAtendidoTU(string nombreTU) {
		if (ticketActual->getTipoUsser() == nombreTU) {
			delete ticketActual;
			ticketActual = nullptr;
		}
	}

	// Borra el ticket de la ventanilla si coincide con el servicio borrado
	void  borrarTicketAtendidoServ(string nombreServ) {
		if (ticketActual->getServicio() == nombreServ) {
			delete ticketActual;
			ticketActual = nullptr;
		}
	}

	// Saca el promedio del tiempo de atencion de la ventanilla << FLORA >>
	int promedioDuracionAtencionV() {
		int sumaTotal = 0;
		duracionesAtencion->goToStart();
		while (!duracionesAtencion->atEnd()) {
			sumaTotal += duracionesAtencion->getElement();
			duracionesAtencion->next();
		}
		duracionesAtencion->goToStart();
		sumaTotal = sumaTotal / duracionesAtencion->getSize();
		return sumaTotal;
	}

	// Borra los datos en función de la solicitud "Limpiar colas y estadisticas"
	void limpiezaProfunda() {
		duracionesAtencion->clear();
		delete ticketActual;
		ticketActual = nullptr;
		cantTicketsAtendidos = 0;
	}

	// Operadores de comparación -------------------------------
	bool operator==(const Ventanilla& other) {
		return nombre == other.nombre;
	}

	// Métodos Gets -------------------------------------
	string getNombre() const{
		return nombre;
	}
	int getCantTicketsAtendidos() const{
		return cantTicketsAtendidos;
	}
	Ticket* getTicketActual() const{
		return ticketActual;
	}
	void setTicketActual(Ticket* ticketAct) {
		ticketActual = ticketAct;
	}


};
ostream& operator <<(ostream& os, const Ventanilla& ventanilla) {
	os << "Nombre: " << ventanilla.getNombre() << "\n";
	os << "Cantidad atendidos: " << ventanilla.getCantTicketsAtendidos() << "\n";
	os << "Ticket actual: " << ventanilla.getTicketActual() << "\n";
	return os;
}
