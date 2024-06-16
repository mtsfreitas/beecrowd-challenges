#include <vector>
#include <iostream>

using namespace std;

vector<int> pai, altura;

struct Sensor {
    int x,y,sensibilidade;
};

void inicializarUnionFind(int n) {
    pai.resize(n);
    altura.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        pai[i] = i;
    }
}

int find(int u) {
    if (pai[u] != u) {
        pai[u] = find(pai[u]);
    }
    return pai[u];
}

void unir(int u, int v) {
    int paiU = find(u);
    int paiV = find(v);
    if (paiU != paiV) {
        if (altura[paiU] < altura[paiV]) {
            pai[paiU] = paiV;
        } else if (altura[paiU] > altura[paiV]) {
            pai[paiV] = paiU;
        } else {
            pai[paiV] = paiU;
            altura[paiU]++;
        }
    }
}

bool verificaProximo(int x1, int y1, int x2, int y2, int sensibilidade) {
    int dx = x1 - x2;
    int dy = y1 - y2;
    return dx * dx + dy * dy <= sensibilidade*sensibilidade;
}

int main() {
    int M,N,K;
    cin >> M >> N >> K;

    vector<Sensor> sensores(K);
    for (auto &sensor : sensores) {
        cin >> sensor.x >> sensor.y >> sensor.sensibilidade;
    }

    // sensores + 4 bordas
    inicializarUnionFind(K + 4);

    for (int i = 0; i < K; ++i) {
        // esquerda
        if (sensores[i].x <= sensores[i].sensibilidade) {
            unir(i, K);
        }
        // direita
        if (M - sensores[i].x <= sensores[i].sensibilidade) {
            unir(i, K + 1);
        }
        // cima
        if (sensores[i].y <= sensores[i].sensibilidade) {
            unir(i, K + 2);
        }
        // baixo
        if (N - sensores[i].y <= sensores[i].sensibilidade) {
            unir(i, K + 3);
        }

        for (int j = i + 1; j < K; ++j) {
            if (verificaProximo(sensores[i].x, sensores[i].y, sensores[j].x, sensores[j].y, sensores[i].sensibilidade + sensores[j].sensibilidade)) {
                unir(i, j);
            }
        }
    }

    if (find(K) == find(K + 1) || find(K + 2) == find(K + 3) || find(K) == find(K + 2) || find(K + 1) == find(K + 3)) {
        cout << 'N' << endl;
    } else {
        cout << 'S' << endl;
    }
    return 0;
}