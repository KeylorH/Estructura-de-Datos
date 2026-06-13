#pragma once
#include <String>
#include <chrono>

#include <stdexcept>
#include <sstream> // flujos de textos
#include "Ventanilla.h"	
#include "Area.h"
#include "Ticket.h"
#include "Servicio.h"
#include "DLinkedList.h"	// Clase creada por el profe durante clases
#include "TipoDeUsuario.h"
#include "HeapPriorityQueue.h"	// Clase creada por el profe durante clases

using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::getline;
using std::stoi;
using std::istringstream;

class Sistema
{
private:
	HeapPriorityQueue<TipoDeUsuario*>* impresionDeUsuarios;
	DLinkedList<TipoDeUsuario*>* usuarios;
	DLinkedList<string>* nombreUsuarios;
	DLinkedList<Servicio*>* serviciosDisponibles;
	DLinkedList<Servicio*>* respServiciosDisponibles;
	DLinkedList<Area*>* areas;
	int consecutivoGlobal;
	int cantUssers;
	bool dDLServiciosDisp;
	bool dDLRespServiciosDisp;


	Sistema(const Sistema& other){}
	void operator=(const Sistema& other){}


public:

	Sistema() {
		impresionDeUsuarios = new HeapPriorityQueue<TipoDeUsuario*>(50, 100);
		usuarios = new DLinkedList<TipoDeUsuario*>;
		nombreUsuarios = new DLinkedList<string>;
		respServiciosDisponibles = new DLinkedList<Servicio*>;
		serviciosDisponibles = new DLinkedList<Servicio*>;
		areas = new DLinkedList<Area*>;
		consecutivoGlobal = 100;
		cantUssers = 0;
		dDLServiciosDisp = true;
		dDLRespServiciosDisp = false;
	}

	/*Es el intermediario para que se ejecuten las funciones respectivas de cada opcion, la idea fue originalmente
	  de Flora, es utilizada hasta el día de hoy en las tareas de este curso*/
	int inicio() {
		string eleccionString;
		OpcionesMenu();
		getline(cin, eleccionString);
		int eleccion = validandoEntradas(eleccionString, 6);
		switch (eleccion) {
		case 1: // Estado de las colas
			estadoDeLasColas();
			break;
		case 2: // Solicitud de ticket
			administradorOpc2();
			break;
		case 3: // Atender
			atenderTickets();
			break;
		case 4: // Administracion
			administradorOpc4();
			break;
		case 5: // Estadisticas del sistema
			consultaEstadisticas();
			break;
		}
		return eleccion; // El 6 es borrar
	}
	
	// La columna vertebral del programa, este es el que corre el main
	void programa() {
		int condicion = 1;
		while (condicion != 6) { 
			try {
				condicion = inicio();
			}
			catch (const std::exception& e) {
				cout << endl;
				std::cerr << e.what() << endl;
			}
			cout << endl;
			cout << endl;
		}
		cout << " ------------ Programa terminado ----------- " << endl;
		delete areas;
		delete usuarios;
		delete serviciosDisponibles;
		delete respServiciosDisponibles;
		delete nombreUsuarios;
		delete impresionDeUsuarios;
	}

	// Imprime las opciones principales del menú
	void OpcionesMenu(){
		cout << " ------------------------- Menu ------------------------- " << endl;
		cout << endl;
		cout << "<< Enter the corresponding number for the desired operation >>" << endl;
		cout << endl;
		cout << "1. Check queue status." << endl;
		cout << "2. Request a ticket." << endl;
		cout << "3. Serve at the window." << endl;
		cout << "4. System administration." << endl;
		cout << "5. System statistics." << endl;
		cout << "6. Log off" << endl;
		cout << endl;
	}
	
	// Se encarga de hacer posible la interfaz de la segunda opcion (solicitar un ticket)
	void administradorOpc2() {
		if (areas->getSize() > 0  && usuarios->getSize() > 0 && (verifiVoidDLLServDisp() == 1 || verifiVoidDLLServDisp() == 2)) {
			int opcionElegida;
			do {
				cout << endl;
				string opcionElegidaStr;
				cout << "Now you are in the 'Ticket Request' section, select an option:" << endl;
				cout << endl;
				cout << "Press << 1 >> to request a ticket" << endl;
				cout << "Press << 2 >> to return to the main menu" << endl;
				cout << endl;
				getline(cin, opcionElegidaStr);
				opcionElegida = validandoEntradas(opcionElegidaStr, 2);
				if (opcionElegida == 1)
					sacarTicket();
			} while (opcionElegida != 2);
		}
		else {
			cout << endl;
			cout << "The system doesn't have the information required to execute the request" << endl;
			cout << endl;
		}
	}

