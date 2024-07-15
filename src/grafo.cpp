#include "grafo.h"

double euclidean_distance(const Clareira& a, const Clareira& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Grafo::Grafo(int n) : n(n), clareiras(), trilhas(n), portais(n) {
    for (int i = 0; i < n; ++i) {
        trilhas.push_back(Vetor<Caminho>());
        portais.push_back(Vetor<Caminho>());
    }
}

Grafo::~Grafo() {
}

void Grafo::adicionar_clareira(double x, double y) {
    Clareira clareira = {x, y};
    clareiras.push_back(clareira);
}

void Grafo::adicionar_trilha(int u, int v) {
    double weight = euclidean_distance(clareiras[u], clareiras[v]);
    trilhas[u].push_back({v, weight});
}

void Grafo::adicionar_portal(int u, int v) {
    portais[u].push_back({v, 0});
}

const Vetor<Clareira>& Grafo::get_clareiras() const {
    return clareiras;
}

const Vetor<Vetor<Caminho>>& Grafo::get_trilhas() const {
    return trilhas;
}

const Vetor<Vetor<Caminho>>& Grafo::get_portais() const {
    return portais;
}
