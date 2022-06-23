#include <iostream>
#include <fstream>
#include <vector>
#include "PriorityQueue.h"

struct tCliente {
	int tiempo = -1;
	int momentoEnQueSaldra = -1;
	int cajaALaQueVa = -1;
};

bool operator<(tCliente a, tCliente b) {
	return a.momentoEnQueSaldra<b.momentoEnQueSaldra || (a.momentoEnQueSaldra == b.momentoEnQueSaldra && a.cajaALaQueVa<b.cajaALaQueVa);
}

bool resuelveCaso() {
	int cajas, clientes, a;
	
	std::cin >> cajas >> clientes;
	if (cajas==0) return false; //Fin del programa
	else if (cajas > clientes) {
		for (int i = 0; i < clientes; ++i) std::cin >> a;
		std::cout <<clientes + 1 << std::endl; //Caso donde hay mas cajas libres que clientes
	}
	else if (cajas>0 && clientes>0){ //Caso donde tenemos que gestionar las cajas
		int tiempo = 0, primeraCajaLibre = 0;
		PriorityQueue<tCliente> colaClientes;
		while(clientes>0) {
			//Si hay caja vacia, se mete al cliente en la cola de cajas
			if (colaClientes.size() < cajas){ 
				tCliente cliente;
				std::cin >> cliente.tiempo; //Se mete por fichero el tiempo que va a tardar
				cliente.momentoEnQueSaldra = tiempo + cliente.tiempo; //El momento en que saldra es el tiempo actual + lo que tarde
				cliente.cajaALaQueVa = primeraCajaLibre; //Se le asigna la primera caja libre
				//std::cout << "El cliente tarda " << cliente.tiempo << " saldra " << cliente.momentoEnQueSaldra << " y va a la caja " << primeraCajaLibre << std::endl;
				colaClientes.push(cliente); //Se le mete en la cola
				if (primeraCajaLibre<cajas) ++primeraCajaLibre; //Se aumenta la primera caja libre, solo surte efecto cuando hay cajas vacias
				--clientes;
				//Cuando ya no quedan clientes a tratar, la primera caja libre sera la que hay en la cima de la cola
				if (clientes == 0) primeraCajaLibre = colaClientes.top().cajaALaQueVa; 
			}
			//Si no, se actualiza el tiempo y se saca el mas prioritario
			else {
				tiempo = colaClientes.top().momentoEnQueSaldra; //Se suma el tiempo de espera del cliente
				primeraCajaLibre = colaClientes.top().cajaALaQueVa; //Se asigna que la nueva caja disponible es la que ocupaba el cliente
				colaClientes.pop(); //Se saca el cliente de la cola
			}
		}
		//if (colaClientes.size() == cajas) std::cout << colaClientes.top().cajaALaQueVa +1<< std::endl;
		std::cout << primeraCajaLibre +1 << std::endl;
	}
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif // !DOMJUDGE
	while (resuelveCaso());
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif // !DOMJUDGE

}