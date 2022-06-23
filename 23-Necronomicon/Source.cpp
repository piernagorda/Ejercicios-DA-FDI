#include <iostream>
#include <fstream>
#include <vector>
#include "Digrafo.h"

class Problema {
public:
	Problema(Digrafo const& g) :_acaba(false), _hayCiclos(false), apilados(g.V(), false), _visitados(0), visitados(g.V(), false) {
		dfs(g, 0);
	}

	bool acaba() const { return _acaba; }
	bool hayCiclos() const { return _hayCiclos; }

private:
	bool _acaba;
	bool _hayCiclos;
	int _visitados;
	std::vector<bool> apilados;
	std::vector<bool> visitados;

	void dfs(Digrafo const& g, int vertice) {
		apilados[vertice] = true;
		visitados[vertice] = true;
		++_visitados;
		if (g.ady(vertice).size() == 0 && _visitados==g.V()) _acaba = true;
		else {
			if (g.ady(vertice).size() == 0 && _visitados < g.V()) _acaba = true;
			else {
				for (auto w : g.ady(vertice)) {
					if (!visitados[w]) 	dfs(g, w);
					else if (apilados[w])_hayCiclos = true;
				}
			}
		}
		apilados[vertice] = false;
	}
};

bool resuelveCaso() {
	int L;
	std::cin >> L;
	if (!std::cin) return false;
	Digrafo miDigrafo(L+1);
	for (int i = 0; i < L; ++i) {
		char tipoInstruccion;
		std::cin >> tipoInstruccion;
		if (tipoInstruccion == 'A') {
			miDigrafo.ponArista(i, i + 1);
		}
		else if (tipoInstruccion == 'J') {
			int direccion;
			std::cin >> direccion;
			miDigrafo.ponArista(i, direccion-1);
		}
		else {
			int direccion;
			std::cin >> direccion;
			miDigrafo.ponArista(i, direccion-1);
			miDigrafo.ponArista(i, i + 1);
		}
	}
	

	Problema miProblema(miDigrafo);
	if (!miProblema.acaba()) std::cout << "NUNCA" << std::endl;
	else {
		if (miProblema.hayCiclos()) std::cout << "A VECES" << std::endl;
		else std::cout << "SIEMPRE" << std::endl;
	}
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while (resuelveCaso());
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
}
