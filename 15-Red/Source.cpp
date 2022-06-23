#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Grafo.h"

class NodosNoAlcanzables {
public:
	NodosNoAlcanzables(Grafo const& miGrafo, int nodoIni, int TTL):visitados(miGrafo.V(), false), distancias(miGrafo.V(), -1) {
		std::queue<int> miCola;
		_TTL = TTL;
		bfs(miGrafo, miCola, nodoIni);
	}

	int noAlcanzables() {
		int contador = 0;
		for (int i = 0; i < distancias.size(); ++i) {
			if (distancias[i] > _TTL || distancias[i]==-1)++contador;
		}
		return contador;
	}

private:
	std::vector<bool> visitados;
	std::vector<int> distancias;
	int _TTL;

	void bfs(Grafo const& miGrafo, std::queue<int> &miCola,int nodoIni) {

		visitados[nodoIni] = true;
		distancias[nodoIni] = 0;
		miCola.push(nodoIni);

		while (!miCola.empty()) {
			int cima = miCola.front();
			miCola.pop();
			for (int w : miGrafo.ady(cima)) {
				if (!visitados[w]) {
					visitados[w] = true;
					distancias[w] = distancias[cima] + 1;
					miCola.push(w);
				}
			}
		}
		
	}

};

bool resuelveCaso() {
	int vertices, aristas;
	std::cin >> vertices >> aristas;
	if (!std::cin) return false;
	Grafo miGrafo(vertices);
	for (int i = 0; i < aristas; ++i) {
		int a, b;
		std::cin >> a >> b;
		miGrafo.ponArista(a - 1, b - 1);
	}
	int k, nodoIni, TTL;
	std::cin >> k;
	for (int i = 0; i < k; ++i){
		std::cin >> nodoIni >> TTL;
		--nodoIni;
		NodosNoAlcanzables miRed(miGrafo, nodoIni, TTL);
		std::cout << miRed.noAlcanzables() << std::endl;
	}
	std::cout << "---" << std::endl;
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