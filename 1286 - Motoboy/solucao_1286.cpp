#include <iostream>
#include <vector>
using namespace std;

void lerDadosEntrada(int& N, int& P, vector<int>& tempo, vector<int>& pizzas) {
    cin >> N;
    if (N==0) return;

    cin >> P;
    tempo.resize(N);
    pizzas.resize(N);
    for (int i=0; i<N; i++) {
        cin >> tempo[i] >> pizzas[i];
    }
}

int calcularTempoMaximo(int N, int P, const vector<int>& tempo, const vector<int>& pizzas) {
    vector<int> tempoMaximoPorPizzas(P+1, 0);

    for (int i=0; i<N; i++) {
        for (int j = P; j >= pizzas[i]; j--) {
            if (tempoMaximoPorPizzas[j] < tempoMaximoPorPizzas[j-pizzas[i]]+tempo[i]) {
                tempoMaximoPorPizzas[j] = tempoMaximoPorPizzas[j-pizzas[i]]+tempo[i];
            }
        }
    }

    return tempoMaximoPorPizzas[P];
}

int main() {
    vector<int> resultados;

    while (true) {
        int N, P;
        vector<int> tempo, pizzas;
        lerDadosEntrada(N, P, tempo, pizzas);

        if (N==0) break;

        int tempoMaximo = calcularTempoMaximo(N, P, tempo, pizzas);
        resultados.push_back(tempoMaximo);
    }

    for (int resultado : resultados) {
        cout << resultado << " min." << endl;
    }

    return 0;
}