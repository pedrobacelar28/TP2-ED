#include <iostream>
#include "grafo.h"

using namespace std;

int main() {

    int n = 3;  // número de nós
    int m = 3;  // número de trilhas
    int k = 0;  // número de portais

    Grafo grafo(n);

    // Adicionando clareiras (pontos)
    grafo.adicionar_clareira(0, 0); // Clareira 0
    grafo.adicionar_clareira(1, 0); // Clareira 1
    grafo.adicionar_clareira(2, 0); // Clareira 2

    // Adicionando trilhas (arestas)
    grafo.adicionar_trilha(0, 1); // Trilha de 0 a 1
    grafo.adicionar_trilha(0, 2); // Trilha de 0 a 2
    grafo.adicionar_trilha(1, 2); // Trilha de 1 a 2

    // Exibindo trilhas
    for (int i = 0; i < grafo.get_trilhas().getSize(); ++i) {
        cout << "Trilhas from node " << i << " (size: " << grafo.get_trilhas()[i].getSize() << "):\n";
        for (int j = 0; j < grafo.get_trilhas()[i].getSize(); ++j) {
            Caminho caminho = grafo.get_trilhas()[i][j];
            cout << "  to " << caminho.to << " with weight " << caminho.weight << "\n";
        }
    }

    return 0;
}
