#pragma once
#include <String>
#include "Ventanilla.h"
#include "LinkedPriorityQueue.h" //Clase creada por el profe durante clases
#include "PriorityQueue.h"	// Clase creada por el profe durante clases
#include "HeapPriorityQueue.h"	// Clase creada por el profe durante clases
#include "UnsortedArrayDictionary.h"	// Clase facilitada por el profe
#include "DLinkedList.h"	// Clase creada por el profe durante clases

using std::string;
using std::to_string;
using std::isdigit;
using std::stoi;
using std::ostream;

class Area
{
private:
	string codigo;
	string descripcion;
	int numVentanilllas;
	int cantTicketsDispensados;
	int cantTicketsAtendidos;
	DLinkedList<Ticket*>* respTickets;
	HeapPriorityQueue<Ticket*>* ticketHaAtender;
	UnsortedArrayDictionary<int, Ventanilla*>* ventanillas;

public:

	Area() {
		codigo = "";
		descripcion = "";
		numVentanilllas = 0;
		cantTicketsDispensados = 0;
		cantTicketsAtendidos = 0;
		respTickets = nullptr;
		ticketHaAtender = nullptr;
		ventanillas = nullptr;
	}

	Area(string code, string descrip, int numVentanill) {
		codigo = code;
		descripcion = descrip;
		numVentanilllas = numVentanill;
		cantTicketsDispensados = 0;
		cantTicketsAtendidos = 0;
		respTickets = new DLinkedList<Ticket*>;
		ticketHaAtender = new HeapPriorityQueue<Ticket*>(50, 2901);
		ventanillas = new UnsortedArrayDictionary<int, Ventanilla*>;
		creacionVentanillas(numVentanill);
	}
	Area(string code) {
		codigo = code;
		descripcion = "";
		cantTicketsDispensados = 0;
		cantTicketsAtendidos = 0;
		numVentanilllas = 0;
		respTickets = nullptr;
		ventanillas = nullptr;
		ticketHaAtender = new HeapPriorityQueue<Ticket*>(50, 100);
	}
	Area(const Area& other) {
		codigo = other.codigo;
		descripcion = other.descripcion;
		numVentanilllas = other.numVentanilllas;
		cantTicketsDispensados = other.cantTicketsDispensados;
		cantTicketsAtendidos = other.cantTicketsAtendidos;
		respTickets = new DLinkedList<Ticket*>;
		ventanillas = new UnsortedArrayDictionary<int, Ventanilla*>;
		ticketHaAtender = new HeapPriorityQueue<Ticket*>(50, 100);
	}
	void operator =(const Area other) {
		codigo = other.codigo;
		descripcion = other.descripcion;
		numVentanilllas = other.numVentanilllas;
		cantTicketsDispensados = other.cantTicketsDispensados;
		cantTicketsAtendidos = other.cantTicketsAtendidos;
	}

	~Area(){
		delete respTickets;
		delete ticketHaAtender;
		delete ventanillas;
	}

	// Se encarga de pasar el ticket a las ventanillas, simula la atención.
	void atendiendo(int numVentanilla) {
		Ventanilla* ventanillaElegida = ventanillas->getValue(numVentanilla);
		if (!ticketHaAtender->isEmpty()) { // Por si no hay usuarios en espera
			Ticket* ticketAAtender = ticketHaAtender->min(); // Obtener el puntero del ticket mínimo
			ventanillaElegida->asignarNuevoTicket(ticketAAtender);
			ticketHaAtender->removeMin(); // Saca el ticket de la cola de prioridad
			bool seguro = true;
			respTickets->goToStart();
			while (!respTickets->atEnd() && seguro) {
				Ticket* ticketAtendido = respTickets->getElement();
				if (*ticketAAtender == *ticketAtendido) {
					respTickets->remove(); // También lo elimina del respaldo ya que ahora no se encuentra en la fila
					seguro = false;
				}
				respTickets->next();
			}
			cantTicketsAtendidos++;
			respTickets->goToStart();
		}
		else {
			cout << endl;
			cout << "No users waiting" << endl;
			cout << endl;
		}
	}

	// Agrega tickets a la cola de prioridad
	void agregarTciket(Ticket* newTicket) {
		int priori = newTicket->getPrioridadFinal();
		ticketHaAtender->insert(newTicket, priori);
		respTickets->append(newTicket);
		cantTicketsDispensados++;
	}

