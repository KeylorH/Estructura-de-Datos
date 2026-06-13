#pragma once
#include <String>
using std::string;
using std::ostream;

class TipoDeUsuario
{
private:
	string nombre;
	string descripcion;
	int numPrioridad;
	int cantTicketsEmitidos;

public:
	TipoDeUsuario() {
		nombre = "";
		descripcion = "";
		numPrioridad = 0;
		cantTicketsEmitidos = 0;
	}
	TipoDeUsuario(string nombre, string descripcion, int numPrioridad) {
		this->nombre = nombre;
		this->descripcion = descripcion;
		this->numPrioridad = numPrioridad;
		cantTicketsEmitidos = 0;
	}
	TipoDeUsuario(const TipoDeUsuario& other) {
		nombre = other.nombre;
		descripcion = other.descripcion;
		numPrioridad = other.numPrioridad;
		cantTicketsEmitidos = other.cantTicketsEmitidos;
	}
	void operator =(const TipoDeUsuario other) {
		nombre = other.nombre;
		descripcion = other.descripcion;
		numPrioridad = other.numPrioridad;
		cantTicketsEmitidos = other.cantTicketsEmitidos;
	}
	

	// Operadores de comparación
	bool operator==(const TipoDeUsuario& other) {
		return nombre == other.nombre;
	}

	void sumaCantTicketsEmitidos() {
		cantTicketsEmitidos++;
	}

	void reinicioCantTicketsEmitidos() {
		cantTicketsEmitidos = 0;
	}

	// Métodos gets
	string getNombre() const{
		return nombre;
	}

	string getDescripcion() const{
		return descripcion;
	}

	int getNumPrioridad() const{
		return numPrioridad;
	}

	int getCantTicketsEmitidos() const{
		return cantTicketsEmitidos;
	}
};
ostream& operator <<(ostream& os, const TipoDeUsuario& usuario) {
	os << "Nombre: " << usuario.getNombre() << "\n";
	os << "Descripcion: " << usuario.getDescripcion() << "\n";
	os << "Num Prioridad: " << usuario.getNumPrioridad() << "\n";
	os << "Cantidad tickets: " << usuario.getCantTicketsEmitidos() << "\n";
	return os;
}
