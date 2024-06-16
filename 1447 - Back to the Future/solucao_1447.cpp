#include <iostream>
#include <vector>
#include <map>

using namespace std;

const long long INF = 1e15; // Limite de 10^15

struct Aresta {
    int de, para;
    long long fluxo, capacidade, custo;
};

vector<Aresta> arestas;
vector<vector<int>> adjacencia;
vector<long long> distancia;
vector<int> pai, paiAresta;

void adicionarAresta(int de, int para, long long capacidade, long long custo) {
    arestas.push_back({de, para, 0, capacidade, custo});
    adjacencia[de].push_back(arestas.size() - 1);
    arestas.push_back({para, de, 0, 0, -custo});
    adjacencia[para].push_back(arestas.size() - 1);
}

bool BellmanFord(int origem, int destino, int N) {
    distancia.assign(N, INF);
    pai.assign(N,-1);
    paiAresta.assign(N,-1);
    distancia[origem] = 0;
    for (int i = 0; i < N - 1; ++i) {
        bool atualizado = false;
        for (int u = 0; u < N; ++u) {
            if (distancia[u] == INF) continue;
            for (int idx : adjacencia[u]) {
                Aresta &e = arestas[idx];
                if (e.fluxo < e.capacidade && distancia[u]+e.custo < distancia[e.para]) {
                    distancia[e.para] = distancia[u] + e.custo;
                    pai[e.para] = u;
                    paiAresta[e.para] = idx;
                    atualizado =true;
                }
            }
        }
        if (!atualizado) break;
    }
    return distancia[destino] != INF;
}

long long fluxoCustoMinimo(int origem, int destino, long long demanda, int N) {
    long long fluxo = 0, custo = 0;
    while (BellmanFord(origem, destino, N) && fluxo < demanda) {
        long long fluxoCaminho = INF;
        for (int v = destino; v != origem; v = pai[v]) {
            int idx = paiAresta[v];
            fluxoCaminho = min(fluxoCaminho, arestas[idx].capacidade - arestas[idx].fluxo);
        }
        if (fluxo + fluxoCaminho > demanda) fluxoCaminho = demanda - fluxo;
        for (int v = destino; v != origem; v = pai[v]) {
            int idx = paiAresta[v];
            arestas[idx].fluxo += fluxoCaminho;
            arestas[idx ^ 1].fluxo -= fluxoCaminho;
            custo += fluxoCaminho * arestas[idx].custo;
        }
        fluxo += fluxoCaminho;
    }
    if (fluxo < demanda) return -1;
    return custo;
}

int main() {
    int numCidades,numRotas,cidadeA,cidadeB,custo,numAmigos, capacidade;
    int instancia = 1;

    while (cin >> numCidades >> numRotas) {
        map<int, map<int, int>> grafo;

        for (int i = 0; i < numRotas; ++i) {
            cin >> cidadeA >> cidadeB >> custo;
            grafo[cidadeA][cidadeB] = custo;
            grafo[cidadeB][cidadeA] = custo;
        }

        cin >> numAmigos >> capacidade;

        arestas.clear();
        adjacencia.assign(numCidades + 2, vector<int>());

        for (auto &i : grafo) {
            int de = i.first;
            for (auto &j : i.second) {
                int para = j.first;
                int custo = j.second;
                adicionarAresta(de,para, capacidade, custo);
            }
        }

        adicionarAresta(0, 1,numAmigos, 0);
        adicionarAresta(numCidades, numCidades+1, numAmigos, 0);

        long long resultado = fluxoCustoMinimo(0, numCidades+1, numAmigos, numCidades + 2);

        cout << "Instancia " << instancia++ << endl;
        if (resultado == -1) {
            cout << "impossivel" << endl << endl;
        } else {
            cout << min(resultado,INF) << endl << endl;
        }
    }

    return 0;
}