	// Se encarga de hacer posible la interfaz de la cuarta opcion (Administración del sistema)
	void administradorOpc4() {
		int opcionElegida;
		do {
			cout << endl;
			string opcionElegidaStr;
			cout << "Now you are in the 'Administration' section, select an option:" << endl;
			cout << endl;
			cout << "Press << 1 >> to add items (User Types | Areas | Services)" << endl;
			cout << "Press << 2 >> to delete items (User Types | Areas | Services)" << endl;
			cout << "Press << 3 >> to modify elements (Quantity of windows | Order of services)" << endl;
			cout << "Press << 4 >> to clear queues and statistics (Reset some system data)" << endl;
			cout << "Press << 5 >> to return to the main menu" << endl;
			cout << endl;
			getline(cin, opcionElegidaStr);
			opcionElegida = validandoEntradas(opcionElegidaStr, 5);
			switch (opcionElegida) {
			case 1:
				agregarElementos();
				break;
			case 2:
				borrar();
				break;
			case 3:
				modificar();
				break;
			case 4:
				limpiarColasYEstadisticas();
				break;
			}
		} while (opcionElegida != 5);
	}

	// Se encarga de llevar a cabo la consulta de las estadisticas del sistema
	void consultaEstadisticas() {
		cout << endl;
		if (areas->getSize() > 0 && usuarios->getSize() > 0 && (verifiVoidDLLServDisp() == 1 || verifiVoidDLLServDisp() == 2)) {
			cout << " ----- System statistics ----- " << endl;
			cout << endl;
			detallesEstadisticasAreas();
			cout << endl;
			detallesEstadisticasServ();
			cout << endl;
			detallesEstadisticasUsuarios();
			cout << endl;
			cout << " ----- Press any key to exit ----- " << endl;
			cin.ignore(); // Para no tener que guardar la info del string
		}
		else {
			cout << "The system does not have the information required to execute the request" << endl;
			cout << endl;
		}
		
	}

	// Enseña las estadisticas de las areas
	void detallesEstadisticasAreas() {
		while (!areas->atEnd()) {
			Area* area = areas->getElement();
			cout << "Area: " << area->getCodigo() << endl;
			cout << "Number of tickets dispensed: " << area->getCantidadDeTicketsDispensados() << endl;
			area->ventanillasCantTickAtend();
			cout << endl;
			area->promedioDuracionA();
			cout << endl;
			areas->next();
		}
		areas->goToStart();
	}

	// Enseña las estadisticas de los servicios
	void detallesEstadisticasServ() {
		cout << "Number of tickets requested per service:" << endl;
		if (verifiVoidDLLServDisp() == 1) {
			serviciosDisponibles->goToStart();
			while (!serviciosDisponibles->atEnd()) {
				Servicio* servicio = serviciosDisponibles->getElement();
				cout << servicio->getNombre() << ": " << servicio->getCantTicketsSolcitados() << endl;
				serviciosDisponibles->next();
			}
			serviciosDisponibles->goToStart();
		}
		else {
			respServiciosDisponibles->goToStart();
			while (!respServiciosDisponibles->atEnd()) {
				Servicio* servicio = respServiciosDisponibles->getElement();
				cout << servicio->getNombre() << ": " << servicio->getCantTicketsSolcitados() << endl;
				respServiciosDisponibles->next();
			}
			respServiciosDisponibles->goToStart();
		}
	}

	// Enseña las estadisticas de los tipos de usuario
	void detallesEstadisticasUsuarios() {
		cout << endl;
		usuarios->goToStart();
		cout << "Number of tickets issued by user type:" << endl;
		while (!usuarios->atEnd()) {
			TipoDeUsuario* usuario = usuarios->getElement();
			cout << usuario->getNombre() << ": " << usuario->getCantTicketsEmitidos() << endl;
			usuarios->next();
		}
		usuarios->goToStart();
	}
	
	// Agrega la información al sistema
	void agregarElementos() {
		int eleccion;
		do {
			cout << endl;
			string eleccionStr;
			cout << "Now, enter the number of the item you want to add:" << endl;
			cout << endl;
			cout << "1. Usser" << endl;
			cout << "2. Area" << endl;
			cout << "3. Service" << endl;
			cout << endl;
			cout << "Or type << 4 >> to abort the process" << endl;
			cout << endl;
			getline(cin, eleccionStr);
			eleccion = validandoEntradas(eleccionStr, 4);
			if (eleccion == 1) {
				agregarTipoDeUsuario();
			}
			else {
				if (eleccion == 2) {
					agregarArea();
				}
				else {
					if (eleccion == 3)
						agregarServicio();
				}
			}
		} while (eleccion != 4);
	}


	// Enseña el estado de las colas (Areas, ventanillas y filas) (estructura principal)
	void estadoDeLasColas() {
		if (areas->getSize() > 0) {
			cout << endl;
			cout << "Now, the current status of the queues:" << endl;
			cout << endl;
			while (!areas->atEnd()) {
				Area* areaAct = areas->getElement();
				areaAct->printEstadoColas();
				areas->next();
				cout << endl;
			}
			areas->goToStart();
			cout << "Press any key to exit" << endl;
			cin.ignore(); // Para no tener que guardar la info del string
		}
		else {
			cout << endl;
			cout << "The system does not have the information required to show what was requested (areas are missing)" << endl;
			cout << endl;
		}
	}

