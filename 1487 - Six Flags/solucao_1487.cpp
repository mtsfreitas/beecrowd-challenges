#include <iostream>
#include <vector>
using namespace std;

struct Atracao {
    int duracao;
    int pontuacao;
};

struct Caso {
    int T;
    vector<Atracao> atracoes;
};

vector<Caso> lerCasos() {
    vector<Caso> casos;
    int N, T;

    while (true) {
        cin >> N >> T;
        if (N == 0 && T == 0) {
            break;
        }
        Caso caso;
        caso.T = T;
        caso.atracoes.resize(N);

        for (int i = 0; i < N; ++i) {
            cin >> caso.atracoes[i].duracao >> caso.atracoes[i].pontuacao;
        }

        casos.push_back(caso);
    }

    return casos;
}

int resolverCaso(int T, const vector<Atracao>& atracoes) {
    vector<int> pontuacaoMaxima(T+1, 0);

    for (const auto& atracao : atracoes) {
        for (int t = atracao.duracao; t <= T; ++t) {
            pontuacaoMaxima[t] = max(pontuacaoMaxima[t], pontuacaoMaxima[t-atracao.duracao]+atracao.pontuacao);
        }
    }
    return pontuacaoMaxima[T];
}

void processarCasos(const vector<Caso>& casos) {
    for (size_t instancia = 0; instancia < casos.size(); ++instancia) {
        const auto& caso = casos[instancia];

        int resultado = resolverCaso(caso.T, caso.atracoes);
        cout << "Instancia " << instancia+1 << "\n";
        cout << resultado << "\n\n";
    }
}

int main() {
    auto casos = lerCasos();
    processarCasos(casos);
    
    return 0;
}