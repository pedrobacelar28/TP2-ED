#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "grafo.h"
#include "queue.h"
#include <limits>

class Dijkstra {
public:
    Dijkstra(const Grafo& grafo, int maxPortais);
    Vetor<double> calcularDistancias(int origem);
    Vetor<int> calcularCaminho(int origem, int destino);

private:
    const Grafo& grafo;
    int maxPortais;
};

Dijkstra::Dijkstra(const Grafo& grafo, int maxPortais) : grafo(grafo), maxPortais(maxPortais) {}

Vetor<double> Dijkstra::calcularDistancias(int origem) {
    int n = grafo.get_clareiras().getSize();
    Vetor<double> distancias(n, std::numeric_limits<double>::infinity());
    Vetor<int> portaisUsados(n, 0);
    PriorityQueue<int, double> filaPrioridade;

    distancias[origem] = 0;
    filaPrioridade.push(origem, 0);

    while (!filaPrioridade.isEmpty()) {
        int u = filaPrioridade.pop();

        // Verificar trilhas
        for (int i = 0; i < grafo.get_trilhas()[u].getSize(); ++i) {
            Caminho caminho = grafo.get_trilhas()[u][i];
            int v = caminho.to;
            double peso = caminho.weight;

            if (distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                portaisUsados[v] = portaisUsados[u];
                filaPrioridade.push(v, distancias[v]);
            }
        }

        // Verificar portais
        for (int i = 0; i < grafo.get_portais()[u].getSize(); ++i) {
            Caminho portal = grafo.get_portais()[u][i];
            int v = portal.to;
            double peso = 0.0; // Peso zero para portais

            if (portaisUsados[u] + 1 <= maxPortais && distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                portaisUsados[v] = portaisUsados[u] + 1;
                filaPrioridade.push(v, distancias[v]);
            }
        }
    }

    return distancias;
}

Vetor<int> Dijkstra::calcularCaminho(int origem, int destino) {
    int n = grafo.get_clareiras().getSize();
    Vetor<double> distancias = calcularDistancias(origem);
    Vetor<int> antecessores(n, -1);
    PriorityQueue<int, double> filaPrioridade;

    distancias[origem] = 0;
    filaPrioridade.push(origem, 0);

    while (!filaPrioridade.isEmpty()) {
        int u = filaPrioridade.pop();

        // Verificar trilhas
        for (int i = 0; i < grafo.get_trilhas()[u].getSize(); ++i) {
            Caminho caminho = grafo.get_trilhas()[u][i];
            int v = caminho.to;
            double peso = caminho.weight;

            if (distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                antecessores[v] = u;
                filaPrioridade.push(v, distancias[v]);
            }
        }

        // Verificar portais
        for (int i = 0; i < grafo.get_portais()[u].getSize(); ++i) {
            Caminho portal = grafo.get_portais()[u][i];
            int v = portal.to;
            double peso = 0.0; // Peso zero para portais

            if (distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                antecessores[v] = u;
                filaPrioridade.push(v, distancias[v]);
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

#endif // DIJKSTRA_H
