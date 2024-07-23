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

private:
    const Grafo& grafo;  // Referência ao grafo
    int maxPortais;      // Número máximo de portais que podem ser usados

    // Função heurística para estimar a distância entre dois pontos
    double heuristica(int origem, int destino) const;
};


#endif // ASTAR_H
