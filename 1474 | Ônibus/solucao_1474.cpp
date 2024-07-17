#include <iostream>
using namespace std;

const long long MODULO = 1000000;

struct Matriz {
    long long matriz[2][2];
    Matriz operator*(const Matriz& other) const {
        Matriz result = {0};
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    result.matriz[i][j] = (result.matriz[i][j] + matriz[i][k] * other.matriz[k][j]) % MODULO;
        return result;
    }
};

int main() {
    // n: Comprimento Total
    // k: Cores distintas para micro-ônibus
    // l: Cores distintas para ônibus
    long long n, k, l;
    while (cin >> n >> k >> l) {
        k %= MODULO;
        l %= MODULO;

        // Matrizes
        Matriz base = {{{k, l}, {1, 0}}};
        Matriz resultado = {{{1, 0}, {0, 1}}};

        // Simplificando pois os onibus são multiplos de 5
        long long exp = n/5;
        while (exp) {
            if (exp%2) {
                resultado = resultado * base;
            }
            base = base * base;
            exp /= 2;
        }

        long long finalResult = (resultado.matriz[0][0]) % MODULO;
        printf("%06lld\n", finalResult);
    }
    return 0;
}
