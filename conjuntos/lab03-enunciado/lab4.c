#include<stdio.h>
#include<stdbool.h>

#define MAXN 15
#define MAXM 17

typedef struct{
    int elementos[MAXN];
    int tamanho;
}Cjto;

void zera(Cjto *apc){
    apc->tamanho = 0;
}

void insere(Cjto *apc, int x){
    for(int i=0; i<apc->tamanho; i++){
        if(apc->elementos[i] == x){
            return;
        }
    }
    apc->elementos[(apc->tamanho)++] = x;
}

void remover(Cjto *apc, int x){
    for(int i=0; i<apc->tamanho; i++){
        if(apc->elementos[i] == x){
            apc->elementos[i] = apc->elementos[--(apc->tamanho)];
            return;
        }
    }
}

bool busca(Cjto *apc, int x){
    for(int i=0; i<apc->tamanho; i++){
        if(apc->elementos[i] == x){
            return true;
        }
    }
    return false;
}

void copia(Cjto *Res, Cjto A){
    zera(Res);
    for(int i=0; i<A.tamanho; i++){
        insere(Res, A.elementos[i]);  
    }
}

void uniao(Cjto *Res, Cjto A, Cjto B){
    copia(Res, A);               
    for(int i = 0; i<B.tamanho; i++){
        insere(Res, B.elementos[i]); 
    }
}


void interseccao(Cjto *Res, Cjto A, Cjto B){
    zera(Res);
    for(int i=0; i<A.tamanho; i++){
        for(int j=0; j<B.tamanho; j++){
            if(A.elementos[i] == B.elementos[j]){
               insere(Res, A.elementos[i]);
            }
        }
    }
}

bool resolve(int idx, Cjto cobertos, Cjto W[], int m, int n, int vet[], int *tam_vet){
    if(cobertos.tamanho == n){
        return true;
    }
    if(idx == m){
        return false;
    }
    if(resolve(idx+1, cobertos, W, m, n, vet, tam_vet)){ 
        return true;
    }
    Cjto inter;
    interseccao(&inter, cobertos, W[idx]);
    if(inter.tamanho == 0){
        Cjto novo;
        uniao(&novo, cobertos, W[idx]);
        vet[*tam_vet] = idx;
        (*tam_vet)++;
        if(resolve(idx+1, novo, W, m, n, vet, tam_vet)){
            return true;
        }
        (*tam_vet)--;
    }
    return false;
}

int main() {
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    Cjto W[MAXM];
    for(int i = 0; i < m; i++){
        int k; scanf("%d", &k);
        zera(&W[i]);
        for (int j = 0; j < k; j++) {
            int x; scanf("%d", &x);
            insere(&W[i], x);
        }
    }
    Cjto cobertos; zera(&cobertos);
    int vet[MAXM], tam_vet = 0;
    if(resolve(0, cobertos, W, m, n, vet, &tam_vet)){
        printf("%d\n", tam_vet);
        for(int i = 0; i < tam_vet; i++){
            int idx = vet[i];
            printf("%d", W[idx].tamanho);
            for(int j = 0; j < W[idx].tamanho; j++){
                printf(" %d", W[idx].elementos[j]);
            } 
            printf("\n"); 
        }
    }else{
        printf("Insoluvel\n");
    }
    return 0;
}