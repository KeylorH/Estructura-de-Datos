#pragma once
#include <String>
#include "Area.h"

using std::ostream;
using std::string;

class Servicio
{
private:
	string nombre;
	string descripcion;
	int numPrioridad;
	string area;
	int cantTicketsSolcitados;

	

public:
	Servicio() {
		nombre = "";
		descripcion = "";
		numPrioridad = 2901;
		area = "";
		cantTicketsSolcitados = 0;
	}

	Servicio(string nombre, string descripcion, int numPrioridad, string area) {
		this->nombre = nombre;
		this->area = area;
		this->descripcion = descripcion;
		this->numPrioridad = numPrioridad;
		cantTicketsSolcitados = 0;
	}

	Servicio(const Servicio& other) {
		nombre = other.nombre;
		descripcion = other.descripcion;
		numPrioridad = other.numPrioridad;
		area = other.area;
		cantTicketsSolcitados = other.cantTicketsSolcitados;
	}
	void operator =(const Servicio& other) {
		nombre = other.nombre;
		descripcion = other.descripcion;
		numPrioridad = other.numPrioridad;
		area = other.area;
		cantTicketsSolcitados = other.cantTicketsSolcitados;
	}

	// Suma al contador de los tickets que fueron solictados para este servicio
	void sumaTicketsSolicitados() {
		cantTicketsSolcitados++;
	}

	void reinicioTicketSolicitados() {
		cantTicketsSolcitados = 0;
	}

	// Métodos Get -------------------------------------------
	string getNombre() const{
		return nombre;
	}

	string getDescripcion() const{
		return descripcion;
	}

	int getNumPrioridad() const{
		return numPrioridad;
	}

	string getArea() const{
		return area;
	}

	int getCantTicketsSolcitados() const{
		return cantTicketsSolcitados;
	}

	// Operadores de comparación -----------------------------
	bool operator==(const Servicio& other) const{
		return this->nombre == other.getNombre();
	}
};
ostream& operator <<(ostream& os, const Servicio& servicio) {
	os << "Nombre: " << servicio.getNombre() << "\n";
	os << "Descripcion: " << servicio.getDescripcion() << "\n";
	os << "Area: " << servicio.getArea() << "\n";
	os << "Numero de prioridad: " << servicio.getNumPrioridad() << "\n";
	os << "Cantidad de tickets: " << servicio.getCantTicketsSolcitados() << "\n";
	return os;
}
