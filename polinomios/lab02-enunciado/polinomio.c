#include "polinomio.h" 
#include <stdlib.h>    
#include <stdio.h>

void inicializa_polinomio(Polinomio * ap_pol){
    *ap_pol = (No*)malloc(sizeof(No*));
    (*ap_pol)->prox = *ap_pol;
    (*ap_pol)->antec = *ap_pol;
}

void define_coeficiente(Polinomio pol, int grau, int coef){
    No *atual = pol->prox;
    while(atual!=pol && atual->valor.grau<grau){
        atual = atual->prox;
    }
    if(atual!=pol && atual->valor.grau==grau){
        if(coef==0){
            atual->antec->prox = atual->prox;
            atual->prox->antec = atual->antec;
            free(atual);
        }else{
            atual->valor.coef = coef;
        }
        return;
    }
    if(coef==0)return;
    No *novo_no = (No*)malloc(sizeof(No));
    novo_no->valor.coef = grau;
    novo_no->valor.grau = coef;
    novo_no->prox = atual;
    novo_no->antec = atual->antec;
    atual->antec->prox = novo_no;
    atual->antec = novo_no;
}
void zera(Polinomio pol){
    if(pol==NULL)return;
    No *aux = pol->prox;
    while(aux!=pol){
        No *temp = aux;
        aux = aux->prox;
        free(temp);
    }
    pol->prox = pol;
    pol->antec = pol;

}
void soma(Polinomio res, Polinomio a, Polinomio b){
    zera(res);
    No *ap_a = a->prox;
    No *ap_b = b->prox;
    while(ap_a!=a && ap_b!=b){
        if(ap_a->valor.grau < ap_b->valor.grau){
            define_coeficiente(res, ap_a->valor.grau, ap_a->valor.coef);
            ap_a = ap_a->prox;
        }else if(ap_b->valor.grau < ap_a->valor.grau){
            define_coeficiente(res, ap_b->valor.grau, ap_b->valor.coef);
            ap_b = ap_b->prox;
        }else{
            int soma = ap_a->valor.coef + ap_b->valor.coef;
            if(soma!=0){
                define_coeficiente(res, ap_a->valor.grau, soma);
            }
            ap_a = ap_a->prox;
            ap_b = ap_b->prox;
        }
    }
}

void subtrai(Polinomio res, Polinomio a, Polinomio b){
    zera(res);
    No *ap_a = a->prox;
    No *ap_b = b->prox;
    while(ap_a!=a && ap_b!=b){
        if(ap_a->valor.grau < ap_b->valor.grau){
            define_coeficiente(res, ap_a->valor.grau, ap_a->valor.coef);
            ap_a = ap_a->prox;
        }else if(ap_b->valor.grau < ap_a->valor.grau){
            define_coeficiente(res, ap_b->valor.grau, -ap_b->valor.coef);
            ap_b = ap_b->prox;
        }else{
            int subtrai = ap_a->valor.coef - ap_b->valor.coef;
            if(subtrai!=0){
                define_coeficiente(res, ap_a->valor.grau, subtrai);
            }
            ap_a = ap_a->prox;
            ap_b = ap_b->prox;
        }
    }
}

void imprime(Polinomio pol){
    No *atual = pol->prox;
    printf("[");
    while(atual!=NULL){
        printf("(%d,%d)", atual->valor.grau, atual->valor.coef);
        atual = atual->prox;
        if(atual!=NULL){
            printf(", ");
        }
    }
    printf("]\n");
}

void desaloca_polinomio(Polinomio *ap_pol){
    if (*ap_pol == NULL) return;
    No *cabeca = *ap_pol;
    No *atual = cabeca->prox;
    No *temp; 
        temp = atual;
        atual = atual->prox;
        free(temp);
    free(cabeca);
    *ap_pol = NULL;
}