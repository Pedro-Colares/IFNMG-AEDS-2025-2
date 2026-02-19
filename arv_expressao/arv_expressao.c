#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    char Op;
    int valor;
    struct no *esq, *dir;
    int Num;
}No;

typedef struct{
    No* dado[1000];
    int topo;
}PilhaNum;

typedef struct{
    char dado[1000];
    int topo;
}PilhaOp;

void pushNum(PilhaNum* ap, No* num){
    ap->dado[++ap->topo] = num;
}

No* popNum(PilhaNum* ap){
    if (ap->topo == -1) return NULL;
    return ap->dado[ap->topo--];
}

void pushOp(PilhaOp* ap, char op){
    ap->dado[++ap->topo] = op;
}

char popOp(PilhaOp* ap){
    if (ap->topo == -1) return '\0';
    return ap->dado[ap->topo--];
}

No* novo_num(int x){
    No* num = (No*)malloc(sizeof(No));
    num->valor = x;
    num->Num = 1;
    num->esq = NULL;
    num->dir = NULL;
    num->Op = '\0';
    return num;
}

No* novo_op(char x, No* L, No* R){
    No* op = (No*)malloc(sizeof(No));
    op->Op = x;
    op->Num = 0;
    op->esq = L;
    op->dir = R;
    op->valor = 0;
    return op;
}

int precedencia(char op){
    if(op == '*' || op == '/')return 3;
    if(op == '+' || op == '-')return 2;
    if( op == '%')return 1;
    return 0;
}

void processarOperacao(PilhaNum* ap_num, PilhaOp* ap_op){
    char op = popOp(ap_op);
    No* dir = popNum(ap_num);
    No* esq = popNum(ap_num);
    pushNum(ap_num, novo_op(op, esq, dir));
}

void preOrdem_aux(No* arv, int* primeiro){
    if(!arv)return;
    if(*primeiro)*primeiro = 0;
    else printf(" ");
    if (arv->Num) printf("%d", arv->valor);
    else printf("%c", arv->Op);
    preOrdem_aux(arv->esq, primeiro);
    preOrdem_aux(arv->dir, primeiro);
}

void preOrdem(No* arv){
    int primeiro = 1;
    preOrdem_aux(arv, &primeiro);
    printf("\n");
}

void posOrdem_aux(No* arv, int* primeiro){
    if(!arv)return;
    posOrdem_aux(arv->esq, primeiro);
    posOrdem_aux(arv->dir, primeiro);
    if(*primeiro)*primeiro = 0;
    else printf(" ");
    if (arv->Num) printf("%d", arv->valor);
    else printf("%c", arv->Op);
}

void posOrdem(No* arv){
    int primeiro = 1;
    posOrdem_aux(arv, &primeiro);
    printf("\n");
}

int avaliar(No* raiz){
    if(raiz->Num) return raiz->valor;
    int a = avaliar(raiz->esq);
    int b = avaliar(raiz->dir);
    switch (raiz->Op) {
        case '*': return a * b;
        case '/': return a / b;
        case '+': return a + b;
        case '-': return a - b;
        case '%': return a % b;
    }
    return 0;
}

int main(){
    char linha[10000];
    if(!fgets(linha, sizeof(linha), stdin))return 1;
    linha[strcspn(linha, "\n")] = 0;
    PilhaNum num = {.topo = -1};
    PilhaOp op = {.topo = -1};
    char* tok = strtok(linha, " ");
    while(tok){
        if(tok[0]>='0' && tok[0]<='9'){
            pushNum(&num, novo_num(atoi(tok)));
        }else{
            while(op.topo != -1 && precedencia(op.dado[op.topo]) >= precedencia(tok[0])){
                processarOperacao(&num, &op);
            }
            pushOp(&op, tok[0]);
        }
        tok = strtok(NULL, " ");
    }
    while(op.topo != -1){
        processarOperacao(&num, &op);
    }
    No* raiz = popNum(&num);
    preOrdem(raiz);
    posOrdem(raiz);
    printf("%d\n", avaliar(raiz));
    return 0;
}
