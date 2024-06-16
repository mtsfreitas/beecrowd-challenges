#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>

using namespace std;

const int INFINITO = 9999999;

enum Cor {
    BRANCO,
    CINZENTO,
    PRETO
};

struct Vertice {
    Cor cor = BRANCO;
    int distancia = INFINITO;
    string pai = "";
};

void inicializaBFS(map<char, Vertice>& vertices, char s) {
    for (auto& [chave, vertice] : vertices) {
        vertice = Vertice();
    }
    vertices[s].cor = CINZENTO;
    vertices[s].distancia = 0;
    vertices[s].pai = "";
}

void bfs(map<char, vector<char>>& grafo, char s, map<char, Vertice>& vertices) {
    inicializaBFS(vertices, s);

    queue<char> fila;
    fila.push(s);

    while (!fila.empty()) {
        char u = fila.front();
        fila.pop();

        for (char v : grafo[u]) {
            if (vertices[v].cor == BRANCO) {
                vertices[v].cor = CINZENTO;
                vertices[v].distancia = vertices[u].distancia + 1;
                vertices[v].pai = string(1, u);
                fila.push(v);
            }
        }
        vertices[u].cor = PRETO;
    }
}

bool verificaPalavraSemelhante(map<char, vector<char>>& grafo, const string& primeiraPalavra, const string& segundaPalavra, map<char, Vertice>& vertices) {
    if (primeiraPalavra.length() != segundaPalavra.length()) {
        return false;
    }

    for (int i = 0; i < primeiraPalavra.length(); i++) {
        char letraPrimeiraPalavra = primeiraPalavra[i];
        char letraSegundaPalavra = segundaPalavra[i];

        if (letraPrimeiraPalavra != letraSegundaPalavra) {
            if (grafo.find(letraPrimeiraPalavra) == grafo.end()) {
                return false;  // A letra não está no grafo
            }

            bfs(grafo, letraPrimeiraPalavra, vertices);

            // Se ainda for branco, então não é possível alcançar
            if (vertices[letraSegundaPalavra].cor == BRANCO) { 
                return false;
            }
        }
    }
    return true;
}

int main() {
    int m, n;
    char chave, valor;
    string primeiraPalavra, segundaPalavra;
    map<char, vector<char>> grafo;
    map<int, pair<string, string>> palavras;

    cin >> m >> n;

    for (int i = 0; i < m; i++) {
        cin >> chave >> valor;
        grafo[chave].push_back(valor);
    }

    for (int i = 0; i < n; i++) {
        cin >> primeiraPalavra >> segundaPalavra;
        palavras[i] = {primeiraPalavra, segundaPalavra};
    }

    for (auto& pair : palavras) {
        // Inicializando um novo conjunto de vértices para cada par de palavras
        map<char, Vertice> vertices;  
        if (verificaPalavraSemelhante(grafo, pair.second.first, pair.second.second, vertices))
            cout << "yes\n";
        else
            cout << "no\n";
    }

    return 0;
}