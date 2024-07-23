#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "grafo.hpp"
#include "queue.hpp"

#include <limits>

// Classe que implementa o algoritmo de Dijkstra
class Dijkstra {
public:
    // Construtor da classe
    Dijkstra(const Grafo& grafo, int maxPortais);

    // Método para calcular as distâncias mínimas a partir de uma origem
    Vetor<double> calcularDistancias(int origem);

    // Método para calcular o caminho mínimo entre dois pontos
    Vetor<int> calcularCaminho(int origem, int destino);

private:
    const Grafo& grafo;  // Referência ao grafo
    int maxPortais;      // Número máximo de portais que podem ser usados
};

#endif // DIJKSTRA_H
