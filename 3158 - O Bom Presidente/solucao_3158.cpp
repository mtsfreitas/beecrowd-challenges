#include <iostream>
#include <vector>

using namespace std;

struct Vertice {
    int cor; // 0: WHITE, 1: GRAY, 2: BLACK
    int pai;
    int tempo_descoberta;
    int tempo_finalizacao;
};

void DFS_VISIT(int u, int &tempo, vector<Vertice> &vertices, const vector<vector<int>> &adj, int &contagemVertices) {
    tempo += 1;
    vertices[u].tempo_descoberta = tempo;
    vertices[u].cor = 1; 
    contagemVertices++; 

    for (int v : adj[u]) {
        if (vertices[v].cor == 0) { 
            vertices[v].pai = u;
            DFS_VISIT(v, tempo, vertices, adj, contagemVertices);
        }
    }

    vertices[u].cor = 2; 
    tempo += 1;
    vertices[u].tempo_finalizacao = tempo;
}

long long DFS(int N, const vector<vector<int>> &adj, int B, int E) {
    vector<Vertice> vertices(N + 1);
    for (int i = 1; i <= N; ++i) {
        vertices[i] = {0, -1, 0, 0};
    }

    int tempo = 0;
    long long custoTotal = 0;

    for (int u = 1; u <= N; ++u) {
        if (vertices[u].cor == 0) {
            int componentSize = 0;
            DFS_VISIT(u, tempo, vertices, adj, componentSize);

            long long custoComBibliotecas = (long long)componentSize * B; 
            long long custoComEstradas = (long long)B + (long long)(componentSize - 1) * E;

            if (custoComBibliotecas < custoComEstradas) {
                custoTotal += custoComBibliotecas;
            } else {
                custoTotal +=custoComEstradas;
            }
        }
    }

    return custoTotal;
}

long long custoMinimo(int N, int M, int B, int E, vector<pair<int, int>> &estradas) {
    if (M == 0) {
        return (long long)N * B;
    }

    vector<vector<int>> adj(N + 1);
    for (const auto &estrada : estradas) {
        adj[estrada.first].push_back(estrada.second);
        adj[estrada.second].push_back(estrada.first);
    }

    return DFS(N, adj, B, E);
}

int main() {
    int mapas;
    cin >> mapas;

    while (mapas--) {
        int N,M,B,E;
        cin >> N >> M >> B >> E;

        vector<pair<int, int>> estradas(M);
        for (int i = 0; i < M; ++i) {
            cin >> estradas[i].first >> estradas[i].second;
        }
        cout << custoMinimo(N, M, B, E, estradas) << endl;
    }

    return 0;
}