	// Vuelve posible el proceso de atender un ticket (estructura principal)
	void atenderTickets() {
		if (areas->getSize() > 0) {
			cout << endl;
			cout << "Select the area you want to review:" << endl;
			string eleccion = codigosAreas(); // Regresa el string del Area (codigo)
			bool seguro = true; // Para que no recorra el bucle si no es nesesario
			while (!areas->atEnd())
			{
				Area* areaARevisar = areas->getElement();
				if (areaARevisar->getCodigo() == eleccion && seguro == true) {
					string numVentString;
					cout << endl;
					cout << "This area has " << areaARevisar->getNumVentanillas() << " windows, enter the number of the window to attend:" << endl;
					cout << endl;
					getline(cin, numVentString);
					int numVent = validandoEntradas(numVentString, areaARevisar->getNumVentanillas());
					areaARevisar->atendiendo(numVent);
					seguro = false;
				}
				areas->next();
			}
			areas->goToStart();
		}
		else {
			cout << endl;
			cout << "There are not enough areas to fulfill the request" << endl;
		}
	}

	// Pregunta por los atributos para crear un usuario, lo crea y lo mete en la DLinkedList
	void agregarTipoDeUsuario() {
		cout << endl;
		string nombreTU;
		string descTU;
		string numPrioriTUString;
		cout << "Enter the name of the user type: ";
		getline(cin, nombreTU);
		cout << endl;
		cout << "Enter description for user type: ";
		getline(cin, descTU);
		cout << endl;
		cout << "Enter the priority number for the user type: ";
		getline(cin, numPrioriTUString);
		int numPrioriTU = stoi(numPrioriTUString);
		TipoDeUsuario* newUsser = new TipoDeUsuario(nombreTU, descTU, numPrioriTU);
		nombreUsuarios->append(nombreTU);	// Para la busqueda y asignación en tikcet
		usuarios->append(newUsser);	// Respaldo para la impresión de usuarios y asignación en ticket 
		impresionDeUsuarios->insert(newUsser, numPrioriTU);	// Para la impresión de usuarios en orden
		cantUssers++;
	}

	// Pregunta por los atributos para crear una Area, lo crea y lo mete en la DLinkedList
	void agregarArea() {
		cout << endl;
		string codigoArea;
		string descArea;
		string numVentanillasString;
		cout << "Enter area code: ";
		getline(cin, codigoArea);
		cout << endl;
		cout << "Enter area description: ";
		getline(cin, descArea);
		cout << endl;
		cout << "Enter the number of windows for this area: ";
		getline(cin, numVentanillasString);
		int numVentanillas = stoi(numVentanillasString);
		Area* newArea = new Area(codigoArea, descArea, numVentanillas);
		areas->insert(newArea);
	}

	// Pregunta y crea los servicios, los agrega a los servicios disponibles (DLinkedList) 
	void agregarServicio() {
		if (areas->getSize() > 0) {
			cout << endl;
			string nombreServicio;
			string descServicio;
			string numPrioriString;
			cout << "Enter the service name: ";
			getline(cin, nombreServicio);
			cout << endl;
			cout << "Select the area code to which the service belongs:" << endl;
			string area = codigosAreas();
			cout << endl;
			cout << "Enter service description: ";
			getline(cin, descServicio);
			cout << endl;
			cout << "Enter service priority: ";
			getline(cin, numPrioriString);
			int numPriori = stoi(numPrioriString);
			Servicio* newServicio = new Servicio(nombreServicio, descServicio, numPriori, area);	// Servicio con informacion
			serviciosDisponibles->append(newServicio);
		}
		else {
			cout << endl;
			cout << "Before adding services, areas are needed, please add some" << endl;
		}
	}

	// Se encara de cambiar/asignar el orden a los servicios (la lista)
	void ordenServicios() {
		cout << endl;
		if ((verifiVoidDLLServDisp() == 1 && serviciosDisponibles->getSize() > 1) || (verifiVoidDLLServDisp() == 2 && respServiciosDisponibles->getSize() > 1)) {
			string nuevoOrden;
			cout << "Now, you are shown all the existing services:" << endl;
			cout << endl;
			imprServicios();
			cout << endl;
			cout << "Para establecer el orden en interfaz escriba los numeros de los servicios segun su preferencia intercalados por comas (Ej: 1,4,2,0,3):" << endl;
			cout << endl;
			getline(cin, nuevoOrden);
			auxOrdenServicios(nuevoOrden);
		}
		else {
			cout << endl;
			cout << "There are not enough services to be ordered" << endl;
			cout << endl;
		}
	}

