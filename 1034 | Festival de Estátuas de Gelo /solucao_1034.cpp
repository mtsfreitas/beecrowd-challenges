#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

const int INF = 1000000;

int calcularMinBlocos(int comprimentoDesejado, const vector<int>& comprimentosBlocos) {
    vector<int> dp(comprimentoDesejado + 1, INF);
    dp[0] = 0;

    for (int i =1; i <= comprimentoDesejado; ++i) {
        for (int bloco : comprimentosBlocos) {
            if (i >= bloco) {
                dp[i] = min(dp[i], dp[i - bloco]+1);
            }
        }
    }

    return dp[comprimentoDesejado];
}

void lerDadosECalcular() {
    int numeroDeInstancias;
    cin >> numeroDeInstancias;

    for (int instancia=0; instancia < numeroDeInstancias; ++instancia) {
        int numeroDeBlocos, comprimentoDesejado;
        cin >> numeroDeBlocos >> comprimentoDesejado;
        vector<int> comprimentosBlocos(numeroDeBlocos);
        for (int& bloco : comprimentosBlocos) {
            cin >> bloco;
        }

        cout << calcularMinBlocos(comprimentoDesejado,comprimentosBlocos) << endl;
    }
}

int main() {
    lerDadosECalcular();
    return 0;
}