	// Para borrar y asignar nuevas ventanillas
	void modifiCantVentanillas(int num) {
		int i = 1;
		while (ventanillas->getSize() != 0) {
			Ventanilla* ventana = ventanillas->getValue(i);
			ventana->~Ventanilla();
			ventanillas->remove(i);
			i++;
		}
		numVentanilllas = num;
		creacionVentanillas(num);
	}

	// Crea las ventanillas para las áreas
	void creacionVentanillas(int num) {
		for (int i = 1; i <= num; i++) {
			Ventanilla* newVentana = new Ventanilla(codigo + to_string(i));
			ventanillas->insert(i, newVentana);
		}
	}

	// Saca los tickets de la lista de prioridad (Centrado en el tipo de usuario)
	void borrarTicketsPorNombreUser(string nombreUsser) {
		bool huboCoincidencia = false;
		while (!ticketHaAtender->isEmpty())
		{
			Ticket* ticket = ticketHaAtender->removeMin();
			// Si encuentra aunque sea una coincidencia
			if (ticket->getTipoUsser() == nombreUsser && !huboCoincidencia) {
				borrarTicketsTU(nombreUsser); // Manda a remover los tickets del respaldo
				huboCoincidencia = true; // Por lo que ya no hay necesidad de repetir el bucle del método
			}	
		}
		borrarTicketEnVentanillaTU(nombreUsser);
		llenarTicketHaAtenderNuevamente();
	}

	// Remueve los tickets de la lista de respaldo (Centrado en el tipo de usuario)
	void borrarTicketsTU(string nombreUsser) {
		respTickets->goToStart();
		while (!respTickets->atEnd())
		{
			Ticket* finado = respTickets->getElement();
			if (finado->getTipoUsser() == nombreUsser) {
				respTickets->remove();
				delete finado; // Libera la memoria
				cantTicketsDispensados--; // Se borra de los dispensados porque se borra el usuarios
			}
			respTickets->next();
		}
		respTickets->goToStart();
	}

	// Saca los tickets de la lista de prioridad (Centrado en los servicios)
	void borrarTicketsPorNombreServ(string nombreServ) {
		bool huboCoincidencia = false;
		while (!ticketHaAtender->isEmpty())
		{
			Ticket* ticket = ticketHaAtender->removeMin();
			// Si encuentra aunque sea una coincidencia
			if (ticket->getServicio() == nombreServ && !huboCoincidencia) {
				borrarTicketsServ(nombreServ); // Manda a remover los tickets del respaldo
				huboCoincidencia = true; // Por lo que ya no hay necesidad de repetir el bucle del método
			}
		}
		borrarTicketEnVentanillaServ(nombreServ);
		llenarTicketHaAtenderNuevamente();
	}
	
	// Remueve los tickets de la lista de respaldo (Centrado en los servicios)
	void borrarTicketsServ(string nombreServ) {
		respTickets->goToStart();
		while (!respTickets->atEnd())
		{
			Ticket* finado = respTickets->getElement();
			if (finado->getServicio() == nombreServ) {
				respTickets->remove();
				cantTicketsDispensados--; // Se borra de los dispensados porque se borra el servicio
			}
			respTickets->next();
		}
		respTickets->goToStart();
	}

	// Llena la lista de prioridad nuevamente
	void llenarTicketHaAtenderNuevamente() {
		respTickets->goToStart();
		while (!respTickets->atEnd()) {
			Ticket* ticket = respTickets->getElement();
			ticketHaAtender->insert(ticket, ticket->getPrioridadFinal());
			respTickets->next();
		}
		respTickets->goToStart();
	}

	// Borra los tickets en ventanilla si coinciden con el usuario que se está eliminando
	void borrarTicketEnVentanillaTU(string nombreTU) {
		for (int i = 1; i <= numVentanilllas; i++) {
			Ventanilla* ventanillaARevisar = ventanillas->getValue(i);
			if (ventanillaARevisar->getTicketActual() != nullptr) {
				ventanillaARevisar->borrarTicketAtendidoTU(nombreTU);
			}
		}
	}

	// Borra los tickets en ventanilla si coinciden con el servicio que se está eliminando
	void borrarTicketEnVentanillaServ(string nombreServ) {
		for (int i = 1; i <= numVentanilllas; i++) {
			Ventanilla* ventanillaARevisar = ventanillas->getValue(i);
			if (ventanillaARevisar->getTicketActual() != nullptr) {
				ventanillaARevisar->borrarTicketAtendidoServ(nombreServ);
			}
		}
	}

