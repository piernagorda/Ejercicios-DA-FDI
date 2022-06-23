#include <iostream>
#include <fstream>
#include <vector>
#include "Digrafo.h"

class Sumidero {
public:
    Sumidero(Digrafo const& migrafo):_esSumidero(false), _verticeSumidero(-1), entradas(migrafo.V(), 0), comprobados(migrafo.V(), false) {
        for (int i = 0; i < migrafo.V(); ++i) {
            if (!comprobados[i]) dfs(migrafo, i);
        }
        for (int i = 0; i < entradas.size(); ++i) {
            if (entradas[i] == migrafo.V() - 1 && migrafo.ady(i).size()==0) {
                _esSumidero = true;
                _verticeSumidero = i;
                break;
            }
        }
    }

    bool esSumidero() {
        return _esSumidero;
    }

    int verticeSumidero() const { return _verticeSumidero; }

private:
    bool _esSumidero;
    int _verticeSumidero;
    std::vector<int> entradas;
    std::vector<bool> comprobados;

    void dfs(Digrafo const& g, int vertice) {
        comprobados[vertice] = true;
        for (auto w : g.ady(vertice)) {
            entradas[w] += 1;
            if (!comprobados[w]) {
                dfs(g, w);
            }
        }
    }
};

bool resuelveCaso() {
    int vertices, aristas;
    std::cin >> vertices >> aristas;
    if (!std::cin) return false;
    Digrafo migrafo(vertices);
    for (int i = 0; i < aristas; ++i) {
        int origen, destino;
        std::cin >> origen >> destino;
        migrafo.ponArista(origen, destino);
    }
    Sumidero miSumidero(migrafo);
    if (miSumidero.esSumidero()) std::cout << "SI " << miSumidero.verticeSumidero() << std::endl;
    else std::cout << "NO" << std::endl;
    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (resuelveCaso());
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}