#include <iostream>
#include <vector>


using namespace std;

bool podeComer(long long tempo, const vector<int>& pipocas, int qtdSacosPipoca, int qtdCompetidores, int qtdMaxPipocaPorSegundo) {
    long long competidores = 1;
    long long tempoRestante = tempo * qtdMaxPipocaPorSegundo;
    for (int i = 0; i < qtdSacosPipoca; ++i) {
        if (pipocas[i] > tempo * qtdMaxPipocaPorSegundo) { return false; }
        if (pipocas[i] > tempoRestante) {
            competidores++;
            if (competidores > qtdCompetidores) { return false; }
            tempoRestante = tempo * qtdMaxPipocaPorSegundo;
        }
        tempoRestante -= pipocas[i];
    }
    return true;
}

int encontrarValorMaximo(const vector<int>& v) {
    int maxValor = v[0];
    for (int i = 1; i < v.size(); ++i) {
        if (v[i] > maxValor) {
            maxValor = v[i];
        }
    }
    return maxValor;
}

int encontrarMenorTempo(const vector<int>& pipocas, int qtdSacosPipoca, int qtdCompetidores, int qtdMaxPipocaPorSegundo) {
    long long esquerda = 1;
    long long direita = encontrarValorMaximo(pipocas) * qtdSacosPipoca;

    while (esquerda < direita) {
        long long meio = (esquerda + direita) /2;
        if (podeComer(meio, pipocas, qtdSacosPipoca, qtdCompetidores, qtdMaxPipocaPorSegundo)) {
            direita = meio;
        } else {
            esquerda = meio + 1;
        }
    }
    return esquerda;
}

int main() {
    int qtdSacosPipoca, qtdCompetidores, qtdMaxPipocaPorSegundo;
    cin >> qtdSacosPipoca >> qtdCompetidores >> qtdMaxPipocaPorSegundo;

    vector<int> pipocas(qtdSacosPipoca);
    for (int i = 0; i < qtdSacosPipoca; ++i) {
        cin >> pipocas[i];
    }

    int menorTempo = encontrarMenorTempo(pipocas, qtdSacosPipoca, qtdCompetidores, qtdMaxPipocaPorSegundo);
    cout << menorTempo << endl;

    return 0;
}