#include <iostream>
#include "grafo.h"
#include "dijkstra.h"
#include "astar.h"

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;

    Grafo grafo(n);

    // Leitura das clareiras
    for (int i = 0; i < n; ++i) {
        double x, y;
        std::cin >> x >> y;
        grafo.adicionar_clareira(x, y);
    }

    // Leitura das trilhas
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        grafo.adicionar_trilha(u, v);
    }

    // Leitura dos portais
    for (int i = 0; i < k; ++i) {
        int u, v;
        std::cin >> u >> v;
        grafo.adicionar_portal(u, v);
    }

    // Leitura da energia e quantidade de portais permitidos
    double s;
    int q;
    std::cin >> s >> q;

    // Executa o algoritmo de Dijkstra a partir da clareira 0 até n-1
    Dijkstra dijkstra(grafo, q);
    Vetor<double> distancias_dijkstra = dijkstra.calcularDistancias(0);
    double distancia_final_dijkstra = distancias_dijkstra[n - 1];

    // Verifica se a distância calculada pelo Dijkstra está dentro do limite de energia
    bool caminho_possivel_dijkstra = (distancia_final_dijkstra <= s);

    // Executa o algoritmo A* a partir da clareira 0 até n-1
    AStar astar(grafo, q);
    Vetor<double> distancias_astar = astar.calcularDistancias(0, n - 1);
    double distancia_final_astar = distancias_astar[n - 1];

    // Verifica se a distância calculada pelo A* está dentro do limite de energia
    bool caminho_possivel_astar = (distancia_final_astar <= s);

    // Saída dos resultados
    std::cout << (caminho_possivel_dijkstra ? 1 : 0) << " ";
    std::cout << (caminho_possivel_astar ? 1 : 0) << std::endl;

    return 0;
}
