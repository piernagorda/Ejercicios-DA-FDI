#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"


class ArbolLibre {
public:

	ArbolLibre(Grafo miGrafo) :visitados(miGrafo.V(), false), anteriores(miGrafo.V()) {
		_esLibre = true;
		int contador = 0;
		if (miGrafo.A() == 0) _esLibre = false; //Si no hay aristas es falso
		else {
			bool sol = resolver(miGrafo, 0, contador);
			if (sol) {
				if (contador != miGrafo.V())_esLibre = false;
			}
		}

	}

	bool esLibre() const { return _esLibre; }
private:
	std::vector<bool> visitados;
	std::vector<int> anteriores;
	bool _esLibre;

	bool resolver(Grafo const& miGrafo, int v, int& contador) {
		visitados[v] = true; //Marcamos a true
		++contador; //Aumentamos el contador
		//Recorremos los adyacentes del vertice
		for (int i = 0; i < miGrafo.ady(v).size(); ++i) {
			if (!visitados[miGrafo.ady(v)[i]]) { //Si no está visitado nos metemos a el
				anteriores[miGrafo.ady(v)[i]] = v; //Marcamos como que su anterior es el vertice actual v
				resolver(miGrafo, miGrafo.ady(v)[i], contador);
			}
			else {
				//No entiendo esta puta condicion
				std::cout << miGrafo.ady(v)[i] << std::endl;
				for (int i = 0; i < anteriores.size(); ++i) std::cout << anteriores[i] << " ";
				std::cout << "\n";
				if (anteriores[v] != miGrafo.ady(v)[i]) {
					_esLibre = false;
					return false;
				}
			}
			//Sino, pasamos al siguiente
		}
		return true;
	}

};

bool resuelveCaso() {
	int v, a;
	std::cin >> v >> a;
	if (!std::cin) return false;
	Grafo miGrafo(v);
	for (int i = 0; i < a; ++i) {
		int a, b;
		std::cin >> a >> b;
		miGrafo.ponArista(a, b);
	}
	ArbolLibre miArbol(miGrafo);
	if (miArbol.esLibre()) std::cout << "SI" << std::endl;
	else std::cout << "NO" << std::endl;
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