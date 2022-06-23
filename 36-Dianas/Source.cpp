#include <iostream>
#include <fstream>
#include <vector>

const int INF = 1000;

class Problema {
public:
    Problema(std::vector<int> const& valoresSectores, int puntuacionObjetivo): _puntuacionObjetivo(puntuacionObjetivo), _esPosible(false) {
        numeroMinimoTiradas(valoresSectores);
    }

    bool esPosible() const { return _esPosible; }
    int minimoNumeroTiradas() const{ return _minimoNumeroTiradas; }
    void printTiradas() const { for (int i = 0; i < vSol.size(); ++i)std::cout << vSol[i] << " "; }

private:
    int _puntuacionObjetivo;
    int _minimoNumeroTiradas;
    bool _esPosible;
    std::vector<int> vSol;

    void numeroMinimoTiradas(std::vector<int> const& valoresSectores) {
        std::vector<int> sumatorio(_puntuacionObjetivo+1, INF);
        sumatorio[0] = 0;
        for (int i = 0; i < valoresSectores.size(); ++i) {
            int valorSector = valoresSectores[i];
            for (int j = valorSector; j <= _puntuacionObjetivo;++j) {
                sumatorio[j] = std::min(sumatorio[j], sumatorio[j - valorSector] + 1);
            }
        }
        if (sumatorio[_puntuacionObjetivo] != INF) {
            _esPosible = true;
            _minimoNumeroTiradas = sumatorio[_puntuacionObjetivo];
            //Reconstruccion Solucion
            int i = valoresSectores.size() - 1; //Cogemos el valor mas alto
            int j = _puntuacionObjetivo; //J empieza siendo la puntuacion objetivo
            while (j > 0) {
                //Si el valor mas alto <=j y sumatorio[j] == sumatorio[j-valor
                //Valores: 10 15 20 25 30; la j será 30 hasta
                if (valoresSectores[i] <= j && sumatorio[j] == sumatorio[j - valoresSectores[i]] + 1) {
                    vSol.push_back(valoresSectores[i]);
                    j = j - valoresSectores[i];
                }
                else--i;
            }
        }
    }

};

bool resuelveCaso() {
    int valorDestino, sectores;
    std::cin >> valorDestino >> sectores;
    if (!std::cin)return false;
    std::vector<int> valoresSectores(sectores);
    for (int i = 0; i < sectores; ++i) {
        std::cin >> valoresSectores[i];
    }
    Problema miProblema(valoresSectores, valorDestino);
    if (miProblema.esPosible()) {
        std::cout << miProblema.minimoNumeroTiradas() << ": ";
        miProblema.printTiradas(); std::cout << "\n";
    }
    else std::cout << "Imposible" << std::endl;
    return true;
}

/*
Para cada caso se escribir´a el menor n´umero de dardos necesarios para conseguir la cantidad, separado
por dos puntos de las puntuaciones que permiten conseguir ese valor, ordenadas de mayor a menor y
separadas por espacios.
Si hay varias soluciones, se escribir´a aquella cuya mayor puntuaci´on sea la m´as alta; si a´un siguen
existiendo varias soluciones, se escribir´a aquella cuya segunda mayor puntuaci´on sea la m´as alta; y as´ı
sucesivamente.
Si es imposible conseguir el objetivo con las puntuaciones asignadas a los sectores de la diana, se
escribir´a Imposible
*/
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    while (resuelveCaso());
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
}