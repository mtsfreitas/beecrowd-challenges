#include <iostream>
#include <cmath>
#include <vector>
#include <set>
using namespace std;

const double INFINITO = 99999;


int extractMin(const set<int>& Q, const vector<double>& chave) {
    int u = *Q.begin();
    for (int v : Q) {
        if (chave[v] < chave[u]) {
            u = v;
        }
    }
    return u;
}

double algoritoDePrim(const vector<vector<double>>& G, int n) {
    // Inicializando chave e pai
    vector<double> chave(n, INFINITO);
    vector<int> pai(n, -1); // -1 para representar nil
    set<int> Q;

    chave[0] = 0;
    for (int u = 0; u < n; ++u) {
        Q.insert(u); // Q = V
    }

    double peso = 0;

    while (!Q.empty()) {
        int u = extractMin(Q, chave);
        Q.erase(u);
        peso += chave[u];

        for (int v = 0; v < n; ++v) {
            if (Q.count(v) && G[u][v] < chave[v]) {
                pai[v] = u;
                chave[v] = G[u][v];
            }
        }
    }

    return peso;
}

int main() {
    int testes, pessoas;
    cin >> testes;

    for (int t = 0; t < testes; ++t) {
        cin >> pessoas;
        vector<vector<int>> coordenadas(pessoas, vector<int>(2));
        for (int i = 0; i < pessoas; ++i) {
            cin >> coordenadas[i][0] >> coordenadas[i][1];
        }

        vector<vector<double>> grafo(pessoas, vector<double>(pessoas, INFINITO));
        for (int i = 0; i < pessoas; ++i) {
            grafo[i][i] = 0;
        }

        for (int i = 0; i < pessoas; ++i) {
            for (int j = i + 1; j < pessoas; ++j) {
                double dist = sqrt(pow(coordenadas[i][0] - coordenadas[j][0], 2) + pow(coordenadas[i][1] - coordenadas[j][1], 2)) / 100.0;
                grafo[i][j] = grafo[j][i] = dist;
            }
        }

        double resultado = algoritoDePrim(grafo, pessoas);
        printf("%.2f\n", resultado);
    }

    return 0;
}