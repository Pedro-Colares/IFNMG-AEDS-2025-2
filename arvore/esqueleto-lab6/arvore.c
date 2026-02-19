#include "Arvore.h"
#include<stdio.h>
#include<stdlib.h>

bool insere(Arvore* ap_arv, int x){
    if((*ap_arv)==NULL){
        (*ap_arv) = (No*)malloc(sizeof(No));
        (*ap_arv)->valor = x;
        (*ap_arv)->esq = NULL;
        (*ap_arv)->dir = NULL;
        return true;
    }
    if(x==(*ap_arv)->valor)return false;
    if(x<(*ap_arv)->valor){
        return insere(&((*ap_arv)->esq), x);
    }
    return insere(&((*ap_arv)->dir), x);
}

bool remove_(Arvore *ap_arv, int x){
    if (*ap_arv == NULL)
        return false;

    if (x < (*ap_arv)->valor) {
        return remove_(&((*ap_arv)->esq), x);
    } 
    else if (x > (*ap_arv)->valor) {
        return remove_(&((*ap_arv)->dir), x);
    } 
    else {
        No *temp;
        if ((*ap_arv)->esq == NULL && (*ap_arv)->dir == NULL) {
            free(*ap_arv);
            *ap_arv = NULL;
            return true;
        }
        if ((*ap_arv)->esq == NULL) {
            temp = (*ap_arv)->dir;
            free(*ap_arv);
            *ap_arv = temp;
            return true;
        }
        if ((*ap_arv)->dir == NULL) {
            temp = (*ap_arv)->esq;
            free(*ap_arv);
            *ap_arv = temp;
            return true;
        }
        temp = (*ap_arv)->esq;
        while (temp->dir != NULL)
            temp = temp->dir;

        (*ap_arv)->valor = temp->valor;
        return remove_(&((*ap_arv)->esq), temp->valor);
    }
}

bool busca(Arvore arv, int x){
    if(arv == NULL){ 
        return false;
    }
    if(arv->valor == x){
        return true;
    }    
    if(x < arv->valor){
        return busca(arv->esq, x);
    }    
    return busca(arv->dir, x); 
}

void imprime_rec(Arvore arv){
    if(arv==NULL){
        printf(".");
    }else{
        printf("[");
        printf("%d:", arv->valor);
        printf("e=");
        imprime_rec(arv->esq);
        printf(",");
        printf("d=");
        imprime_rec(arv->dir);
        printf("]");
    }
}

void imprime(Arvore arv){
    imprime_rec(arv);
    printf("\n");
}