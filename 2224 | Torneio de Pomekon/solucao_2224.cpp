#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

//distância euclidiana entre dois pontos
double calcular_distancia(pair<int, int>& p1, pair<int, int>& p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

int main() {
    int numInstancias;
    cin >> numInstancias;

    for (int i = 0; i < numInstancias; i++) {
        int N;
        cin >> N;
        vector<pair<int, int>> mestres(N);

        for (int j = 0; j < N; ++j) {
            cin >> mestres[j].first >> mestres[j].second;
        }

        int quantidadeDeEstados = 1 << N;
        vector<double> dp(quantidadeDeEstados, 1e9);

        dp[0] = 0;

        for (int estadoAtual = 0; estadoAtual < quantidadeDeEstados; ++estadoAtual) {
            for (int i = 0; i < N; ++i) {
                for (int j = i + 1; j < N; ++j) {
                    if (!(estadoAtual & (1 << i)) && !(estadoAtual & (1 << j))) {
                        int novoEstado = estadoAtual | (1 << i) | (1 << j);
                        double novaDistancia = calcular_distancia(mestres[i], mestres[j]);
                        dp[novoEstado] = min(dp[novoEstado], dp[estadoAtual] + novaDistancia);
                    }
                }
            }
        }

        double menor_soma = dp[quantidadeDeEstados - 1];
        printf("%.2f\n", menor_soma);
    }

    return 0;
}