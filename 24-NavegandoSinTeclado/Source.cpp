#include <iostream>
#include <fstream>
#include <vector>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

const int INF = 10000000;

class Problema {
public:

    Problema(DigrafoValorado<int> const& g, std::vector<int> const& tiemposCargaPagina):
        tiemposParciales(g.V(), INF), _esPosible(false), pq(g.V()) {
        dijkstra(g, tiemposCargaPagina);
    }

    int tiempoMinimo() const { return _tiempoCargaFinal; }
    bool esPosible() const { return _esPosible; }

private:
    
    int _tiempoCargaFinal;
    bool _esPosible;
    std::vector<int> tiemposParciales;
    IndexPQ<int> pq;

    void dijkstra(DigrafoValorado<int> const& g, std::vector<int> const& tiemposCargaPagina) {
        tiemposParciales[0] = 0; //Ponemos que el tiempo parcial de 0 es 0
        pq.push(0, 0); //Metemos el vertice 0 con prioridad 0
        while (!pq.empty()) {
            int v= pq.top().elem; //Sacamos el elemento mas prioritario
            pq.pop();
            //Relajamos sus aristas
            for (auto w : g.ady(v)) relajar(w, tiemposCargaPagina);
        } //Cuando la cola esta vacia hemos acabado
        if (tiemposParciales[g.V() - 1] != INF) { //Si el tiempoParcial del ultimo elemento no es INF entonces es que ha sido alcazando
            _esPosible = true;
            _tiempoCargaFinal = tiemposParciales[g.V() - 1] + tiemposCargaPagina[g.V() - 1]; //Esto?
        }
    }

    void relajar(AristaDirigida<int> arista, std::vector<int> const& tiemposCargaPagina) {
        int desde = arista.desde();
        int hasta = arista.hasta();
        if (tiemposParciales[desde] + tiemposCargaPagina[desde] + arista.valor() < tiemposParciales[hasta]) {
            tiemposParciales[hasta] = tiemposParciales[desde] + tiemposCargaPagina[desde] + arista.valor();
            pq.update(hasta, tiemposParciales[hasta]);
        }
    }

    /*Esto es O(n^2)
    void dijkstra(DigrafoValorado<int> const& g, std::vector<int> const& tiemposCargaPagina, int vertice) {
        for (auto w : g.ady(vertice)){ //Recorremos los adyacentes
            if (tiemposParciales[vertice] + w.valor() < tiemposParciales[w.hasta()]) tiemposParciales[w.hasta()] = tiemposParciales[vertice] + tiemposCargaPagina[vertice] + w.valor();
            if (w.hasta() == g.V() - 1) _esPosible = true; //Si hemos llegado a la pagina N
            dijkstra(g, tiemposCargaPagina, w.hasta());
        }
    }
    */
};

bool resuelveCaso() {
    int numPaginas, enlaces, origen, destino, tCarga;
    std::cin >> numPaginas;
    if (numPaginas == 0)return false;
    DigrafoValorado<int> miGrafo(numPaginas);
    std::vector<int> tiemposCarga(numPaginas);
    for (int i = 0; i < numPaginas; ++i) std::cin>>tiemposCarga[i];
    std::cin >> enlaces;
    for (int i = 0; i < enlaces; ++i) {
        std::cin >> origen >> destino >> tCarga;
        AristaDirigida<int> miArista(origen-1, destino-1, tCarga);
        miGrafo.ponArista(miArista);
    }
    Problema miProblema(miGrafo, tiemposCarga);
    if (miProblema.esPosible()) std::cout << miProblema.tiempoMinimo() << std::endl;
    else std::cout << "IMPOSIBLE" << std::endl;
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (resuelveCaso());
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
}