#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"

class Amigos {
public:
	Amigos(Grafo const& miGrafo): _maxAmigos(0), visitados(miGrafo.V(), false) {
		for (int i = 0; i < miGrafo.V(); ++i) {
			if (!visitados[i]) {
				int contador = 0;
				resolver(miGrafo, i, contador);
				if (contador > _maxAmigos) _maxAmigos = contador;
			}
		}
	}

	int grupoAmigosMasGrande() const { return _maxAmigos; }
private:
	
	int _maxAmigos;
	std::vector<bool> visitados;

	void resolver(Grafo const& miGrafo, int v, int &contador) {
		visitados[v] = true;
		++contador;
		for (int i = 0; i < miGrafo.ady(v).size(); ++i) {
			if (!visitados[miGrafo.ady(v)[i]]) resolver(miGrafo, miGrafo.ady(v)[i], contador);
		}
	}

};

void resuelveCaso() {
	int vertices, aristas;
	std::cin >> vertices >> aristas;
	Grafo miGrafo(vertices);
	for (int i = 0; i < aristas; ++i) {
		int a, b;
		std::cin >> a >> b;
		miGrafo.ponArista(a-1, b-1);
	}
	Amigos mapaAmigos(miGrafo);
	std::cout << mapaAmigos.grupoAmigosMasGrande() << std::endl;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif // !DOMJUDGE
	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i) resuelveCaso();
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif // !DOMJUDGE

}