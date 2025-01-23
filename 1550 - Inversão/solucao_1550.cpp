#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum Cor { WHITE, GRAY, BLACK };

struct Vertice {
    Cor cor = WHITE;
    int distancia = 1e9;
    int antecessor = 0; 
};

int inverter(int num) {
    int invertido = 0;
    while (num > 0) {
        invertido = invertido*10 + (num%10);
        num /= 10; 
    }
    return invertido;
}


void bfs(int A, int B, vector<int>& resultados) {
    vector<Vertice> vertices(10000);
    vector<int> fila;
    int inicio = 0, fim = 0;

    vertices[A].cor = GRAY;
    vertices[A].distancia = 0;
    vertices[A].antecessor = 0; 

    fila.push_back(A);
    fim++;

    while (inicio < fim) {
        int u = fila[inicio];
        inicio++;

        if (u == B) {
            resultados.push_back(vertices[u].distancia);
            return;
        }

        if (u + 1 < 10000 && vertices[u+1].cor == WHITE) {
            vertices[u + 1].cor = GRAY;
            vertices[u + 1].distancia = vertices[u].distancia + 1;
            vertices[u + 1].antecessor = u;
            fila.push_back(u + 1);
            fim = fim+1;
        }

        int invertido = inverter(u);
        if (invertido < 10000 && vertices[invertido].cor == WHITE) {
            vertices[invertido].cor = GRAY;
            vertices[invertido].distancia = vertices[u].distancia +1;
            vertices[invertido].antecessor = u;
            fila.push_back(invertido);
            fim = fim +1;
        }
        vertices[u].cor = BLACK;
    }

    resultados.push_back(-1);
}

int main() {
    int casosDeTeste;
    cin >> casosDeTeste;

    vector<int> resultados; 

    while (casosDeTeste--) {
        int inicialVisor,finalVisor;
        cin >> inicialVisor >> finalVisor;

        bfs(inicialVisor,finalVisor,resultados);
    }

    for (int resultado : resultados) {
        cout << resultado << endl;
    }

    return 0;
}