	// Extrae los números del orden de servicios y hace la nueva insercion en DLL serviciosDisp a la de repuesto o viceversa.
	void auxOrdenServicios(string ordenServicios) {
		try { // El codigo de abajo fue sacado de https://acortar.link/fxqWe2, implementado para la función del metodo
			istringstream ss(ordenServicios); // Guarda la cadena en el ss
			int num; // Aqui se guardarán los numeros
			while (ss >> num) { // Mientras sea posible sacar numeros del ordenServicios
				if (dDLServiciosDisp) {
					serviciosDisponibles->goToPos(num);
					Servicio* servicio = serviciosDisponibles->getElement();
					respServiciosDisponibles->append(servicio);
					if (ss.peek() == ',') { // Se asegura de que el siguiente caracter sea un numero
						ss.ignore();
					}

				} // Se supone que funciona como un semaforo, si DLLServDisp está en verde los datos se pasan al DLLRespSD
				else {
					respServiciosDisponibles->goToPos(num);
					Servicio* servicio = respServiciosDisponibles->getElement();
					serviciosDisponibles->append(servicio);
					if (ss.peek() == ',') {
						ss.ignore();
					}
				} // Si no está en verde entonces la DLLRespSD es la que tiene los datos, por ende ella es la que debe pasarlos
			}
			serviciosDisponibles->goToStart(); // Ambas listas vuelven al inicio
			respServiciosDisponibles->goToStart();
			// Aquí se cambian las luces del semaforo xD
			if (dDLServiciosDisp && dDLRespServiciosDisp == false) {
				dDLServiciosDisp = false;
				dDLRespServiciosDisp = true;
				serviciosDisponibles->clear();
			}
			else {
				dDLServiciosDisp = true;
				dDLRespServiciosDisp = false;
				respServiciosDisponibles->clear();
			}
		} // Por si algo no funka, entonces que salga un error
		catch (const std::exception& e) {
			cout << endl;
			cerr << "La entrada fue invalida" << e.what() << endl;
			cout << endl;
		}
	}

	// Imprime los servicios disponibles, solo para enseñar (cambio de orden)
	void imprServicios() {
		int i = 0;
		if (verifiVoidDLLServDisp() == 1) {
			serviciosDisponibles->goToStart();
			while (!serviciosDisponibles->atEnd()) {
				Servicio* servicioAImprimir = serviciosDisponibles->getElement();
				cout << i << ". " << servicioAImprimir->getNombre() << endl;
				serviciosDisponibles->next();
				i++;
			}
			serviciosDisponibles->goToStart();
		}
		else {
			respServiciosDisponibles->goToStart();
			while (!respServiciosDisponibles->atEnd()) {
				Servicio* servicioAImprimir = respServiciosDisponibles->getElement();
				cout << i << ". " << servicioAImprimir->getNombre() << endl;
				respServiciosDisponibles->next();
				i++;
			}
			respServiciosDisponibles->goToStart();
		}
	}

	// Imprime los servicios disponibles, regresa el servicio elegido (interaccion de usario)
	int imprServiciosDisp() {
		int i = 1;
		string eleccionString;
		cout << "Select a type of service:" << endl;
		cout << endl;
		if (verifiVoidDLLServDisp() == 1) {
			serviciosDisponibles->goToStart();
			while (!serviciosDisponibles->atEnd()) {
				Servicio* servicioAImprimir = serviciosDisponibles->getElement();
				cout << i << ". " << servicioAImprimir->getNombre() << endl;
				serviciosDisponibles->next();
				i++;
			}
			cout << endl;
			serviciosDisponibles->goToStart();
			getline(cin, eleccionString);
		}
		else {
			respServiciosDisponibles->goToStart();
			while (!respServiciosDisponibles->atEnd()) {
				Servicio* servicioAImprimir = respServiciosDisponibles->getElement();
				cout << i << ". " << servicioAImprimir->getNombre() << endl;
				respServiciosDisponibles->next();
				i++;
			}
			cout << endl;
			respServiciosDisponibles->goToStart();
			getline(cin, eleccionString);
		}
		return stoi(eleccionString);
	}

	int verifiVoidDLLServDisp() {
		if (serviciosDisponibles->getSize() > 0)
			return 1;	// Significa que los datos los tiene la DLLServDisp
		else
			return 2;	// Significa que los datos los tiene la DLLRespSD
	}

	// Enseña el codigo de todas las areas y regresa el codigo seleccionado (Atender Tickets y agregar Servicios)
	string codigosAreas() {
		cout << endl;
		int i = 1;
		string eleccion;
		while (!areas->atEnd()) {
			Area* areaAImprimir = areas->getElement();
			cout << "Press " << i << " for " << areaAImprimir->getCodigo() << endl;
			i++;
			areas->next();
		}
		cout << endl;
		getline(cin, eleccion);
		int num = stoi(eleccion);
		num--;
		areas->goToPos(num);
		Area* areaSeleccionada = areas->getElement();
		string codigoAreaSelec = areaSeleccionada->getCodigo();
		areas->goToStart();
		return codigoAreaSelec;
	}

