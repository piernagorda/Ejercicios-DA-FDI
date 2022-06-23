#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Grafo.h"

class Solucion {
public:

	Solucion(int tam): numVisitados(0), visitados(tam, false), alcanceVertices(tam, 1){
	}
	
	//Guardar Vector de tamanos de componentes conexas
	void calcularAlcance(Grafo const& miGrafo) {

		for (int i = 0; i < miGrafo.V(); ++i){
			if (!visitados[i]){
				numVisitados = 0;
				dfs(miGrafo, i);
				while (!visitadosEnDFS.empty()) {
					alcanceVertices[visitadosEnDFS.front()] = numVisitados;
					visitadosEnDFS.pop();
				}
			}
		}
		//Mostrar cuantos vertices ha alcanzado cada recorrido
		for (int i = 0; i < miGrafo.V(); ++i) std::cout << alcanceVertices[i] << " ";
	}

private:
	std::vector<bool> visitados;
	std::vector<int> alcanceVertices;
	std::queue<int> visitadosEnDFS;
	int numVisitados;

	void dfs(Grafo const& miGrafo, int vertice) {
		visitados[vertice] = true;
		++numVisitados;
		visitadosEnDFS.push(vertice);
		for (int a : miGrafo.ady(vertice)) {
			if (!visitados[a]) {
				dfs(miGrafo, a);
			}
		}
	}

};

void crearGrupo(int n, Grafo& miGrafo) {
	int uno, dos;
	std::cin >> uno >> dos;
	miGrafo.ponArista(uno-1, dos-1);
	n -= 2;
	for (int i = 0; i < n; ++i) {
		int siguiente;
		std::cin >> siguiente;
		miGrafo.ponArista(dos-1, siguiente-1);
		dos = siguiente;
	}
}

bool resuelveCaso() {
	int v, grupos;
	std::cin >> v >> grupos;
	if (!std::cin) return false;
	
	Grafo miGrafo(v);

	for (int i = 0; i < grupos; ++i) {
		int n; //Tam grupo
		std::cin >> n;
		if (n > 1) crearGrupo(n, miGrafo);
		else if (n == 1) {
			int temp; std::cin >> temp;
		}
	}
	Solucion sol(miGrafo.V());
	
	sol.calcularAlcance(miGrafo);
	
	std::cout << "\n";

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
