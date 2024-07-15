#include <iostream>
#include "grafo.h"

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    
    Grafo grafo(n);
    
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        grafo.adicionar_clareira(x, y);
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        grafo.adicionar_trilha(u, v);
    }

    for (int i = 0; i < k; ++i) {
        int u, v;
        cin >> u >> v;
        grafo.adicionar_portal(u, v);
    }

    double s;
    int q;
    cin >> s >> q;

    // Algoritmos de Dijkstra e A* entram aqui usando `grafo`

    return 0;
}
