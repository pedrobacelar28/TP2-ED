#ifndef GRAFO_H
#define GRAFO_H

#include <cmath>
#include "vetor.h"

struct Clareira {
    double x, y;
};

struct Caminho {
    int to;
    double weight;
};

double euclidean_distance(const Clareira& a, const Clareira& b);

class Grafo {
public:
    Grafo(int n);
    ~Grafo();
    
    void adicionar_clareira(double x, double y);
    void adicionar_trilha(int u, int v);
    void adicionar_portal(int u, int v);
    
    Vetor<Clareira>& get_clareiras();
    Vetor<Vetor<Caminho>>& get_trilhas();
    Vetor<Vetor<Caminho>>& get_portais();

private:
    int n;
    Vetor<Clareira> clareiras;
    Vetor<Vetor<Caminho>> trilhas;
    Vetor<Vetor<Caminho>> portais;
};

#endif // GRAFO_H
