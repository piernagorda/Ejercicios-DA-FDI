#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

struct tDatos {
	long int ID;
	int intervalo;
	int invervaloCola;
};

bool operator<(tDatos a, tDatos b) {
	return a.invervaloCola < b.invervaloCola || (a.invervaloCola ==b.invervaloCola && a.ID < b.ID);
}

bool operator>(tDatos a, tDatos b) {
	return a.invervaloCola > b.invervaloCola || (a.invervaloCola == b.invervaloCola && a.ID > b.ID);
}

bool resuelveCaso() {
	int n, k;
	std::cin >> n;
	if (n == 0) return false;
	std::priority_queue<tDatos, std::vector<tDatos>, std::greater<tDatos>> miCola;

	for (int i = 0; i < n; ++i) {
		long int idTemp, intervalo;
		std::cin >> idTemp >> intervalo;
		miCola.push({ idTemp, intervalo, intervalo });
	}
	std::cin >> k;
	int intervaloActual = 0;
	for (int i = 0; i < k; ++i) {
		tDatos primeroEnCola = miCola.top();
		miCola.pop();
		intervaloActual = primeroEnCola.invervaloCola;
		std::cout << primeroEnCola.ID << "\n";
		primeroEnCola.invervaloCola += primeroEnCola.intervalo;
		miCola.push(primeroEnCola);
	}
	std::cout << "---\n";
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