	// Print para el estado de las colas
	void printEstadoColas() {
		cout << "Area: " << codigo << endl;
		int i = 1;
		cout << endl;
		cout << "Queue status:" << endl;
		if (!ticketHaAtender->isEmpty()) {
			while (ticketHaAtender->getSize() > 0)
			{
				Ticket* ticketAImprimir = ticketHaAtender->removeMin();
				cout << "Position " << i << ": Ticket #" << ticketAImprimir->getCodigo() << endl;
				i++;
			}
			llenarTicketHaAtenderNuevamente();
			cout << endl;
		}
		else {
			cout << endl;
			cout << "The queue is empty" << endl;
			cout << endl;
		}
		cout << "Windows condition:" << endl;
		for (int i = 1; i <= numVentanilllas; i++) {
			Ventanilla* ventanillaARevisar = ventanillas->getValue(i);
			if (ventanillaARevisar->getTicketActual() != nullptr) {
				Ticket* ultTicketAtendido = ventanillaARevisar->getTicketActual();
				cout << ventanillaARevisar->getNombre() << ": " << ultTicketAtendido->getCodigo() << endl;
			}
			else {
				cout << ventanillaARevisar->getNombre() << ": " << "There is no registration yet" << endl;
			}
			
		}
		cout << endl;
		cout << endl;
	}
	
	// Se encarga de llevar a cabo la limpieza de colas y estadisticas para todo lo relacionado con areas
	void limpieza() {
		respTickets->clear();
		int i = 1;
		while (!ticketHaAtender->isEmpty())
		{
			Ticket* ticket = ticketHaAtender->removeMin();
		}
		for (int i = 1; i <= numVentanilllas; ++i) {
			Ventanilla* ventana = ventanillas->getValue(i);
			ventana->limpiezaProfunda();
			i++;
		}
		cantTicketsAtendidos = 0;
		cantTicketsDispensados = 0;
	}

	// Da el tiempo promedio de espera para ser atendido en esta Area << FLORA >> y << CARMEN >>
	void promedioDuracionA(){
		int promedioVent = 0; // C
		for (int i = 1; i <= numVentanilllas; ++i) {
			Ventanilla* ventana = ventanillas->getValue(i);
			if (ventana->getCantTicketsAtendidos() > 0)
				promedioVent += ventana->promedioDuracionAtencionV();
		}
		promedioVent = promedioVent / numVentanilllas; // F
		if (promedioVent > 0) {
			int horas = promedioVent / 3600;
			int minutos = (promedioVent % 3600) / 60;
			int segundos = promedioVent % 60;
			cout << "The average waiting time is:" << endl;
			cout << "Hours: " << horas << endl;
			cout << "Minutes: " << minutos << endl;
			cout << "Seconds: " << segundos << endl;
		}
		else {
			cout << "Without data, an estimated time cannot be obtained." << endl;
			cout << endl;
		}
		
	}

	void ventanillasCantTickAtend() {
		cout << "Number of tickets served per window :" << endl;
		for (int i = 1; i <= numVentanilllas; i++) {
			Ventanilla* ventanilla = ventanillas->getValue(i);
			cout << ventanilla->getNombre() << ": " << ventanilla->getCantTicketsAtendidos() << endl;
		}
	}

	// Operadores de comparación -----------------------------
	bool operator==(const Area& other) {
		return codigo == other.codigo;
	}

	// Métodos Get -------------------------------------------
	string getCodigo() const{
		return codigo;
	}

	string getDescripcion() const{
		return descripcion;
	}

	int getNumVentanillas() const{
		return numVentanilllas;
	}

	int getCantidadDeTicketsDispensados() const{
		return cantTicketsDispensados;
	}

	int getCantidadDeTicketsAtendidos() const {
		return cantTicketsAtendidos;
	}
};

// < Flora > El print como objeto
ostream& operator <<(ostream& os, const Area& area) {
	os << "Codigo: " << area.getCodigo() << "\n";
	os << "Descripcion: " << area.getDescripcion() << "\n";
	os << "NumVentanilla: " << area.getNumVentanillas() << "\n";
	os << "CantidadTicketsDispensados: " << area.getCantidadDeTicketsDispensados() << "\n";
	os << "CantidadTicketsAtendidos: " << area.getCantidadDeTicketsAtendidos() << "\n";
	return os;
}