	// Enseña al usuario las areas y retorna su eleccion (posicion en lista, util en el borrado)
	int areasPosicion() {
		int i = 1;
		string eleccion;
		while (!areas->atEnd()) {
			Area* areaAImprimir = areas->getElement();
			cout << "Press " << i << " for " << areaAImprimir->getCodigo() << endl;
			i++;
			areas->next();
		}
		cout << endl;
		areas->goToStart();
		getline(cin, eleccion);
		int num = validandoEntradas(eleccion, areas->getSize());
		num--;
		return num;
	}

	// Enseña al usuario los servicios y retorna su eleccion (posicion en lista, util en el borrado) < DLLServDisp >
	int serviciosPosicionSD() {
		int i = 1;
		string eleccion;
		serviciosDisponibles->goToStart();
		while (!serviciosDisponibles->atEnd()) {
			Servicio* servicioAImprimir = serviciosDisponibles->getElement();
			cout << "Press " << i << " for " << servicioAImprimir->getNombre() << endl;
			i++;
			serviciosDisponibles->next();
		}
		cout << endl;
		serviciosDisponibles->goToStart();
		getline(cin, eleccion);
		int num = validandoEntradas(eleccion, serviciosDisponibles->getSize());
		num--;
		return num;
	}

	// Enseña al usuario los servicios y retorna su eleccion (posicion en lista, util en el borrado) < DLLRespSD >
	int serviciosPosicionRespSD() {
		int i = 1;
		string eleccion;
		respServiciosDisponibles->goToStart();
		while (!respServiciosDisponibles->atEnd()) {
			Servicio* servicioAImprimir = respServiciosDisponibles->getElement();
			cout << "Press " << i << " for " << servicioAImprimir->getNombre() << endl;
			i++;
			respServiciosDisponibles->next();
		}
		cout << endl;
		respServiciosDisponibles->goToStart();
		getline(cin, eleccion);
		int num = validandoEntradas(eleccion, respServiciosDisponibles->getSize());
		num--;
		return num;
	}

	// Gestiona el objeto a borrar (Se encarga de ejecutar los metodos)
	void borrar() {
		int eleccion;
		do {
			cout << endl;
			string eleccionStr;
			cout << "Now, enter the number of the item you want to delete:" << endl;
			cout << endl;
			cout << "1. User" << endl;
			cout << "2. Area" << endl;
			cout << "3. Service" << endl;
			cout << endl;
			cout << "Or type << 4 >> to abort the process" << endl;
			cout << endl;
			getline(cin, eleccionStr);
			eleccion = validandoEntradas(eleccionStr, 4);
			if (eleccion == 1) {
				borrandoTipoUsuario();
			}
			else {
				if (eleccion == 2) {
					borrandoAreas();
				}
				else {
					if (eleccion == 3)
						borrandoServicios();
				}
			}
		} while (eleccion != 4);
	}

	// Se encarga manejar el borrado de tipos de usuario
	void borrandoTipoUsuario() {
		if (usuarios->getSize() > 0) {
			cout << endl;
			cout << "What Type of User do you want to delete?" << endl;
			cout << endl;
			int tipoDeUsuario = imprUsserDesor();
			tipoDeUsuario--;
			int seguro = advertenciaBorrado();
			if (seguro == 1) {
				muerteUsser(tipoDeUsuario);
				cantUssers--;
				cout << endl;
				cout << "Users successfully updated!" << endl;
				cout << endl;
				imprUsserPorPriori();
				cout << "Press any key to exit" << endl;
				cin.ignore(); // Para no tener que guardar la info del string
			}
			else {
				cout << endl;
				cout << " ---- Aborted operation ----" << endl;
				cout << endl;
			}
		}
		else {
			cout << endl;
			cout << "There are no users to delete" << endl;
			cout << endl;
		}
		
	}
	
	// Se encarga de manejar el borrado de areas
	void borrandoAreas() {
		if (areas->getSize() > 0) {
			cout << endl;
			cout << "Which Area do you want to delete?" << endl;
			cout << endl;
			int posArea = areasPosicion();
			int seguro = advertenciaBorrado();
			if (seguro == 1) {
				muerteArea(posArea);
				cout << endl;
				cout << "Successfully updated areas!" << endl;
				cout << endl;
			}
			else {
				cout << endl;
				cout << " ---- Aborted operation ----" << endl;
				cout << endl;
			}
		}
		else {
			cout << endl;
			cout << "There are no areas to eliminate" << endl;
			cout << endl;
		}
		
	}

	// Se encarga de manejar el borrado de servicios
	void borrandoServicios() {
		if (serviciosDisponibles->getSize() > 0 || respServiciosDisponibles->getSize() > 0) {
			if (verifiVoidDLLServDisp() == 1) { // Significa que los datos los tiene la DLLServDisp
				cout << endl;
				cout << "Which Service do you want to delete?" << endl;
				cout << endl;
				int servicios = serviciosPosicionSD();
				int seguro = advertenciaBorrado();
				if (seguro == 1) {
					muerteServicioSD(servicios);
					cout << endl;
					cout << "Services updated successfully!" << endl;
					cout << endl;
				}
				else {
					cout << endl;
					cout << " ---- Aborted operation ----" << endl;
					cout << endl;
				}
			}
			else { // Centrado en la DLLRespSD
				cout << endl;
				cout << "Which Service do you want to delete?" << endl;
				cout << endl;
				int servicios = serviciosPosicionRespSD();
				int seguro = advertenciaBorrado();
				if (seguro == 1) {
					muerteServicioRespSD(servicios);
					cout << endl;
					cout << "Services updated successfully!" << endl;
					cout << endl;
				}
				else {
					cout << endl;
					cout << " ---- Aborted operation ----" << endl;
					cout << endl;
				}
			}
		}
		else {
			cout << endl;
			cout << "There are no services to delete" << endl;
			cout << endl;
		}
	}

