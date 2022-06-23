#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"

const int INF = 1000000;

class SolucionProblema {
public:
    
    SolucionProblema(GrafoValorado<int> const& g, int origen, int destino, int anchoCamion): 
        visitados(g.V(), false), _esPosible(false), _anchoCamion(anchoCamion), _destino(destino){
        dfs(g, origen);
    }

    void esPosible() {
        if (_esPosible) std::cout << "SI" << std::endl;
        else std::cout << "NO" << std::endl;
    }

private:
    std::vector<bool> visitados;
    bool _esPosible;
    int _anchoCamion;
    int _destino;

    void dfs(GrafoValorado<int> const& g, int origen) {
        visitados[origen] = true;
        for (auto w : g.ady(origen)) {
            int otro = w.otro(origen);
            int valor = w.valor();
            if (otro == _destino) { //Si el siguiente es el destino
                if (valor >= _anchoCamion) { //Si el ancho de la calle lo permites
                    visitados[otro] = true;
                    _esPosible = true;
                }
            }
            else { //Si no es el vertice destino
                if (!visitados[otro]) {//Si no esta visitado comprobamos
                    if (valor >= _anchoCamion) { //Si se puede pasar por esa calle vamos
                        dfs(g, otro);
                    }
                }
            }
        }
    }


};

bool resuelveCaso() {
    int vertices, aristas;
    std::cin >> vertices >> aristas;
    if (!std::cin)return false;

    GrafoValorado<int> miGrafo(vertices);
    
    for (int i = 0; i < aristas; ++i) {
        int a, b, valor;
        std::cin >> a >> b >> valor;
        Arista<int> miArista(a-1, b-1, valor);
        miGrafo.ponArista(miArista);
    }
    int numConsultas;
    std::cin >> numConsultas;
    for (int i = 0; i < numConsultas; ++i) {
        int origen, destino, anchoCamion;
        std::cin >> origen>> destino >>anchoCamion;
        SolucionProblema miSolucion(miGrafo, origen-1, destino-1, anchoCamion);
        miSolucion.esPosible();
    }

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}