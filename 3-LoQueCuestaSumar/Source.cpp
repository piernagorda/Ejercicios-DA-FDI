#include <iostream>
#include <fstream>
#include <queue>

int resolver(std::priority_queue<int, std::vector<int>, std::greater<int> > miCola) {
	int esfuerzo = 0;
	int suma = 0;
	if (miCola.size() <= 1) return 0;
	else {
		while (miCola.size()>1) {
			int a = miCola.top(); miCola.pop();
			int b = miCola.top(); miCola.pop();
			suma = a + b;
			esfuerzo += suma;
			miCola.push(suma);
		}
		return esfuerzo;
	}
}

bool resuelveCaso() {
	int n;
	std::cin >> n;
	if (n == 0) return false;
	std::priority_queue<int, std::vector<int>, std::greater<int> > miCola;
	for (int i = 0; i < n; ++i) {
		int a;
		std::cin >> a;
		miCola.push(a);
	}
	miCola.pop();
	std::cout << miCola.top() << std::endl;
	std::cout << resolver(miCola) << std::endl;
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

