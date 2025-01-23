#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Vertice {
    string cor ="WHITE";  // Cor para o estado do vértice (branco, cinza, preto)
    int distancia = 1e9;   // Distância inicial, valor alto para indicar não visitado
    string antecessor = ""; // Vértice anterior no caminho mais curto
};

void BFS(const unordered_map<string, vector<string>>& grafo, const string& inicio, unordered_map<string, bool>& visitados) {
    unordered_map<string, Vertice> vertices;

    // Inicializa todos os vértices do grafo
    for (const auto& par : grafo) {
        vertices[par.first] = Vertice();
    }

    // Configura o vértice de início
    vertices[inicio].cor = "GRAY";
    vertices[inicio].distancia = 0;

    queue<string> fila;
    fila.push(inicio);

    // Executa a busca em largura BFS
    while (!fila.empty()) {
        string vertice_atual = fila.front();
        fila.pop();

        visitados[vertice_atual] = true; // Marca o vértice como visitado
        for (const string& vizinho : grafo.at(vertice_atual)) {
            if (vertices[vizinho].cor == "WHITE") {
                vertices[vizinho].cor = "GRAY";
                vertices[vizinho].distancia = vertices[vertice_atual].distancia + 1;
                vertices[vizinho].antecessor = vertice_atual;
                fila.push(vizinho);
            }
        }
    vertices[vertice_atual].cor = "BLACK"; // Marca o vértice como completamente explorado
    }
}

int main() {
    int num_animais, num_relacoes, num_testes;
    cin >> num_animais >> num_relacoes >> num_testes;

    unordered_map<string, vector<string>> grafo;

    for (int i = 0; i < num_relacoes; ++i) {
        string pai1, pai2, filho;
        cin >> pai1 >> pai2 >> filho;

        grafo[filho].push_back(pai1);
        grafo[filho].push_back(pai2);

        if (grafo.find(pai1) == grafo.end()) grafo[pai1] = {};
        if (grafo.find(pai2) == grafo.end()) grafo[pai2] = {};
    }

    vector<string> resultados;

    for (int i = 0; i < num_testes; ++i) {
        string animal1, animal2;
        cin >> animal1 >> animal2;

        unordered_map<string, bool> visitados_animal1, visitados_animal2;

        // Executa a BFS para ambos os animais
        BFS(grafo, animal1, visitados_animal1);
        BFS(grafo, animal2, visitados_animal2);

        bool tem_ancestral_comum = false;
        for (const auto& par : visitados_animal1) {
            if (par.second && visitados_animal2[par.first]) {
                tem_ancestral_comum = true; break;                
            }
        }
        resultados.push_back(tem_ancestral_comum ? "verdadeiro" : "falso");
    }

    for (const auto& resultado : resultados) {
        cout << resultado << endl;
    }

    return 0;
}