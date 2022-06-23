#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "PriorityQueue.h"
#include "IndexPQ.h"
#include "GrafoValorado.h"

const int INF = 1000000000;
//El problema es: coincide el ARM con el camino de coste minimo?

class Problema {
public:
	Problema(GrafoValorado<int> const& g, int ini, int fin): _ini(ini),_fin(fin), ultimo(g.V()), distanciasParciales(g.V(), INF), pq(g.V()), _coinciden(false) {
		dijsktra(g);
		bfs(g);
	}

	bool hayCamino() const{ return distanciasParciales[_fin] < INF;}
	bool coinciden()const { return _numMinimoAristasARM == distanciasParciales[_fin]; }
	int minimoCoste()const { return distanciasParciales[_fin]; }

private:
	int _ini;
	int _fin;
	int _numMinimoAristasARM;
	bool _coinciden;
	std::vector<int> ultimo;
	std::vector<int> distanciasParciales;
	IndexPQ<int> pq;
	void dijsktra(GrafoValorado<int> const& g) {
		ultimo[_ini] = _ini;
		distanciasParciales[_ini] = 0;
		pq.push(_ini, 0);
		while (!pq.empty()) {
			int v = pq.top().elem;
			pq.pop();
			for (auto w : g.ady(v)) relajar(w, v);
		}
	}

	void relajar(Arista<int> arista, int origen) {
		int otro = arista.otro(origen);
		if (distanciasParciales[otro] > distanciasParciales[origen] + arista.valor()) {
			distanciasParciales[otro] = distanciasParciales[origen] + arista.valor();
			ultimo[otro] = origen;
			pq.update(otro, distanciasParciales[otro]);
		}
	}
	//Pendiente
	void bfs(GrafoValorado<int> const& g) {
	
	}

};

bool resuelveCaso() {
	int aristas, vertices;
	std::cin >> vertices >> aristas;
	if (!std::cin)return false;

	GrafoValorado<int> miGrafo(vertices);
	
	for (int i = 0; i < aristas; ++i) {
		int origen, destino, valor;
		std::cin >> origen >> destino >> valor;
		Arista<int> miArista(origen-1, destino-1, valor);
		miGrafo.ponArista(miArista);
	}
	int k; std::cin >> k;
	for (int i = 0; i < k; ++i) {
		int origen, destino;
		std::cin >> origen >> destino;
		Problema miProblema(miGrafo, origen-1, destino-1);
		if (miProblema.hayCamino()) {
			std::cout << miProblema.minimoCoste() << " ";
			if (miProblema.coinciden()) std::cout << "SI" << std::endl;
			else std::cout << "NO" << std::endl;
		}
		else std::cout << "SIN CAMINO" << std::endl;
	}
	std::cout << "---" << std::endl;

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while (resuelveCaso());
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}