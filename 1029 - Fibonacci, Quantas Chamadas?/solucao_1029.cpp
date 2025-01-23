#include <iostream>
#include <vector>
using namespace std;

void inicializarCasosBase(vector<int>& fib, vector<int>& chamadas) {
    fib[0] = 0, chamadas[0] = 0;
    if (fib.size() > 1) fib[1] = 1, chamadas[1] = 0;
}

//Utilizando memoization

int calcularFibonacci(int n, vector<int>& fib, vector<int>& chamadas) {
    if (fib[n] != -1) return fib[n];

    fib[n] = calcularFibonacci(n-1, fib, chamadas)+calcularFibonacci(n-2, fib, chamadas);
    chamadas[n] = chamadas[n-1] + chamadas[n-2] + 2;
    return fib[n];
}

int main() {
    int casos;
    cin >> casos;

    vector<int> entradas(casos);
    for (int i = 0; i < casos; i++) {
        cin >> entradas[i];
    }

    for (int n : entradas) {
        vector<int> fib(n+1, -1); 
        vector<int> chamadas(n+1, -1); 

        inicializarCasosBase(fib, chamadas);
        int resultado = calcularFibonacci(n, fib, chamadas);

        cout << "fib(" << n << ") = " << chamadas[n] << " calls = " << resultado << endl;
    }

    return 0;
}