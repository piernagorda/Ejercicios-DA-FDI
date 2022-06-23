#include <iostream>
#include <fstream>
#include <queue>

struct tRestaurante {
    int posIni, posFin, radio;
};

bool operator>(tRestaurante a, tRestaurante b) {
    return a.posIni > b.posIni;
}


int numMaximoRestaurantes(std::priority_queue<tRestaurante, std::vector<tRestaurante>, std::greater<tRestaurante>> &cola, int L) {
    int restaurantes = 0, posIni = 0, hastaDondeCubierto = 0; 
    if (cola.top().posIni > 0) return -1;
    else {  
        hastaDondeCubierto = cola.top().posFin;
        while (hastaDondeCubierto < L && !cola.empty()) {
            //std::cout << "He cubierto hasta "<<hastaDondeCubierto<<" el siguiente empieza en "<<cola.top().posIni<<" \n";
            if (cola.top().posIni > hastaDondeCubierto) {
                restaurantes = -1;
                
                break;
            }
            else {
                while (!cola.empty() && cola.top().posIni <= posIni) {
                    if (cola.top().posFin > hastaDondeCubierto) {
                        hastaDondeCubierto = cola.top().posFin;
                    }
                    cola.pop();
                }
                ++restaurantes;
                posIni = hastaDondeCubierto;
            }
        }
    }
    if (hastaDondeCubierto < L) restaurantes = -1;
    return restaurantes;
}

bool resuelveCaso() {
    int L, numRestaurantes;
    std::cin >> L >> numRestaurantes;
    if (!std::cin) return false;
    if (numRestaurantes == 0) {
        std::cout << "-1 \n";
    }
    else {
        std::priority_queue<tRestaurante, std::vector<tRestaurante>, std::greater<tRestaurante>> colaRestaurantes;

        for (int i = 0; i < numRestaurantes; ++i) {
            int posicion, radio;
            std::cin >> posicion >> radio;
            int posIni, posFin;
            if (posicion - radio < 0) posIni = 0;
            else posIni = posicion - radio;
            posFin = posicion + radio;
            //std::cout << "Introduciendo posIni: " << posIni << "Introduciendo posFin: " << posFin << " pos: " << posicion << " \n";
            tRestaurante temp = { posIni, posFin, radio };
            colaRestaurantes.push(temp);
        }

        int sol = numMaximoRestaurantes(colaRestaurantes, L);
        std::cout << sol << std::endl;
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