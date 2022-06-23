#include <iostream>
#include <fstream>
#include <vector>
#include <string>

/*
Caso base: LCS(a, 0) = 0; LCS(0, b) = 0 -> Alguna de las dos cadenas es vacia -> no hay subsecuencias comunes
Caso recursivo: 
			{	1 + LCS(a-1, b-1) si a[fin] == b[fin]
LCS(a, b) = {
			{	max(LCS(a, b-1), LCS(a-1, b) si a[fin] != b[fin]

Ver este video para entender bien: https://www.youtube.com/watch?v=ASoaQq66foQ
*/

//Nota: tiene que mostrarse una solucion VALIDA, no la que pone el problema solamente
//		Para MATAMOSCAS - AMAPOLA vale con MAOA, porque es de longitud maxima. AAOA tambien lo es

void resolver(std::string palabraA, std::string palabraB) {
	std::vector<std::vector<int>> matriz(palabraB.size() + 1, std::vector<int>(palabraA.size() + 1, 0));

	for (int fila = 1; fila <= palabraB.size(); ++fila) {
		char c = palabraB[fila - 1];
		for (int columna = 1; columna <= palabraA.size(); ++columna) {
			if (palabraA[columna - 1] == c) matriz[fila][columna] = matriz[fila - 1][columna - 1] + 1;
			else matriz[fila][columna] = std::max(matriz[fila - 1][columna], matriz[fila][columna - 1]);
		}
	}

	//Mostrar matriz
	/*
	for (int i = 0; i <= palabraB.size(); ++i) {
		for (int j = 0; j <= palabraA.size(); ++j) {
			std::cout << matriz[i][j] << " ";
		}
		std::cout << "\n";
	}
	*/
	//Reconstruccion
	std::vector<char> comun;
	int fila = palabraB.size();
	int columna = palabraA.size();
	while (fila > 0 && columna > 0) {
		//Si el valor de la casilla es igual al de arriba y abajo -> vamos arriba
		if (matriz[fila][columna] == matriz[fila - 1][columna] && matriz[fila][columna] == matriz[fila][columna - 1]) --fila;
		//Si el valor de la casilla es mayor que arriba y abajo -> es una letra coincidente, la metemos y subimos en diagonal
		else if (matriz[fila][columna] > matriz[fila - 1][columna] && matriz[fila][columna] > matriz[fila][columna - 1]) {
			comun.push_back(palabraB[fila - 1]);
			--fila;
			--columna;
		}
		//Si la casilla es igual a la de arriba pero mayor que la de la izq -> arriba
		else if (matriz[fila][columna] == matriz[fila - 1][columna] && matriz[fila][columna] > matriz[fila][columna - 1]) --fila;
		//Si la casilla es igual a la de la izq pero mayor que la de arriba -> izq
		else if (matriz[fila][columna] > matriz[fila - 1][columna] && matriz[fila][columna] == matriz[fila][columna - 1]) --columna;
	}

	for (int i = comun.size()-1; i >=0; --i) std::cout << comun[i];
	std::cout << "\n";

}

bool resuelveCaso() {
	std::string palabraA, palabraB;
	std::cin >> palabraA >> palabraB;
	if (!std::cin) return false;
	resolver(palabraA, palabraB);
	//resolver(palabraB, palabraA);
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