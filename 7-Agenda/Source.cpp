#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

struct tTarea {
	int ini=0;
	int fin=0;
	bool esPeriodica = false;
	int periodo;
};

bool operator<(tTarea a, tTarea b) {
	return a.ini < b.ini || a.ini==b.fin && a.fin<b.fin;
}

bool hayConflictos(PriorityQueue<tTarea>& miCola, int T) {
	int tiempo = 0;
	bool hayConflicto = false;
	while (tiempo < T && !hayConflicto) {
		if (miCola.size()>1) {
			tTarea tareaPrioritaria = miCola.top(); //Copiamos la tarea prioritaria
			miCola.pop(); //La sacamos
			if (tareaPrioritaria.ini < T) { //Si la tarea a mirar empieza en el intervalo observable nos importa, sino no y acabamos
				if (miCola.top().ini < T && tareaPrioritaria.fin > miCola.top().ini) {
					hayConflicto = true;
				}
				else {
					if (tareaPrioritaria.esPeriodica) {
						//Cogemos la tarea, le ajustamos el tiempo de inicio y fin para que se vuelva a repetir y la metemos en cola
						tareaPrioritaria.ini += tareaPrioritaria.periodo;
						tiempo = tareaPrioritaria.fin;
						tareaPrioritaria.fin += tareaPrioritaria.periodo;
						miCola.push(tareaPrioritaria);
					}
					else tiempo = tareaPrioritaria.fin;
				}
			}
			else tiempo = T;
		}
		else tiempo = T;
	}
	return hayConflicto;
}

bool resuelveCaso() {
	int N, M, T;
	std::cin >> N >> M >> T;
	if (!std::cin || N==0 && M==0) return false;
	PriorityQueue<tTarea> miCola;
	//Metemos las tareas unicas 
	for (int i = 0; i < N; ++i) {
		int ini, fin;
		std::cin >> ini >> fin;
		tTarea temp = { ini, fin, false, 0 };
		miCola.push(temp);
	}
	//Metemos las periodicas
	for (int i = 0; i < M; ++i) {
		int ini, fin, periodo;
		std::cin >> ini >> fin >> periodo;
		tTarea temp = { ini, fin, true, periodo };
		miCola.push(temp);
	}

	if (hayConflictos(miCola, T)) std::cout << "SI" << std::endl;
	else std::cout << "NO" << std::endl;

	/* MOSTRAR COLA
	for (int i = 0; i < N+M; ++i) {
		std::cout << miCola.top().ini << " "<<miCola.top().fin<<std::endl;
		miCola.pop();
	}
	*/
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
