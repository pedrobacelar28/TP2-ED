#include "astar.h"


// Implementação do construtor da classe
AStar::AStar(const Grafo& grafo, int maxPortais) : grafo(grafo), maxPortais(maxPortais) {}

// Implementação da função heurística
double AStar::heuristica(int origem, int destino) const {
    return euclidean_distance(grafo.get_clareiras()[origem], grafo.get_clareiras()[destino]);
}

// Implementação do método para calcular as distâncias mínimas
Vetor<double> AStar::calcularDistancias(int origem, int destino) {
    int n = grafo.get_clareiras().getSize(); // Número de nós no grafo
    Vetor<double> distancias(n, std::numeric_limits<double>::infinity()); // Vetor de distâncias, inicializado com infinito
    Vetor<double> custos(n, std::numeric_limits<double>::infinity()); // Vetor de custos, inicializado com infinito
    Vetor<int> portaisUsados(n, 0); // Vetor para contar o número de portais usados
    PriorityQueue<int, double> filaPrioridade; // Fila de prioridade para os nós a serem processados

    distancias[origem] = 0; // Distância da origem para ela mesma é zero
    custos[origem] = heuristica(origem, destino); // Custo inicial é a heurística
    filaPrioridade.push(origem, custos[origem], portaisUsados[origem], maxPortais); // Adiciona a origem na fila de prioridade

    // Enquanto houver nós na fila de prioridade
    while (!filaPrioridade.isEmpty()) {
        int u = filaPrioridade.pop(); // Pega o nó com a menor estimativa de custo

        if (u == destino) break; // Se alcançou o destino, interrompe a busca

        // Verifica todas as trilhas (arestas) a partir do nó u
        for (int i = 0; i < grafo.get_trilhas()[u].getSize(); ++i) {
            Caminho caminho = grafo.get_trilhas()[u][i];
            int v = caminho.to;
            double peso = caminho.weight;

            // Se encontrar uma distância menor para o nó v, atualiza a distância e o custo
            if (distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                custos[v] = distancias[v] + heuristica(v, destino);
                portaisUsados[v] = portaisUsados[u];
                filaPrioridade.push(v, custos[v], portaisUsados[v], maxPortais);
            }
        }

        // Verifica todos os portais a partir do nó u
        for (int i = 0; i < grafo.get_portais()[u].getSize(); ++i) {
            Caminho portal = grafo.get_portais()[u][i];
            int v = portal.to;

            // Se puder usar mais um portal e encontrar uma distância menor para o nó v, atualiza a distância e o custo
            if (portaisUsados[u] + 1 <= maxPortais && distancias[u] < distancias[v]) {
                distancias[v] = distancias[u];
                custos[v] = distancias[v] + heuristica(v, destino);
                portaisUsados[v] = portaisUsados[u] + 1;
                filaPrioridade.push(v, custos[v], portaisUsados[v], maxPortais);
            }
        }
    }

    return distancias; // Retorna o vetor de distâncias
}