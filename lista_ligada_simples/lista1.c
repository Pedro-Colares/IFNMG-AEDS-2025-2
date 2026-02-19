#include "lista.h"
#include<stdio.h>
#include<stdlib.h>

void inicializa_lista(Lista *ap_lista){
    *ap_lista=NULL;
}

void insere_inicio(Lista *ap_lista,int valor){
    No *novo_no=(No *)malloc(sizeof(No));
    if(novo_no==NULL)return;
    novo_no->valor=valor;
    novo_no->proximo=*ap_lista;
    *ap_lista=novo_no;
}

void insere_fim(Lista *ap_lista,int valor){
    No *novo_no=(No *)malloc(sizeof(No));
    if(novo_no==NULL)return;
    novo_no->valor=valor;
    novo_no->proximo=NULL;
    if(*ap_lista==NULL){
        *ap_lista=novo_no;
        return;
    }
    No *aux=*ap_lista;
    while(aux->proximo!=NULL)aux=aux->proximo;
    aux->proximo=novo_no;
}

int remove_inicio(Lista *ap_lista){
    if(*ap_lista==NULL)return -1;
    No *removido=*ap_lista;
    int valor=removido->valor;
    *ap_lista=removido->proximo;
    free(removido);
    return valor;
}

int remove_fim(Lista *ap_lista){
    if(*ap_lista==NULL)return -1;
    No *aux=*ap_lista;
    if(aux->proximo==NULL){
        int valor=aux->valor;
        free(aux);
        *ap_lista=NULL;
        return valor;
    }
    while(aux->proximo->proximo!=NULL)aux=aux->proximo;
    int valor=aux->proximo->valor;
    free(aux->proximo);
    aux->proximo=NULL;
    return valor;
}

int remove_ocorrencias(Lista *ap_lista,int valor){
    int qtd=0;
    while(*ap_lista!=NULL&&(*ap_lista)->valor==valor){
        No *removido=*ap_lista;
        *ap_lista=removido->proximo;
        free(removido);
        qtd++;
    }
    No *aux=*ap_lista;
    while(aux!=NULL&&aux->proximo!=NULL){
        if(aux->proximo->valor==valor){
            No *removido=aux->proximo;
            aux->proximo=removido->proximo;
            free(removido);
            qtd++;
        }else aux=aux->proximo;
    }
    return qtd;
}

int busca(Lista lista,int valor){
    int pos=1;
    No *aux=lista;
    while(aux!=NULL){
        if(aux->valor==valor)return pos;
        aux=aux->proximo;
        pos++;
    }
    return -1;
}

bool remove_i_esimo(Lista *ap_lista,int i){
    int tam=tamanho(*ap_lista);
    if(i<1||i>tam)return false;
    if(i==1){
        remove_inicio(ap_lista);
        return true;
    }
    No *anterior=*ap_lista;
    for(int j=1;j<i-1;j++)anterior=anterior->proximo;
    No *a_remover=anterior->proximo;
    anterior->proximo=a_remover->proximo;
    free(a_remover);
    return true;
}

int tamanho(Lista lista){
    int cont=0;
    No *aux=lista;
    while(aux!=NULL){
        cont++;
        aux=aux->proximo;
    }
    return cont;
}

int recupera_i_esimo(Lista lista,int i){
    if(i<1||i>tamanho(lista))return -1;
    No *aux=lista;
    for(int j=1;j<i;j++)aux=aux->proximo;
    return aux->valor;
}

void imprime(Lista lista){
    printf("(");

    No *aux = lista;

    while(aux != NULL){
        printf("%d", aux->valor);

        if(aux->proximo != NULL){
            printf(",");
        }

        aux = aux->proximo;
    }

    printf(")\n");
}


void desaloca_lista(Lista *ap_lista){
    No *aux=*ap_lista;
    while(aux!=NULL){
        No *temp=aux;
        aux=aux->proximo;
        free(temp);
    }
    *ap_lista=NULL;
}
