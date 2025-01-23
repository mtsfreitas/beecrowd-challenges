#include <iostream>
#include <string>
#include <vector>
using namespace std;

string encontrarMaior(int N, int D, const string& numero) {
    vector<char> pilha;
    int apagar = D;

    for (char digito : numero) {
        while (!pilha.empty() && apagar > 0 && pilha.back() < digito) {
            pilha.pop_back();
            apagar = apagar - 1;
        }
        pilha.push_back(digito);
    }

    while (apagar > 0) {
        pilha.pop_back();
        apagar = apagar - 1;
    }

    return string(pilha.begin(), pilha.begin() + (N - D));
}

vector<pair<int, string>> lerEntradas() {
    vector<pair<int, string>> entradas;
    int N,D;
    cin >> N >> D;

    while (N != 0 || D != 0) {
        string numero;
        cin >> numero;

        entradas.emplace_back(D, numero);

        cin >> N >> D;
    }

    return entradas;
}

vector<string> processarResultados(const vector<pair<int, string>>& entradas) {
    vector<string> resultados;
    for (const auto& entrada : entradas) {
        int N = entrada.second.size();
        int D = entrada.first;
        const string& numero = entrada.second;
        resultados.push_back(encontrarMaior(N, D, numero));
    }
    return resultados;
}

void exibirResultados(const vector<string>& resultados) {
    for (const string& res : resultados) {
        cout << res << endl;
    }
}

int main() {
    vector<pair<int, string>> entradas = lerEntradas();
    vector<string> resultados = processarResultados(entradas);
    exibirResultados(resultados);
    return 0;
}