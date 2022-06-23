#include <iostream>
#include <fstream>
#include <vector>

bool resuelveCaso() {
	int dimensionTablero;
	std::cin >> dimensionTablero;
	if (!std::cin) return false;
	std::vector<std::vector<int>> tablero(dimensionTablero, std::vector<int>(dimensionTablero, 0));

	for (int i = 0; i < dimensionTablero; ++i) {
		for (int j = 0; j < dimensionTablero; ++j) {
			int temp; std::cin >> temp;
			tablero[i][j] = temp;
		}
	}
	//Mostrar max puntuacion y pos
	for (int i = 1; i < tablero.size()-1; ++i) { //Empezamos por fila 1
		for (int j = 0; j < dimensionTablero; ++j) {
			int maximo = 0;
			if (j == 0) maximo = std::max(tablero[i - 1][j], tablero[i - 1][ j + 1]);
			else if (j == dimensionTablero - 1) maximo = std::max(tablero[i - 1][j], tablero[i - 1][j - 1]);
			else {
				maximo = std::max(tablero[i - 1][j - 1], tablero[i - 1][j]);
				maximo = std::max(maximo, tablero[i - 1][j + 1]);
			}
			tablero[i][j] += maximo;
		}
	}
	int posMax = 0;
	int valorMax = 0;
	//En la ultima fila nos quedamos con el maximo, que es el que nos interesa. Se hace en la ultima fila para evitar comprobar en todas las filas
	//si i es la ultima fila o no. 
	for (int i = tablero.size() - 1; i < tablero.size(); ++i) {
		for (int j = 0; j < dimensionTablero; ++j) {
			int maximo = 0;
			if (j == 0) maximo = std::max(tablero[i - 1][j], tablero[i - 1][j + 1]);
			else if (j == dimensionTablero - 1) maximo = std::max(tablero[i - 1][j], tablero[i - 1][j - 1]);
			else {
				maximo = std::max(tablero[i - 1][j - 1], tablero[i - 1][j]);
				maximo = std::max(maximo, tablero[i - 1][j + 1]);
			}
			tablero[i][j] += maximo;
			if (tablero[i][j] > valorMax) {
				valorMax = tablero[i][j];
				posMax = j;
			}
		}
	}
	std::cout << valorMax <<" "<< posMax + 1 << std::endl;
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