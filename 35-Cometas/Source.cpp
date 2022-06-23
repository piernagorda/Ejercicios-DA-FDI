#include <iostream>
#include <fstream>
#include <vector>

const int INF = 1000000000;

struct tCuerda {
	int coste;
	int longitud;
};

class Problema {
public:
	Problema(std::vector<tCuerda> const& listaCuerdas, int const& longitudDeseada) :
		_listaCuerdas(listaCuerdas), _longitudDeseada(longitudDeseada), _esPosible(false), _formasConseguirlo(0), _cuerdasMinimas(0), _costeMinimo(0) {
		formasDeConseguirlo();
		cuerdasMinimasInt();
		costeMinimoInt();
	}

	bool esPosible() const { return _esPosible; }
	int formasConseguirlo() const { return _formasConseguirlo; }
	int cuerdasMinimas() const { return _cuerdasMinimas; }
	int costeMinimo() const { return _costeMinimo; }

private:

	std::vector<tCuerda> const& _listaCuerdas;
	int const& _longitudDeseada;
	bool _esPosible;
	int _formasConseguirlo;
	int _cuerdasMinimas;
	int _costeMinimo;

	void formasDeConseguirlo() {
		std::vector<int> sumatorio(_longitudDeseada + 1, 0);
		sumatorio[0] = 1;
		for (int i = 0; i < _listaCuerdas.size(); ++i) {
			int longitud = _listaCuerdas[i].longitud;
			for (int j = _longitudDeseada; j >= longitud; --j) {
				sumatorio[j] += sumatorio[j - longitud];
			}
		}
		if (sumatorio[_longitudDeseada] != 0) {
			_esPosible = true;
			_formasConseguirlo = sumatorio[_longitudDeseada];
		}
	}

	void cuerdasMinimasInt() {
		std::vector<long long int> sumatorio(_longitudDeseada + 1, INF);
		sumatorio[0] = 0;
		for (int i = 0; i < _listaCuerdas.size(); ++i) {
			int longitud = _listaCuerdas[i].longitud;
			for (int j = _longitudDeseada; j >= longitud; --j) {
				sumatorio[j] = std::min(sumatorio[j], sumatorio[j - longitud])+1;
			}
		}
		_cuerdasMinimas = sumatorio[_longitudDeseada];
	}

	void costeMinimoInt() {
		std::vector<long long int> sumatorio(_longitudDeseada + 1, INF);
		sumatorio[0] = 0;
		for (int i = 0; i < _listaCuerdas.size(); ++i) {
			int longitud = _listaCuerdas[i].longitud;
			int coste = _listaCuerdas[i].coste;
			for (int j = _longitudDeseada; j >= longitud; --j) {
				sumatorio[j] = std::min(sumatorio[j], sumatorio[j - longitud]+coste);
			}
		}
		_costeMinimo = sumatorio[_longitudDeseada];
	}

};

bool resuelveCaso(){
	int numeroCuerdas, longitudDeseada;
	std::cin >> numeroCuerdas >> longitudDeseada;
	if (!std::cin) return false;
	std::vector<tCuerda> cuerdas(numeroCuerdas);
	for (int i = 0; i < numeroCuerdas; ++i) {
		tCuerda temp;
		std::cin >> temp.longitud >> temp.coste;
		cuerdas[i] = temp;
	}
	Problema miProblema(cuerdas, longitudDeseada);
	if (miProblema.esPosible()) {
		std::cout << "SI " << miProblema.formasConseguirlo() << " " << miProblema.cuerdasMinimas() << " " << miProblema.costeMinimo() << std::endl;
	}
	else std::cout << "NO" << std::endl;
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