	// Menu encargado de ejecutar los procesos que encapsula modificar (Cantidad de ventanias y Orden de los servicios)
	void modificar() {
		if (areas->getSize() > 0) {
			int eleccion;
			do {
				cout << endl;
				string eleccionStr;
				cout << "Next, enter the number of the element you want to modify:" << endl;
				cout << endl;
				cout << "1. Number of windows (specific area)" << endl;
				cout << "2. Order of available services" << endl;
				cout << endl;
				cout << "Or type << 3 >> to abort the process" << endl;
				cout << endl;
				getline(cin, eleccionStr);
				eleccion = validandoEntradas(eleccionStr, 3);
				if (eleccion == 1) {
					modificarVentanillas();
				}
				else {
					if (eleccion == 2) {
						ordenServicios();
					}
				}
			} while (eleccion != 3);
		}
		else {
			cout << endl;
			cout << "There are no elements that can be modified" << endl;
			cout << endl;
		}
		
	}

	// Se encarga de manejar la modificación de las ventanillas
	void modificarVentanillas() {
		cout << endl;
		cout << "Next, select the area where you want to make the change:" << endl;
		cout << endl;
		int posArea = areasPosicion();
		string newNumVentStr;
		cout << endl;
		cout << "Insert the new number of windows:" << endl;
		cout << endl;
		getline(cin, newNumVentStr);
		int newNumVent = stoi(newNumVentStr);
		areas->goToPos(posArea);
		Area* area = areas->getElement();
		area->modifiCantVentanillas(newNumVent);
		areas->goToStart();
	}

	// Se encarga de limpiar las colas y las estadisticas del sistema (datos, pero sin estructuras principales)
	void limpiarColasYEstadisticas() {
		if (areas->getSize() > 0 && (verifiVoidDLLServDisp() == 1 || verifiVoidDLLServDisp() == 2) && usuarios->getSize() > 0 && consecutivoGlobal != 100) {
			cout << endl;
			while (!areas->atEnd()) { // Lleva a cabo la limpieza de las areas
				Area* areaALimpiar = areas->getElement();
				areaALimpiar->limpieza();
				areas->next();
			}
			areas->goToStart();
			limpiezaServicios(); // Lleva a cabo la limpieza de los servicios
			limpiezaUsuarios(); // Lleva a cabo la limpieza de los usuarios
			cout << "System statistics and tickets in queue have been successfully cleared!" << endl;
			cout << endl;
		}
		else {
			cout << endl;
			cout << "No information to clear" << endl;
			cout << endl;
		}
	}

	// Limpia los servicios
	void limpiezaServicios() {
		if (verifiVoidDLLServDisp() == 1) {
			serviciosDisponibles->goToStart();
			while (!serviciosDisponibles->atEnd())
			{
				Servicio* ServicioALimpiar = serviciosDisponibles->getElement();
				ServicioALimpiar->reinicioTicketSolicitados();
				serviciosDisponibles->next();
			}
			serviciosDisponibles->goToStart();
		}
		else {
			respServiciosDisponibles->goToStart();
			while (!respServiciosDisponibles->atEnd())
			{
				Servicio* ServicioALimpiar = respServiciosDisponibles->getElement();
				ServicioALimpiar->reinicioTicketSolicitados();
				respServiciosDisponibles->next();
			}
			respServiciosDisponibles->goToStart();
		}
	}

	// Limpia los usuarios
	void limpiezaUsuarios() {
		usuarios->goToStart();
		while (!usuarios->atEnd()) {
			TipoDeUsuario* usuarioALimpiar = usuarios->getElement();
			usuarioALimpiar->reinicioCantTicketsEmitidos();
			usuarios->next();
		}
		usuarios->goToStart();
	}
	
	// Una advertencia genérica para cualquier borrado
	int advertenciaBorrado() {
		string eleccion;
		cout << endl;
		cout << "---------------- ATTENTION ----------------" << endl;
		cout << endl;
		cout << "Please note that the following deletion will affect all data related to it." << endl;
		cout << "Are you really sure of your choice?" << endl;
		cout << endl;
		cout << "Press " << 1 << " for " << "YES" << endl;
		cout << "Press " << 2 << " for " << "NO" << endl;
		cout << endl;
		getline(cin, eleccion);
		return validandoEntradas(eleccion,2);
	}

