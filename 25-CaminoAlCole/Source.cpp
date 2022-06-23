#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"
#include "IndexPQ.h"

const int INF = 1000000000;

class Problema {
public:
	Problema(GrafoValorado<int> const& g)
		: _distanciasParciales(g.V(), INF), pq(g.V()), _caminoArrastrados(g.V()), _caminos(0) {
		dijsktra(g);
	}

	int numCamino() const { return _caminos; }

private:
	int _caminos; //Esta nos guarda el numero de caminos
	std::vector<int> _distanciasParciales;
	std::vector<int> _caminoArrastrados;
	IndexPQ<int> pq;

	void dijsktra(GrafoValorado<int> const& g) {
		_distanciasParciales[0] = 0;
		pq.update(0,0);
		_caminoArrastrados[0] = 1;
		while (!pq.empty()) {
			int v = pq.top().elem;
			pq.pop();
			for (auto w : g.ady(v)) relajar(w, v);
		}
		//El numero de caminos total sera el numero de caminos arrastrados
		_caminos=_caminoArrastrados[g.V() - 1];
	}

	void relajar(Arista<int> const& arista, int origen) {
		int destino = arista.otro(origen);
		//Si la distancia que hay en el destino es mayor que la que aportamos -> Actualizamos la distancia al destino
		if (_distanciasParciales[origen] + arista.valor() < _distanciasParciales[destino]) {
			
			_caminoArrastrados[destino] = _caminoArrastrados[origen]; //Actualizamos el numero de caminos que llegan hasta el
			_distanciasParciales[destino] = _distanciasParciales[origen] + arista.valor(); //Actualizamos la distancia hacia ese vertice
			pq.update(destino, _distanciasParciales[destino]); //Actualizamos prioridad del destino en la cola
		
		}
		//Sino, si son iguales -> hay otro camino igual!
		else if (_distanciasParciales[origen] + arista.valor() == _distanciasParciales[destino]) _caminoArrastrados[destino] += _caminoArrastrados[origen];
	}

};

bool resuelveCaso() {
	int vertices, aristas;
	std::cin >> vertices >> aristas;
	if (!std::cin) return false;
	GrafoValorado<int> miGrafo(vertices);
	for (int i = 0; i < aristas; ++i) {
		int v, w, valor;
		std::cin >> v >> w >> valor;
		Arista<int> miArista(v-1, w-1, valor);
		miGrafo.ponArista(miArista);
	}
	Problema miProblema(miGrafo);
	std::cout << miProblema.numCamino() << std::endl;
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
#endif
}