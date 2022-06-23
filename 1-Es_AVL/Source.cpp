#include <iostream>
#include <fstream>
#include "bintree.h"

bool resuelveCaso() {
	bintree<int> arbol;
	arbol.
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