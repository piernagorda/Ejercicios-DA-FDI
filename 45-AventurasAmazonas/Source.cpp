#include <iostream>
#include <fstream>
#include <vector>

const int INF = 100000000;

void resolver(std::vector<std::vector<int>> &dist, int poblados) { //Tamano matriz: 4x5 
	for (int k = 0; k < dist.size(); k++) {
		// Pick all vertices as source one by one
		for (int i = 0; i < dist.size(); i++) {
			// Pick all vertices as destination for the
			// above picked source
			for (int j = 0; j <= dist.size(); j++) {
				// If vertex k is on the shortest path from
				// i to j, then update the value of
				// dist[i][j]
				if (dist[i][j] > (dist[i][k] + dist[k][j])&& (dist[k][j] != INF && dist[i][k] != INF))
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
	for (int i = 0; i < poblados - 1; ++i) {
		for (int j = i+1; j < poblados; ++j) {
			std::cout << dist[i][j] << " ";
		}
		std::cout << "\n";
	}
}

bool resuelveCaso() {
	int poblados;
	std::cin >> poblados;
	if (!std::cin)return false;
	std::vector<std::vector<int>> distanciasPoblados(poblados-1, std::vector<int>(poblados, INF));
	
	for (int i = 0; i < poblados - 1; ++i) {
		int j = i + 1;
		distanciasPoblados[i][j-1] = 0;
		for (j; j < poblados; ++j) {
			std::cin >> distanciasPoblados[i][j];
		}
	}
	
	/*
	
	*/
	resolver(distanciasPoblados, poblados);
	
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
#endif // 

}