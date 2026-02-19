#include <stdio.h>
#include <stdlib.h>
#include "Arvore_AVL.h"

Arvore novo(int x){
    Arvore new = malloc(sizeof(No));
    new->valor = x;
    new->altura = 0;
    new->esq = new->dir = NULL;
    return new;
}

int height(Arvore ap_arv){
    if(ap_arv == NULL) return -1;
    return ap_arv->altura;
}

int max(int a, int b){
    return (a > b ? a : b);
}

void rodaE(Arvore *ap_arv){
    Arvore no = *ap_arv;
    Arvore y = no->dir;
    no->dir = y->esq;
    y->esq = no;
    no->altura = 1 + max(height(no->esq), height(no->dir));
    y->altura = 1 + max(height(y->esq), height(y->dir));
    *ap_arv = y;
}

void rodaD(Arvore *ap_arv){
    Arvore no = *ap_arv;
    Arvore y = no->esq;
    no->esq = y->dir;
    y->dir = no;
    no->altura = 1 + max(height(no->esq), height(no->dir));
    y->altura = 1 + max(height(y->esq), height(y->dir));
    *ap_arv = y;
}

bool insere(Arvore* ap_arv, int x){
    if(*ap_arv == NULL){
        *ap_arv = novo(x);
        return true;
    }
    if((*ap_arv)->valor == x) return false;

    if(x < (*ap_arv)->valor){
        if(!insere(&((*ap_arv)->esq), x)) return false;
    } else {
        if(!insere(&((*ap_arv)->dir), x)) return false;
    }
    (*ap_arv)->altura = 1 + max(height((*ap_arv)->esq), height((*ap_arv)->dir));

    int fb = height((*ap_arv)->esq) - height((*ap_arv)->dir);
    if(fb == 2){
        if(x < (*ap_arv)->esq->valor){ 
            rodaD(ap_arv);
        } else {                       
            rodaE(&((*ap_arv)->esq));
            rodaD(ap_arv);
        }
    }
    if(fb == -2){
        if(x > (*ap_arv)->dir->valor){ 
            rodaE(ap_arv);
        } else {                       
            rodaD(&((*ap_arv)->dir));
            rodaE(ap_arv);
        }
    }

    return true;
}

bool busca(Arvore arv, int x){
    if(arv == NULL) return false;
    if(arv->valor == x) return true;
    if(x < arv->valor) return busca(arv->esq, x);
    return busca(arv->dir, x);
}