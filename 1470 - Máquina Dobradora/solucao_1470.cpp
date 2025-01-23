#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int tamanhoEntrada, tamanhoSaida;
vector<int> fitaEntrada, fitaSaida;

bool isSolucao(const vector<int>& sequencia) {
    if (sequencia.size() == tamanhoSaida) {
        for (int i=0; i <tamanhoSaida; ++i) {
            if (sequencia[i] != fitaSaida[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

vector<int> gerarSequencia(const vector<int>& base, int inicio) {
    vector<int> resultado;
    int esquerda = inicio-1, direita = inicio;
    while (esquerda >=0 && direita < base.size()) {
        resultado.push_back(base[esquerda--] + base[direita++]);
    }
    while (direita < base.size()) {
        resultado.push_back(base[direita++]);
    }
    while (esquerda >=0) {
        resultado.push_back(base[esquerda--]);
    }
    return resultado;
}

bool resolver() {
    queue<vector<int>> fila;
    for (int i=1; i <= tamanhoEntrada; ++i) {
        vector<int> base = fitaEntrada;
        auto sequencia = gerarSequencia(base, i);
        if (sequencia.size() >= tamanhoSaida) {
            vector<int> sequenciaInvertida(sequencia.rbegin(), sequencia.rend());
            if (isSolucao(sequencia) || isSolucao(sequenciaInvertida)) {
                return true;
            }
            fila.push(sequencia);
        }
    }

    while (!fila.empty()) {
        auto atual = fila.front();
        fila.pop();
        for (int i = 1; i < atual.size(); ++i) {
            auto sequencia = gerarSequencia(atual, i);
            if (sequencia.size() >= tamanhoSaida) {
                vector<int> sequenciaInvertida(sequencia.rbegin(), sequencia.rend());
                if (isSolucao(sequencia) || isSolucao(sequenciaInvertida)) {
                    return true;
                }
                fila.push(sequencia);
            }
        }
    }
    return false;
}

int main() {
    while (cin >> tamanhoEntrada) {
        fitaEntrada.clear();
        fitaSaida.clear();

        fitaEntrada.resize(tamanhoEntrada);
        for (int i = 0; i < tamanhoEntrada; ++i) {
            cin >> fitaEntrada[i];
        }
        cin >> tamanhoSaida;
        fitaSaida.resize(tamanhoSaida);
        for (int i = 0; i < tamanhoSaida; ++i) {
            cin >> fitaSaida[i];
        }

        cout << (resolver() ? "S" : "N") << endl;
    }
    return 0;
}