#include <iostream>
#include <vector>

int obterMaximo(int a, int b) {
    return (a > b) ? a : b;
}

void merge(std::vector<short>& x, std::vector<short>& y, int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;
    
    std::vector<short> x1(n1), y1(n1), x2(n2), y2(n2);
    
    for (int i = 0; i < n1; i++) {
        x1[i] = x[esq + i];
        y1[i] = y[esq + i];
    }
    for (int j = 0; j < n2; j++) {
        x2[j] = x[meio + 1 + j];
        y2[j] = y[meio + 1 + j];
    }
    
    int i = 0, j = 0, k = esq;
    while (i < n1 && j < n2) {
        if (x1[i] < x2[j] || (x1[i] == x2[j] && y1[i] < y2[j])) {
            x[k] = x1[i];
            y[k] = y1[i];
            i++;
        } else {
            x[k] = x2[j];
            y[k] = y2[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        x[k] = x1[i];
        y[k] = y1[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        x[k] = x2[j];
        y[k] = y2[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<short>& x, std::vector<short>& y, int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        
        mergeSort(x, y, esq, meio);
        mergeSort(x, y, meio + 1, dir);
        
        merge(x, y, esq, meio, dir);
    }
}

void atualizarMovimentosParaCima(int i, int j, const std::vector<short>& x, const std::vector<short>& y, 
                                  std::vector<int>& movimentosParaCima, std::vector<int>& movimentosParaBaixo) {
    if (x[i] > x[j] && y[i] == y[j] + 2) {
        movimentosParaCima[i] = obterMaximo(movimentosParaCima[i], movimentosParaBaixo[j] + 1);
    }
}

void atualizarMovimentosParaBaixo(int i, int j, const std::vector<short>& x, const std::vector<short>& y, 
                                   std::vector<int>& movimentosParaCima, std::vector<int>& movimentosParaBaixo) {
    if (x[i] > x[j] && y[i] == y[j] - 2) {
        movimentosParaBaixo[i] = obterMaximo(movimentosParaBaixo[i], movimentosParaCima[j] + 1);
    }
}

void processarMovimentos(int n, const std::vector<short>& x, const std::vector<short>& y, 
                         std::vector<int>& movimentosParaCima, std::vector<int>& movimentosParaBaixo) {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            atualizarMovimentosParaCima(i, j, x, y, movimentosParaCima, movimentosParaBaixo);
            atualizarMovimentosParaBaixo(i, j, x, y, movimentosParaCima, movimentosParaBaixo);
        }
    }
}

int main() {
    int n;
    while (std::cin >> n) {
        std::vector<short> x(n), y(n);
        std::vector<int> movimentosParaCima(n, 1), movimentosParaBaixo(n, 1);

        for (int i = 0; i < n; i++) {
            std::cin >> x[i] >> y[i];
        }
        
        mergeSort(x, y, 0, n - 1);
        
        processarMovimentos(n, x, y, movimentosParaCima, movimentosParaBaixo);

        int maxMovimentos = 1;
        for (int i = 0; i < n; i++) {
            maxMovimentos = obterMaximo(maxMovimentos, obterMaximo(movimentosParaCima[i], movimentosParaBaixo[i]));
        }

        std::cout << maxMovimentos << "\n";
    }
    return 0;
}