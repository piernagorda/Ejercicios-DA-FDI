#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Digrafo.h"

class OrdenTareas {
public:
	
	OrdenTareas(Digrafo const& miDigrafo): visitados(miDigrafo.V(), false), apilados(miDigrafo.V(), false), _esPosible(true) {
		for (int i = 0; i < miDigrafo.V(); ++i) {
			if (!visitados[i]) { //El vertice no se ha visitado
				dfs(miDigrafo, i);
			}
		}
	}

	bool esPosible() {
		return _esPosible;
	}

	void mostrarOrden() {
		for (int i = 0; i < miCola.size(); ++i) std::cout << miCola[i] + 1 << " ";
		std::cout << "\n";
	}

private:

	bool _esPosible;
	std::deque<int> miCola;
	std::vector<bool> visitados;
	std::vector<bool> apilados;

	void dfs(Digrafo const& miDigrafo, int vertice) {
		visitados[vertice] = true;
		apilados[vertice] = true;
		for (auto w : miDigrafo.ady(vertice)) {
			if (!visitados[w]) {
				dfs(miDigrafo, w);
			}
			else {
				if (apilados[w]) {
					_esPosible = false;
					break;
				}
			}
		}
		apilados[vertice] = false;
		miCola.push_back(vertice);
	}
};

bool resuelveCaso() {
	int vertices, aristas;
	std::cin >> vertices >> aristas;
	if (!std::cin) return false;
	Digrafo miDigrafo(vertices);
	for (int i = 0; i < aristas; ++i) {
		int origen, destino;
		std::cin >> origen >> destino; //La tarea  origen ha de hacerse antes
		miDigrafo.ponArista(origen-1, destino-1);
	}
	OrdenTareas misTareas(miDigrafo);
	if (misTareas.esPosible()) misTareas.mostrarOrden();
	else std::cout << "Imposible" << std::endl;
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