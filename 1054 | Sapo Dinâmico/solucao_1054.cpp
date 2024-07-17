#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Estado {
    int puloMaximo;
    int distancia;
    int pedraSmall;
    int pedraBig;

    Estado() : puloMaximo(0), distancia(0), pedraSmall(-1), pedraBig(0) {}
};

int calcularMaxPulo(vector<char> &tiposDePedras, vector<int> &distancias, int quantidadeDePedras, int d) {
    Estado estado;

    //ida
    for (int i = 0; i <= quantidadeDePedras + 1; i++) {
        if (tiposDePedras[i] == 'S') estado.pedraSmall++;
        if (tiposDePedras[i] == 'B') estado.pedraBig++;
        if (tiposDePedras[i] == 'B' || (estado.pedraSmall % 2 == 0 && tiposDePedras[i] == 'S')) {
            int pulo_atual = distancias[i] - estado.distancia;
            if (pulo_atual > estado.puloMaximo) {
                estado.puloMaximo = pulo_atual;
            }
            estado.distancia = distancias[i];
        }
    }

    estado.pedraSmall++;
    estado.pedraBig--;

    //volta
    for (int i = quantidadeDePedras + 1; i >= 0; i--) {
        if (tiposDePedras[i] == 'S') estado.pedraSmall--;
        if (tiposDePedras[i] == 'B') estado.pedraBig--;
        if (tiposDePedras[i] == 'B' || (estado.pedraSmall % 2 == 1 && tiposDePedras[i] == 'S')) {
            int pulo_atual = estado.distancia - distancias[i];
            if (pulo_atual > estado.puloMaximo) {
                estado.puloMaximo = pulo_atual;
            }
            estado.distancia = distancias[i];
        }
    }

    return estado.puloMaximo;
}

int main() {
    int n;
    cin >> n;
    for (int k=0; k<n; k++) {
        int quantidadeDePedras, d;
        cin >> quantidadeDePedras >> d;

        vector<char> tiposDePedras(quantidadeDePedras + 2);
        vector<int> distancias(quantidadeDePedras + 2);

        for (int i=1; i<=quantidadeDePedras; i++) {
            string p;
            cin >> p;
            tiposDePedras[i] = p[0];
            distancias[i] = stoi(p.substr(2));
        }

        tiposDePedras[0] = 'B';
        distancias[0] =0;
        tiposDePedras[quantidadeDePedras + 1] = 'B';
        distancias[quantidadeDePedras + 1] = d;

        int max_pulo = calcularMaxPulo(tiposDePedras, distancias, quantidadeDePedras, d);
        cout << "Case " << (k+1) << ": " << max_pulo << endl;
    }
    return 0;
}
