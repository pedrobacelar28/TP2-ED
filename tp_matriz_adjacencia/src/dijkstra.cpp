#include "dijkstra.hpp"


// Implementação do construtor da classe
Dijkstra::Dijkstra(const Grafo& grafo, int maxPortais) : grafo(grafo), maxPortais(maxPortais) {}

// Implementação do método para calcular as distâncias mínimas
Vetor<double> Dijkstra::calcularDistancias(int origem) {
    int n = grafo.get_clareiras().getSize(); // Número de nós no grafo
    Vetor<double> distancias(n, std::numeric_limits<double>::infinity()); // Vetor de distâncias, inicializado com infinito
    Vetor<int> portaisUsados(n, 0); // Vetor para contar o número de portais usados
    PriorityQueue<int, double> filaPrioridade; // Fila de prioridade para os nós a serem processados

    distancias[origem] = 0; // Distância da origem para ela mesma é zero
    filaPrioridade.push(origem, 0, portaisUsados[origem], maxPortais); // Adiciona a origem na fila de prioridade

    // Enquanto houver nós na fila de prioridade
    while (!filaPrioridade.isEmpty()) {
        int u = filaPrioridade.pop(); // Pega o nó com a menor distância

        // Verifica todas as trilhas (arestas) a partir do nó u
        for (int v = 0; v < grafo.get_trilhas()[u].getSize(); ++v) {
            double peso = grafo.get_trilhas()[u][v];

            if (peso < std::numeric_limits<double>::infinity()) { // Verifica se existe uma trilha (peso não infinito)
                // Se encontrar uma distância menor para o nó v, atualiza a distância
                if (distancias[u] + peso < distancias[v]) {
                    distancias[v] = distancias[u] + peso;
                    portaisUsados[v] = portaisUsados[u];
                    filaPrioridade.push(v, distancias[v], portaisUsados[v], maxPortais);
                }
            }
        }

        // Verifica todos os portais a partir do nó u
        for (int v = 0; v < grafo.get_portais()[u].getSize(); ++v) {
            double peso = grafo.get_portais()[u][v];

            if (peso == 0) { // Verifica se existe um portal (peso zero)
                // Se puder usar mais um portal e encontrar uma distância menor para o nó v, atualiza a distância
                if (portaisUsados[u] + 1 <= maxPortais && distancias[u] + peso < distancias[v]) {
                    distancias[v] = distancias[u] + peso;
                    portaisUsados[v] = portaisUsados[u] + 1;
                    filaPrioridade.push(v, distancias[v], portaisUsados[v], maxPortais);
                }
            }
        }
    }

    return distancias; // Retorna o vetor de distâncias
}
