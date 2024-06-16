#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

const int INFINITO = 9999999;

struct Palavra {
    string idiomaDestino;
    string palavra;
    char inicial;

    Palavra(const string& idiomaDestino, const string& palavra) {
        this->idiomaDestino = idiomaDestino;
        this->palavra = palavra;
        this->inicial = palavra[0];
    }
};

struct EstadoDoVertice {
    string idioma;
    int distancia;
    char ultimaInicial;

    EstadoDoVertice(const string& idioma, int distancia, char ultimaInicial) {
        this->idioma = idioma;
        this->distancia = distancia;
        this->ultimaInicial = ultimaInicial;
    }

    bool operator>(const EstadoDoVertice& other) const {
        return this->distancia > other.distancia;
    }
};

void InitializeSingleSource(unordered_map<string, unordered_map<char, int>>& distancias, const string& idiomaOrigem) {
    for (auto& [idioma, mapa] : distancias) {
        for (char c = 'a'; c <= 'z'; ++c) {
            mapa[c] = INFINITO;
        }
    }
    distancias[idiomaOrigem][0] = 0;
}

void Relax(const EstadoDoVertice& estadoAtual, const Palavra& info, unordered_map<string, unordered_map<char, int>>& distancias, priority_queue<EstadoDoVertice, vector<EstadoDoVertice>, greater<>>& fila) {
    if (info.inicial != estadoAtual.ultimaInicial) {
        int novaDistancia = estadoAtual.distancia + info.palavra.length();
        if (novaDistancia < distancias[info.idiomaDestino][info.inicial]) {
            distancias[info.idiomaDestino][info.inicial] = novaDistancia;
            fila.emplace(info.idiomaDestino, novaDistancia, info.inicial);
        }
    }
}

int Dijkstra(unordered_map<string, vector<Palavra>>& grafo, const string& idiomaOrigem, const string& idiomaDestino) {
    unordered_map<string, unordered_map<char, int>> distancias;
    for (const auto& [idioma, _] : grafo) {
        distancias[idioma] = unordered_map<char, int>();
    }
    priority_queue<EstadoDoVertice, vector<EstadoDoVertice>, greater<>> fila;

    InitializeSingleSource(distancias, idiomaOrigem);
    fila.emplace(idiomaOrigem, 0, 0);

    while (!fila.empty()) {
        EstadoDoVertice estadoAtual = fila.top();
        fila.pop();

        for (const auto& info : grafo[estadoAtual.idioma]) {
            Relax(estadoAtual, info, distancias, fila);
        }
    }

    int menorDistancia = INFINITO;
    for (const auto& [inicial, distancia] : distancias[idiomaDestino]) {
        if (distancia < menorDistancia) {
            menorDistancia = distancia;
        }
    }

    return (menorDistancia == INFINITO) ? -1 : menorDistancia;
}

int main() {
    int totalPalavrasCompiladas;
    string idiomaOrigem, idiomaDestino;
    string idioma1, idioma2, palavraEmComum;
    unordered_map<string, vector<Palavra>> grafo;

    while (cin >> totalPalavrasCompiladas && totalPalavrasCompiladas != 0) {
        cin >> idiomaOrigem >> idiomaDestino;

        grafo.clear();
        for (int i = 0; i < totalPalavrasCompiladas; ++i) {
            cin >> idioma1 >> idioma2 >> palavraEmComum;
            grafo[idioma1].emplace_back(idioma2, palavraEmComum);
            grafo[idioma2].emplace_back(idioma1, palavraEmComum);
        }

        int resultado = Dijkstra(grafo, idiomaOrigem, idiomaDestino);
        if (resultado == -1) {
            cout << "impossivel" << endl;
        } else {
            cout << resultado << endl;
        }
    }

    return 0;
}