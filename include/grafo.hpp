#ifndef GRAFO_H
#define GRAFO_H

#include <cmath>
#include "vetor.hpp"

// Estrutura Clareira para representar uma clareira com coordenadas x e y
struct Clareira {
    double x, y;
};

// Estrutura Caminho para representar uma trilha com um destino (to) e um peso (weight)
struct Caminho {
    int to;
    double weight;
};

// Função para calcular a distância euclidiana entre duas clareiras
double euclidean_distance(const Clareira& a, const Clareira& b);


// Classe Grafo para representar um grafo de clareiras conectadas por trilhas e portais
class Grafo {
public:
    Grafo(int n); // Construtor que inicializa o grafo com n clareiras
    ~Grafo(); // Destrutor
    
    void adicionar_clareira(double x, double y); // Adiciona uma clareira ao grafo
    void adicionar_trilha(int u, int v); // Adiciona uma trilha entre duas clareiras
    void adicionar_portal(int u, int v); // Adiciona um portal entre duas clareiras
    
    const Vetor<Clareira>& get_clareiras() const;  // Retorna as clareiras do grafo (marcado como const)
    const Vetor<Vetor<Caminho>>& get_trilhas() const;  // Retorna as trilhas do grafo (marcado como const)
    const Vetor<Vetor<Caminho>>& get_portais() const;  // Retorna os portais do grafo (marcado como const)

private:
    int n; // Número de clareiras no grafo
    Vetor<Clareira> clareiras; // Vetor de clareiras
    Vetor<Vetor<Caminho>> trilhas; // Vetor de vetores de trilhas
    Vetor<Vetor<Caminho>> portais; // Vetor de vetores de portais
};

#endif // GRAFO_H

