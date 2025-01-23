#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int INF = 1e9;

enum Cor { BRANCO, CINZA, PRETO };

struct Vertice {
    Cor cor = BRANCO;
    int distancia = INF;
    int antecessor = -1;
};

struct Aresta {
    int destino, capacidade, fluxo, indiceReverso;
};

struct Grafo {
    vector<vector<Aresta>> adj;

    void adicionarAresta(int u, int v, int capacidade) {
        Aresta arestaDireta = {v, capacidade, 0, (int)adj[v].size()};
        Aresta arestaReversa = {u, 0, 0, (int)adj[u].size()};
        adj[u].push_back(arestaDireta);
        adj[v].push_back(arestaReversa);
    }
};

bool bfs(Grafo& g, int origem, int destino, vector<int>& pai) {
    int n = g.adj.size();
    vector<Vertice> vertices(n);  

    vertices[origem].cor = CINZA;
    vertices[origem].distancia = 0;
    pai[origem] = -2;

    vector<int> fila;
    int frente = 0, fundo = 0;
    fila.push_back(origem);
    fundo++;

    while (frente < fundo) {
        int u = fila[frente];
        frente++;

        for (Aresta& aresta : g.adj[u]) {
            if (vertices[aresta.destino].cor == BRANCO && aresta.capacidade > aresta.fluxo) {  
                vertices[aresta.destino].cor = CINZA;
                vertices[aresta.destino].distancia = vertices[u].distancia + 1;
                vertices[aresta.destino].antecessor = u;
                pai[aresta.destino] = u;

                if (aresta.destino == destino) {
                    return true;
                }

                fila.push_back(aresta.destino);
                fundo++;
            }
        }

        vertices[u].cor = PRETO; 
    }

    return false;
}

int fordFulkerson(Grafo& g, int origem, int destino) {
    int fluxo = 0;
    vector<int> pai(g.adj.size());

    while (bfs(g, origem, destino, pai)) {
        int novoFluxo = INF;
        int atual = destino;
        while (atual != origem) {
            int anterior = pai[atual];
            for (Aresta& aresta : g.adj[anterior]) {
                if (aresta.destino == atual) {
                    novoFluxo = min(novoFluxo, aresta.capacidade - aresta.fluxo);
                    break;
                }
            }
            atual = anterior;
        }

        fluxo += novoFluxo;
        atual = destino;
        while (atual != origem) {
            int anterior = pai[atual];
            for (Aresta& aresta : g.adj[anterior]) {
                if (aresta.destino == atual) {
                    aresta.fluxo += novoFluxo;
                    g.adj[atual][aresta.indiceReverso].fluxo -= novoFluxo;
                    break;
                }
            }
            atual = anterior;
        }
    }

    return fluxo;
}

int main() {
    int casosDeTeste;
    cin >> casosDeTeste;

    string tamanhoCamiseta[6] = {"XXL", "XL", "L", "M", "S", "XS"};
    vector<string> resultados;

    while (casosDeTeste--) {
        int numTotalCamisetas, numVoluntarios;
        cin >> numTotalCamisetas >> numVoluntarios;

        int numTamanhos = 6;
        int totalNos = 2+numTamanhos+numVoluntarios;
        int origem = totalNos-2;
        int destino = totalNos - 1;

        Grafo g;
        g.adj.resize(totalNos);

        for (int i = 0; i < numTamanhos; ++i) {
            g.adicionarAresta(origem, i, numTotalCamisetas / numTamanhos);
        }

        for (int i = 0; i < numVoluntarios; ++i) {
            g.adicionarAresta(numTamanhos + i, destino, 1);
        }

        for (int i = 0; i < numVoluntarios; ++i) {
            string tamanho1, tamanho2;
            cin >> tamanho1 >> tamanho2;

            int pos1 = -1;
            int pos2 = -1;
            for (int j = 0; j < 6; ++j) {
                if (tamanhoCamiseta[j] == tamanho1) {
                    pos1 = j;
                } 
                if (tamanhoCamiseta[j] == tamanho2) {
                     pos2 = j;
                }
            }

            g.adicionarAresta(pos1, numTamanhos+i, 1);
            g.adicionarAresta(pos2, numTamanhos+i, 1);
        }

        int fluxoMaximo = fordFulkerson(g, origem, destino);

        if (fluxoMaximo == numVoluntarios) {
            resultados.push_back("YES");
        } else {
            resultados.push_back("NO");
        }
    }

    for (const string& resultado : resultados) {
        cout << resultado << endl;
    }

    return 0;
}