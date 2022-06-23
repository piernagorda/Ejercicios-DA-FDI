#include <iostream>
#include <fstream>
#include <vector>

struct tBombilla {
	int potencia, coste;
};

const int INF = 1000000;
/* --------------------------------------------------VERSION CON MATRIZ-----------------------------------------------------

void resolver(int  potenciaMax, int potenciaMinima, std::vector<tBombilla> listaBombillas) {
	std::vector<std::vector<int>> matriz(listaBombillas.size() + 1, std::vector<int>(potenciaMax +1, INF));
	for (int i = 0; i <= listaBombillas.size(); ++i) matriz[i][0] = 0;
	int posAcceso = 0;
	for (int i = 1; i <= listaBombillas.size(); ++i) {
		int costeBombillaActual = listaBombillas[posAcceso].coste;
		int potenciaBombillaActual = listaBombillas[posAcceso].potencia;
		for (int j = 1; j < potenciaBombillaActual; ++j) matriz[i][j] = matriz[i - 1][j];
		for (int j = potenciaBombillaActual; j <= potenciaMax; ++j) {
			matriz[i][j] = std::min(matriz[i - 1][j], matriz[i][j - potenciaBombillaActual] + costeBombillaActual);
		}
		++posAcceso;
	}
	int costeMin = INF;
	int potencia = INF;
	/*MOSTRAR MATRIZ
	for (int i = 0; i <= listaBombillas.size(); ++i) {
		for (int j = 0; j <= potenciaMax; ++j) {
			if (matriz[i][j] == INF) std::cout << "INF \t";
			else std::cout << matriz[i][j] << " \t";
		}
		std::cout << "\n";
	}
	

	for (int i = potenciaMinima; i <= potenciaMax; ++i) {
		if (matriz[listaBombillas.size()][i] < costeMin) {
			costeMin = matriz[listaBombillas.size()][i];
			potencia = i;
		}
	}
	if (costeMin != INF) {
		std::cout << costeMin <<" "<< potencia << std::endl;
	}
	else std::cout << "IMPOSIBLE \n";
}
*/

//Version con vector
void resolver(int  potenciaMax, int potenciaMinima, std::vector<tBombilla> listaBombillas) {
	std::vector<int> matriz(potenciaMax + 1, INF);
	matriz[0] = 0;
	for (int i = 0; i < listaBombillas.size(); ++i) {
		int costeBombillaActual = listaBombillas[i].coste;
		int potenciaBombillaActual = listaBombillas[i].potencia;
		for (int j = potenciaBombillaActual; j <= potenciaMax; ++j) {
			matriz[j] = std::min(matriz[j], matriz[j - potenciaBombillaActual] + costeBombillaActual);
		}
	}
	int costeMin = INF, potencia = INF;
	for (int i = potenciaMinima; i <= potenciaMax; ++i) {
		if (matriz[i] < costeMin) {
			costeMin = matriz[i];
			potencia = i;
		}
	}
	if (costeMin != INF) std::cout << costeMin << " " << potencia << std::endl;
	else std::cout << "IMPOSIBLE \n";
}

bool resuelveCaso() {
	int nTiposBombillas, potenciaMax, potenciaMinima;
	std::cin >> nTiposBombillas >> potenciaMax >> potenciaMinima;
	if (!std::cin) return false;
	std::vector<tBombilla> listaBombillas;
	for (int i = 0; i < nTiposBombillas; ++i) {
		int potencia; std::cin >> potencia;
		listaBombillas.push_back({ potencia, 0 });
	}
	for (int i = 0; i < nTiposBombillas; ++i) {
		int coste; std::cin >> coste;
		listaBombillas[i].coste = coste;
	}

	resolver(potenciaMax, potenciaMinima, listaBombillas);
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