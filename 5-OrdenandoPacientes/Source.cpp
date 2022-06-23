#include <iostream>
#include <fstream>
#include <queue>
#include <string>
//La STL: cola de maximos, hay que definir el operdor <
//Si se quiere cola de minimos, hay que definir el operador >
struct tDatos {
	std::string nombre;
	int gravedad;
	int turno;
};

bool operator<(tDatos a, tDatos b) {
	return a.gravedad < b.gravedad || (a.gravedad == b.gravedad && a.turno > b.turno);
}

bool resuelveCaso() {
	int n;
	std::cin >> n;
	if (n == 0) return false;
	
	std::priority_queue<tDatos> miCola;

	for (int i = 0; i < n; ++i) {
		char tipo; 
		std::cin >> tipo;
		if (tipo == 'I') {
			std::string paciente;
			int gravedad;
			std::cin >> paciente >> gravedad;
			miCola.push({ paciente, gravedad, i });
		}
		else {
			if (!miCola.empty()){
				std::cout << miCola.top().nombre << "\n";
				miCola.pop();
			}
		}
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