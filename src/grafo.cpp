#include "grafo.h"

// Função para calcular a distância euclidiana entre duas clareiras
double euclidean_distance(const Clareira& a, const Clareira& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Construtor da classe Grafo que inicializa as clareiras, trilhas e portais
Grafo::Grafo(int n) : n(n), clareiras(), trilhas(n), portais(n) {
    for (int i = 0; i < n; ++i) {
        trilhas.push_back(Vetor<Caminho>());
        portais.push_back(Vetor<Caminho>());
    }
}

// Destrutor da classe Grafo
Grafo::~Grafo() {
}

// Método para adicionar uma clareira ao grafo
void Grafo::adicionar_clareira(double x, double y) {
    Clareira clareira = {x, y};
    clareiras.push_back(clareira);
}

// Método para adicionar uma trilha entre duas clareiras no grafo
void Grafo::adicionar_trilha(int u, int v) {
    double weight = euclidean_distance(clareiras[u], clareiras[v]);
    trilhas[u].push_back({v, weight});
}

// Método para adicionar um portal entre duas clareiras no grafo
void Grafo::adicionar_portal(int u, int v) {
    portais[u].push_back({v, 0});
}

// Método para obter as clareiras do grafo
const Vetor<Clareira>& Grafo::get_clareiras() const {
    return clareiras;
}

// Método para obter as trilhas do grafo
const Vetor<Vetor<Caminho>>& Grafo::get_trilhas() const {
    return trilhas;
}

// Método para obter os portais do grafo
const Vetor<Vetor<Caminho>>& Grafo::get_portais() const {
    return portais;
}

