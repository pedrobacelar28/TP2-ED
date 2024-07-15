#ifndef ASTAR_H
#define ASTAR_H

#include "grafo.h"
#include "queue.h"
#include <limits>

class AStar {
public:
    AStar(const Grafo& grafo, int maxPortais);
    Vetor<double> calcularDistancias(int origem, int destino);
    Vetor<int> calcularCaminho(int origem, int destino);

private:
    const Grafo& grafo;
    int maxPortais;
    double heuristica(int origem, int destino) const;
};

AStar::AStar(const Grafo& grafo, int maxPortais) : grafo(grafo), maxPortais(maxPortais) {}

double AStar::heuristica(int origem, int destino) const {
    return euclidean_distance(grafo.get_clareiras()[origem], grafo.get_clareiras()[destino]);
}

Vetor<double> AStar::calcularDistancias(int origem, int destino) {
    int n = grafo.get_clareiras().getSize();
    Vetor<double> distancias(n, std::numeric_limits<double>::infinity());
    Vetor<double> custos(n, std::numeric_limits<double>::infinity());
    Vetor<int> portaisUsados(n, 0);
    PriorityQueue<int, double> filaPrioridade;

    distancias[origem] = 0;
    custos[origem] = heuristica(origem, destino);
    filaPrioridade.push(origem, custos[origem]);

    while (!filaPrioridade.isEmpty()) {
        int u = filaPrioridade.pop();

        if (u == destino) break;

        // Verificar trilhas
        for (int i = 0; i < grafo.get_trilhas()[u].getSize(); ++i) {
            Caminho caminho = grafo.get_trilhas()[u][i];
            int v = caminho.to;
            double peso = caminho.weight;

            if (distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                custos[v] = distancias[v] + heuristica(v, destino);
                portaisUsados[v] = portaisUsados[u];
                filaPrioridade.push(v, custos[v]);
            }
        }

        // Verificar portais
        for (int i = 0; i < grafo.get_portais()[u].getSize(); ++i) {
            Caminho portal = grafo.get_portais()[u][i];
            int v = portal.to;

            if (portaisUsados[u] + 1 <= maxPortais && distancias[u] < distancias[v]) {
                distancias[v] = distancias[u];
                custos[v] = distancias[v] + heuristica(v, destino);
                portaisUsados[v] = portaisUsados[u] + 1;
                filaPrioridade.push(v, custos[v]);
            }
        }
    }

    return distancias;
}

Vetor<int> AStar::calcularCaminho(int origem, int destino) {
    int n = grafo.get_clareiras().getSize();
    Vetor<double> distancias = calcularDistancias(origem, destino);
    Vetor<int> antecessores(n, -1);
    Vetor<int> portaisUsados(n, 0);
    PriorityQueue<int, double> filaPrioridade;

    distancias[origem] = 0;
    filaPrioridade.push(origem, heuristica(origem, destino));

    while (!filaPrioridade.isEmpty()) {
        int u = filaPrioridade.pop();

        if (u == destino) break;

        // Verificar trilhas
        for (int i = 0; i < grafo.get_trilhas()[u].getSize(); ++i) {
            Caminho caminho = grafo.get_trilhas()[u][i];
            int v = caminho.to;
            double peso = caminho.weight;

            if (distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                antecessores[v] = u;
                portaisUsados[v] = portaisUsados[u];
                filaPrioridade.push(v, distancias[v] + heuristica(v, destino));
            }
        }

        // Verificar portais
        for (int i = 0; i < grafo.get_portais()[u].getSize(); ++i) {
            Caminho portal = grafo.get_portais()[u][i];
            int v = portal.to;

            if (portaisUsados[u] + 1 <= maxPortais && distancias[u] < distancias[v]) {
                distancias[v] = distancias[u];
                antecessores[v] = u;
                portaisUsados[v] = portaisUsados[u] + 1;
                filaPrioridade.push(v, distancias[v] + heuristica(v, destino));
            }
        }
    }

    Vetor<int> caminho;
    for (int v = destino; v != -1; v = antecessores[v]) {
        caminho.push_back(v);
    }
    // Inverter o caminho para obter a ordem correta
    for (int i = 0; i < caminho.getSize() / 2; ++i) {
        std::swap(caminho[i], caminho[caminho.getSize() - 1 - i]);
    }
    return caminho;
}

#endif // ASTAR_H