	// Valida que la opción esté dentro del rango solicitado (los valores siempre serán positivos)
	int validandoEntradas(string eleccionStr, int maxValorPosible) {
		int eleccion = stoi(eleccionStr);
		while (eleccion < 1 || eleccion > maxValorPosible) {
			string eleccionString;
			cout << endl;
			cout << "Enter a valid number, please." << endl;
			cout << endl;
			getline(cin, eleccionString);
			eleccion = stoi(eleccionString);
		}
		return eleccion;
	}

	// Imprime los tipos de usuario por prioridad (solo los enseña)
	void imprUsserPorPriori() {
		for (int i = 1; i <= cantUssers; i++){	// Se imprime omitiendo el 0
			TipoDeUsuario* imprUsser = impresionDeUsuarios->min();
			cout << i << ". " << imprUsser->getNombre() << endl;
			impresionDeUsuarios->removeMin();
		}
		cout << endl;
		rellenarHeapPrioUsser();
	}

	// Imprime los tipos de usuario sin orden específico (para interactuar)
	int imprUsserDesor() {
		cout << endl;
		string opcionEscogidaString;
		int i = 1;
		nombreUsuarios->goToStart();
		while (!nombreUsuarios->atEnd()) {	// Se imprime omitiendo el 0
			string imprUsser = nombreUsuarios->getElement();
			cout << "Press " << i << " for " << imprUsser << endl;
			i++;
			nombreUsuarios->next();
		}
		cout << endl;
		nombreUsuarios->goToStart();
		getline(cin, opcionEscogidaString);
		int opcionEscogida = stoi(opcionEscogidaString);
		if (opcionEscogida <= 0 || opcionEscogida > cantUssers) {
			cout << endl;
			cout << "Invalid selection, please enter a valid number:" << endl;
			opcionEscogida = imprUsserDesor();
		}
		return opcionEscogida;

	}

	// Rellena o organiza el HeapProrityQueue de usuarios nuevamente.
	void rellenarHeapPrioUsser() {
		if (!impresionDeUsuarios->isEmpty()) {	// Para cuando se borra un usuario
			impresionDeUsuarios->clear();
		}
		usuarios->goToStart();
		while(!usuarios -> atEnd()) {
			TipoDeUsuario* usuario = usuarios->getElement();
			impresionDeUsuarios->insert(usuario, usuario->getNumPrioridad());
			usuarios->next();
		}
		usuarios->goToStart();
	}

	// Elimina el usuario específico del sistema
	void muerteUsser(int objetivo) {
		nombreUsuarios->goToPos(objetivo);
		string nombreUsser = nombreUsuarios->getElement();
		usuarios->goToPos(objetivo);
		nombreUsuarios->remove(); // remueve el nombre del sistema
		usuarios->remove(); // remueve el usuario como tal
		removeUssersAreas(nombreUsser);	// Borrar los tickets asociados de las Areas
		nombreUsuarios->goToStart();
		usuarios->goToStart();
		rellenarHeapPrioUsser();
	}

	// Elimina la area específica del sistema
	void muerteArea(int objetivo) {
		areas->goToPos(objetivo);
		Area* finado = areas->getElement();
		string codeArea = finado->getCodigo();
		areas->remove();
		destruccionDeComplices(codeArea);
		delete finado;
		areas->goToStart();
	}

	// Se encarga de eliminar los servicios asociados a la Area que se está borrando
	void destruccionDeComplices(string codeArea) {
		int i = 0;
		if (verifiVoidDLLServDisp() == 1) {
			serviciosDisponibles->goToStart();
			while (!serviciosDisponibles->atEnd()) {
				Servicio* servicio = serviciosDisponibles->getElement();
				// ----------------------- DEPURAR ---------------
				cout << endl;
				cout << "Nombre del servicio: " << servicio->getNombre() << endl;
				cout << endl;
				// ----------------------- DEPURAR --------------

				if (servicio->getArea() == codeArea) {
					// ----------------------- DEPURAR ---------------
					cout << endl;
					cout << "--- Hubo coincidencia con ese nombre ---" << endl;
					cout << endl;
					// ----------------------- DEPURAR --------------
					muerteServicioSD(i);
				}
				else {
					serviciosDisponibles->next();
					i++;
				}
			}
			serviciosDisponibles->goToStart();
		}
		else {
			respServiciosDisponibles->goToStart();
			while (!respServiciosDisponibles->atEnd()) {
				Servicio* servicio = respServiciosDisponibles->getElement();
				if (servicio->getNombre() == codeArea) {
					muerteServicioRespSD(i);
				}
				i++;
				respServiciosDisponibles->next();
			}
			respServiciosDisponibles->goToStart();
		}
	}

	// Elimina el servicio específico del sistema (DLLServDisp)
	void muerteServicioSD(int objetivo) {
		serviciosDisponibles->goToPos(objetivo);
		Servicio* finado = serviciosDisponibles->getElement();
		string nombreServ = finado->getNombre();
		serviciosDisponibles->remove();
		removeServAreas(nombreServ);
	}

