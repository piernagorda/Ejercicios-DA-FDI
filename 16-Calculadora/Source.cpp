#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

const int MAX = 10000;
const int INF = 1000000000;

//El adyacente de v a i sera lo que diga i
int adyacente(int v, int i) {
    switch (i) {
    case 0: return (v + 1) % MAX;
    case 1: return (v * 2) % MAX;
    default: return (v / 3);
    }
}

int dfs(int origen, int destino) {
    if (origen == destino) return 0;
    std::vector<int> distancia(MAX, INF);
    distancia[origen] = 0; //La distancia desde el origen la marcamos como 0
    //Creamos una cola
    std::queue<int> cola; 
    cola.push(origen);

    while (!cola.empty()) {
        //Sacamos de la cola
        int v = cola.front(); 
        cola.pop();
        
        for (int i = 0; i < 3; i++) {
            //Calculamos el siguiente numero basandonos en i: i=0->+1, i=1->*2, i=2->/3
            int w = adyacente(v, i);
            //Si la distancia es INF es que no se ha visitado aun
            if (distancia[w] == INF) {
                //Le ponemos distancia +1
                distancia[w] = distancia[v] + 1;
                if (w == destino)return distancia[w];
                else cola.push(w);
            }
        }
    }
}

bool resuelveCaso() {
    int origen, destino;
    std::cin >> origen >> destino;
    if (!std::cin) return false;
    std::cout << dfs(origen, destino) << std::endl;
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