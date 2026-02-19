#include <stdio.h>
#include<stdlib.h>

#define MAXN 20

typedef struct {
    int peso;
    int valor;
} Cjto;

void ler_conjunto(Cjto S[], int n) {
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &S[i].peso, &S[i].valor);
    }
}

long long soma_peso(Cjto S[], int n, unsigned long long mask) {
    long long soma = 0;
    for (int i = 0; i < n; i++) {
        if (mask & (1ULL << i)) {
            soma += S[i].peso;
        }
    }
    return soma;
}

// Calcula o valor total de um subconjunto
long long soma_valor(Cjto S[], int n, unsigned long long mask) {
    long long soma = 0;
    for (int i = 0; i < n; i++) {
        if (mask & (1ULL << i)) {
            soma += S[i].valor;
        }
    }
    return soma;
}

// Retorna o maior valor possível respeitando o limite M
long long melhor_valor(Cjto S[], int n, long long M) {
    long long melhor = 0;
    unsigned long long total = 1ULL << n;

    for (unsigned long long mask = 0; mask < total; mask++) {
        long long peso = soma_peso(S, n, mask);
        if (peso <= M) {
            long long valor = soma_valor(S, n, mask);
            if (valor > melhor) {
                melhor = valor;
            }
        }
    }
    return melhor;
}

int main(){
    int n;
    long long M;
    Cjto S[MAXN];

    scanf("%d %lld", &n, &M);
    ler_conjunto(S, n);

    printf("%lld\n", melhor_valor(S, n, M));

    return 0;
}
