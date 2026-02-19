#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct no{
  int valor;
  struct no *esq, *dir;
}No;

bool insere(No **arv, int x){
  if((*arv)==NULL){
    (*arv) = (No*)malloc(sizeof(No));
    (*arv)->valor = x;
    (*arv)->esq = NULL;
    (*arv)->dir = NULL;
    return true;
  }
  if(x==(*arv)->valor)return false;
  if(x<(*arv)->valor){
    return insere(&((*arv)->esq), x);
  }else{
    return insere(&((*arv)->dir), x);
  }
}

bool busca(No *arv, int x){
  if(arv==NULL)return false;
  if(x==arv->valor)return true;
  if(x<arv->valor){
    return busca(arv->esq, x);
  }else{
    return busca(arv->dir, x);
  }
}

int tamanho(No *arv){
  if(arv==NULL)return 0;
  return 1 + tamanho(arv->esq)+tamanho(arv->dir);
}
#define ESPACO 10
void imprimeGrafico(No *arvore, int nivel){
    if(arvore == NULL)
        return;
    imprimeGrafico(arvore->dir, nivel + 1);
    for(int i = 0; i < nivel * ESPACO; i++)
        printf(" ");
    printf("%d\n", arvore->valor);
    imprimeGrafico(arvore->esq, nivel + 1);
}

bool remover(No **arv, int x){
    if(*arv == NULL)
        return false;

    if(x < (*arv)->valor){
        return remover(&((*arv)->esq), x);
    }
    else if(x > (*arv)->valor){
        return remover(&((*arv)->dir), x);
    }
    // Se chegou aqui, encontrou o nó que deve ser removido
    No* aux = *arv;
    // Caso 1: nó folha
    if(aux->esq == NULL && aux->dir == NULL){
        free(aux);
        *arv = NULL;
    }
    // Caso 2A: só filho direito
    else if(aux->esq == NULL){
        *arv = aux->dir;
        free(aux);
    }
    // Caso 2B: só filho esquerdo
    else if(aux->dir == NULL){
        *arv = aux->esq;
        free(aux);
    }
    // Caso 3: dois filhos
    else{
        // pegar menor elemento da subárvore direita (sucessor)
        No *temp = aux->dir;
        while(temp->esq != NULL)
            temp = temp->esq;

        // copia valor do sucessor
        aux->valor = temp->valor;

        // remove o sucessor
        return remover(&((*arv)->dir), temp->valor);
    }

    return true;
}


int main(){
  No* raiz=NULL;
  int opcao, num;
  do{
    printf("\n---- MENU ----\n");
    printf("1 - Inserir\n");
    printf("2 - Buscar\n");
    printf("3 - Remover\n");
    printf("4 - Tamanho\n");
    printf("5 - Imprimir Arvore\n");
    printf("6 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    switch(opcao){
    case 1:
        printf("Valor para inserir: ");
        scanf("%d", &num);
        if(insere(&raiz, num))
            printf("%d inserido com sucesso!\n", num);
        else
            printf("Valor ja exite na arvore.\n");
        break;
    case 2:
        printf("Valor para buscar: ");
        scanf("%d", &num);
        if(busca(raiz, num))
            printf("%d esta na arvore!\n", num);
        else
            printf("Valor nao esta na arvore.\n");
        break;
    case 3:
        printf("Valor a ser removido: ");
        scanf("%d", &num);
        if(remover(&raiz, num))
            printf("%d removido.\n", num);
        else
            printf("Valor nao esta na arvore\n");
        break;
    case 4:
        printf("Tamanho da arvore: %d nos\n", tamanho(raiz));
        break;
    case 5:
        imprimeGrafico(raiz, 0);
        printf("\n");
        break;
    case 6:
        printf("Saindo...\nFim do programa.\n");
        break;
    default:
        printf("ERRO: Opcao invalido\n");
    }
  }while(opcao!=6);
  return 0;
}
