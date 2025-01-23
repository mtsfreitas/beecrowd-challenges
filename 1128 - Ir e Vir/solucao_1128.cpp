#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum Cor { WHITE, GRAY, BLACK };

struct Vertice {
    Cor cor = WHITE;  
    int distancia = 1e9; 
    int antecessor = 0; 
};

void BFS(int inicio, const vector<vector<int>>& grafo, vector<Vertice>& vertices) {
    queue<int> fila;
    fila.push(inicio);
    
    vertices[inicio].cor = GRAY;
    vertices[inicio].distancia = 0;

    while (!fila.empty()) {
        int vertice_atual = fila.front();
        fila.pop();

        for (int vizinho : grafo[vertice_atual]) {
            if (vertices[vizinho].cor == WHITE) {
                vertices[vizinho].cor = GRAY;
                vertices[vizinho].distancia = vertices[vertice_atual].distancia + 1;
                vertices[vizinho].antecessor = vertice_atual;
                fila.push(vizinho);
            }
        }
     vertices[vertice_atual].cor = BLACK;
    }
}

int main() {
    int numero_de_interseccoes, numero_de_ruas;
    vector<int> resultados;

    while (cin >> numero_de_interseccoes >> numero_de_ruas, numero_de_interseccoes != 0 && numero_de_ruas != 0) {
        vector<vector<int>> grafo(numero_de_interseccoes + 1), grafoInvertido(numero_de_interseccoes + 1);

        for (int i = 0; i < numero_de_ruas; ++i) {
            int V, W, P;
            cin >> V >> W >> P;

            if (P == 1) {
                grafo[V].push_back(W);
                grafoInvertido[W].push_back(V);
            } else if (P == 2) {
                grafo[V].push_back(W);
                grafo[W].push_back(V);
                grafoInvertido[V].push_back(W);
                grafoInvertido[W].push_back(V);
            }
        }

        vector<Vertice> verticesOriginal(numero_de_interseccoes + 1);
        BFS(1, grafo, verticesOriginal);

        bool conexo = true;
        for (int i = 1; i <= numero_de_interseccoes; ++i) {
            if (verticesOriginal[i].cor == WHITE) {
                conexo = false; break;
            }
        }

        if (!conexo) {
            resultados.push_back(0); continue;
        }

        vector<Vertice> verticesInvertido(numero_de_interseccoes + 1);
        BFS(1, grafoInvertido, verticesInvertido);

        conexo = true;
        for (int i = 1; i <= numero_de_interseccoes; ++i) {
            if (verticesInvertido[i].cor == WHITE) {
                 conexo = false; break;
            }
        }

        if (conexo) {
            resultados.push_back(1);
        } else {
            resultados.push_back(0);
        }
    }

    for (int resultado:resultados) {
        cout << resultado << endl;
    }

    return 0;
}