	// Elimina el servicio específico del sistema (DLLRespSD)
	void muerteServicioRespSD(int objetivo) {
		respServiciosDisponibles->goToPos(objetivo);
		Servicio* finado = respServiciosDisponibles->getElement();
		string nombreServ = finado->getNombre();
		respServiciosDisponibles->remove();
		removeServAreas(nombreServ);
	}

	// Remueve los tickets con el tipo de usuario que se eliminó
	void removeUssersAreas(string nombreUsser) {
		for (int i = 0; i < areas->getSize(); i++) {
			Area* area = areas->getElement();
			area->borrarTicketsPorNombreUser(nombreUsser);
			areas->next();
		}
		areas->goToStart();
	}

	// Remueve los tickets con el servicio que se eliminó
	void removeServAreas(string nombreServ) {
		areas->goToStart();
		for (int i = 0; i < areas->getSize(); i++) {
			Area* area = areas->getElement();
			area->borrarTicketsPorNombreServ(nombreServ);
			areas->next();
		}
		areas->goToStart();
	}

	// Crea los tickets y los manda a su respectiva area (estructura principal)
	void sacarTicket() {
		if (usuarios->getSize() > 0 && areas->getSize() > 0 && (verifiVoidDLLServDisp() == 1 || verifiVoidDLLServDisp() == 2)) { // Si tenemos datos
			cout << endl;
			cout << "Select your user type:" << endl;
			cout << endl;
			int tipoDeUsuario = imprUsserDesor(); // Selecciona su tipo de usuario
			cout << endl;
			tipoDeUsuario--; // Se le resta para buscar en la lista
			usuarios->goToPos(tipoDeUsuario);
			TipoDeUsuario* usserData = usuarios->getElement();
			usserData->sumaCantTicketsEmitidos(); // Le suma a la cantDeTicketsEmitidos para el tipo de usuario ----------
			string nombreTU = usserData->getNombre();
			int prioriTU = usserData->getNumPrioridad();
			if (verifiVoidDLLServDisp() == 1){	// Si es 1 se usa la DLLServDisp, de lo contrario la DLLRespSD
				int servicioElegido = imprServiciosDisp();
				cout << endl;
				servicioElegido--;
				serviciosDisponibles->goToPos(servicioElegido);
				Servicio* servicioData = serviciosDisponibles->getElement();
				servicioData->sumaTicketsSolicitados(); // Le suma al conteo de tickets solictados del servicio
				string nombreServ = servicioData->getNombre();
				int prioriServ = servicioData->getNumPrioridad();
				string areaDelServ = servicioData->getArea();
				int prioriFinal = prioriTU * 10 + prioriServ;	// Operación de la prioridad final (pudo haber sido un método)
				// Por fin se crea el ticket!
				Ticket* newTicket = new Ticket(areaDelServ+to_string(consecutivoGlobal), nombreTU, nombreServ, prioriFinal);
				consecutivoGlobal++; // Se le suma porque ya se creó un ticket
				insertarTicket(newTicket, areaDelServ);
				cout << endl;
				cout << " ---- Ticket generated ---- " << endl;
				cout << *newTicket << endl;
				cout << endl;

			}	// A continuación se ejecuta lo mismo pero a la lista de respaldo (si ella tuviera los datos)
			else {
				int servicioElegido = imprServiciosDisp();
				servicioElegido--;
				respServiciosDisponibles->goToPos(servicioElegido);
				Servicio* servicioData = respServiciosDisponibles->getElement();
				servicioData->sumaTicketsSolicitados(); // Le suma al conteo de tickets solictados del servicio
				string nombreServ = servicioData->getNombre();
				int prioriServ = servicioData->getNumPrioridad();
				string areaDelServ = servicioData->getArea();
				int prioriFinal = prioriTU * 10 + prioriServ;	// Operación de la prioridad final (pudo haber sido un método)
				// Por fin se crea el ticket!
				Ticket* newTicket = new Ticket(areaDelServ + to_string(consecutivoGlobal), nombreTU, nombreServ, prioriFinal);
				consecutivoGlobal++; // Se le suma porque ya se creó un ticket
				insertarTicket(newTicket, areaDelServ);
				cout << endl;
				cout << " ---- Ticket generated ---- " << endl;
				cout << *newTicket << endl;
				cout << endl;
			}
		}
		else {
			cout << "The system does not have the information required to create the request (data is missing)" << endl;
			cout << endl;
			cout << "Press any key to exit" << endl; // Revisar en hoja si esto aplica aqui***
			cin.ignore(); // Para no tener que guardar la info del string
		}
	}

	// Inserta el ticket en la cola del area solicitada
	void insertarTicket(Ticket* elTicket, string areaAInsertar) {
		while (!areas->atEnd()) {
			Area* areaARevisar = areas->getElement();
			if (areaARevisar->getCodigo() == areaAInsertar)
				areaARevisar->agregarTciket(elTicket);
			areas->next();
		}
		areas->goToStart();
	}

};

