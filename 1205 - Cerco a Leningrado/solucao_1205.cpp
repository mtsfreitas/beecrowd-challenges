#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

void initializeSingleSource(int N, vector<double>& probabilidades, int start, const vector<int>& atiradores, int numBalas, double probabilidade) {
    probabilidades.assign(N, 0.0);
    probabilidades[start] = pow(probabilidade, min(atiradores[start], numBalas));
}

void relax(int u, int v, int numBalas, double probabilidade, vector<double>& probabilidades, priority_queue<pair<double, int>>& fila, const vector<int>& atiradores) {
    double novaProb = probabilidades[u] * pow(probabilidade, min(atiradores[v], numBalas));
    if (novaProb > probabilidades[v]) {
        probabilidades[v] = novaProb;
        fila.push({novaProb, v});
    }
}

double dijkstra(const vector<vector<int>>& grafo, int start, int end, const vector<int>& atiradores, int numBalas, double probabilidade) {
    vector<double> probabilidades(grafo.size(), 0.0);
    initializeSingleSource(grafo.size(), probabilidades, start, atiradores, numBalas, probabilidade);

    priority_queue<pair<double, int>> fila;
    fila.push({probabilidades[start], start});

    vector<bool> visitado(grafo.size(), false);

    while (!fila.empty()) {
        int u = fila.top().second;
        fila.pop();
        
        if (!visitado[u]) {
            visitado[u] = true;
        
            if (u == end) {
                return probabilidades[u];
            }
        
            for (int v : grafo[u]) {
                relax(u, v, numBalas, probabilidade, probabilidades, fila, atiradores);
            }
        }
    }

    return 0.0;
}

int main() {
    int pontosEstrategicos, estradas, balas;
    double probabilidade;
    while (cin >> pontosEstrategicos >> estradas >> balas >> probabilidade) {
        vector<vector<int>> grafo(pontosEstrategicos);
        for (int i = 0; i < estradas; i++) {
            int u, v;
            cin >> u >> v;
            u = u -1;
            v = v -1;
            grafo[u].push_back(v);
            grafo[v].push_back(u);
        }

        int numAtiradores;
        cin >> numAtiradores;

        vector<int> atiradores(pontosEstrategicos, 0);
        for (int i = 0; i < numAtiradores; i++) {
            int posicao;
            cin >> posicao;
            posicao = posicao -1;
            atiradores[posicao]++;
        }

        int start, end;
        cin >> start >> end;
        start = start -1; 
        end = end -1;   

        double result = dijkstra(grafo, start, end, atiradores, balas, probabilidade);
        printf("%.3f\n", result);
    }

    return 0;
}