#ifndef ASTAR_H
#define ASTAR_H

#include "grafo.h"
#include "queue.h"
#include <limits>

// Classe que implementa o algoritmo A*
class AStar {
public:
    // Construtor da classe
    AStar(const Grafo& grafo, int maxPortais);

    // Método para calcular as distâncias mínimas entre uma origem e um destino
    Vetor<double> calcularDistancias(int origem, int destino);

    // Método para calcular o caminho mínimo entre dois pontos
    Vetor<int> calcularCaminho(int origem, int destino);

private:
    const Grafo& grafo;  // Referência ao grafo
    int maxPortais;      // Número máximo de portais que podem ser usados

    // Função heurística para estimar a distância entre dois pontos
    double heuristica(int origem, int destino) const;
};

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
    filaPrioridade.push(origem, custos[origem]); // Adiciona a origem na fila de prioridade

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
                filaPrioridade.push(v, custos[v]);
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
                filaPrioridade.push(v, custos[v]);
            }
        }
    }

    return distancias; // Retorna o vetor de distâncias
}

// Implementação do método para calcular o caminho mínimo
Vetor<int> AStar::calcularCaminho(int origem, int destino) {
    int n = grafo.get_clareiras().getSize(); // Número de nós no grafo
    Vetor<double> distancias = calcularDistancias(origem, destino); // Calcula as distâncias mínimas a partir da origem
    Vetor<int> antecessores(n, -1); // Vetor para armazenar os antecessores de cada nó
    Vetor<int> portaisUsados(n, 0); // Vetor para contar o número de portais usados
    PriorityQueue<int, double> filaPrioridade; // Fila de prioridade para os nós a serem processados

    distancias[origem] = 0; // Distância da origem para ela mesma é zero
    filaPrioridade.push(origem, heuristica(origem, destino)); // Adiciona a origem na fila de prioridade

    // Enquanto houver nós na fila de prioridade
    while (!filaPrioridade.isEmpty()) {
        int u = filaPrioridade.pop(); // Pega o nó com a menor estimativa de custo

        if (u == destino) break; // Se alcançou o destino, interrompe a busca

        // Verifica todas as trilhas (arestas) a partir do nó u
        for (int i = 0; i < grafo.get_trilhas()[u].getSize(); ++i) {
            Caminho caminho = grafo.get_trilhas()[u][i];
            int v = caminho.to;
            double peso = caminho.weight;

            // Se encontrar uma distância menor para o nó v, atualiza a distância, o custo e o antecessor
            if (distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                antecessores[v] = u;
                portaisUsados[v] = portaisUsados[u];
                filaPrioridade.push(v, distancias[v] + heuristica(v, destino));
            }
        }

        // Verifica todos os portais a partir do nó u
        for (int i = 0; i < grafo.get_portais()[u].getSize(); ++i) {
            Caminho portal = grafo.get_portais()[u][i];
            int v = portal.to;

            // Se puder usar mais um portal e encontrar uma distância menor para o nó v, atualiza a distância, o custo e o antecessor
            if (portaisUsados[u] + 1 <= maxPortais && distancias[u] < distancias[v]) {
                distancias[v] = distancias[u];
                antecessores[v] = u;
                portaisUsados[v] = portaisUsados[u] + 1;
                filaPrioridade.push(v, distancias[v] + heuristica(v, destino));
            }
        }
    }

    // Vetor para armazenar o caminho
    Vetor<int> caminho;
    for (int v = destino; v != -1; v = antecessores[v]) {
        caminho.push_back(v); // Adiciona o nó ao caminho
    }

    // Inverte o caminho para obter a ordem correta (do início ao destino)
    for (int i = 0; i < caminho.getSize() / 2; ++i) {
        std::swap(caminho[i], caminho[caminho.getSize() - 1 - i]);
    }

    return caminho; // Retorna o vetor de caminho
}

#endif // ASTAR_H
