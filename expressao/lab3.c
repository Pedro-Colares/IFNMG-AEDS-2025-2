#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100

typedef struct{
    int topo;
    int num[MAX];
}Num;

typedef struct{
    int topo;
    char operacao[MAX];
}Operacao;

void empilhar_num(Num *ap, int v){
    ap->num[++ap->topo] = v;
}

void empilhar_op(Operacao *ap, char c){
    ap->operacao[++ap->topo] = c;
}

int desempilhar_num(Num *ap){
    return ap->num[ap->topo--];
}

char desempilhar_op(Operacao *ap){
    return ap->operacao[ap->topo--];
}

char ver_topo(Operacao *ap){
    return ap->operacao[ap->topo];
}

int prioridade(char op){
    if(op == '*' || op == '/')
      return 2;
    if(op == '+' || op == '-')
      return 1;
    else
      return 0;
}

int aplica_op(int a, int b, char op){
    switch(op){
        case '+':
          return a+b;
          break;
        case '-':
          return a-b;
          break;
        case '*':
          return a*b;
          break;
        case '/':
          return a/b;
          break;
        default:
          printf("Erro: operacao invalida.\n");
          exit(1);
    }  
}

int main(){
    char expressao[200];
    char *token;
    Num numeros;
    Operacao operacoes;

    numeros.topo = -1;
    operacoes.topo = -1;

    fgets(expressao, sizeof(expressao), stdin);
    token = strtok(expressao, " \n");
    while(token!=NULL){
        if(token[0]>='0' && token[0]<='9'){
            empilhar_num(&numeros, atoi(token));
        }else{
            char op = token[0];
            while(operacoes.topo>=0 && prioridade(ver_topo(&operacoes))>=prioridade(op)){
                int b = desempilhar_num(&numeros);
                int a = desempilhar_num(&numeros);
                char oper = desempilhar_op(&operacoes);
                empilhar_num(&numeros, aplica_op(a, b, oper));
            }
            empilhar_op(&operacoes, op);
        }
        token = strtok(NULL, " \n"); 
    }
    while(operacoes.topo>=0){
        int b = desempilhar_num(&numeros);
        int a = desempilhar_num(&numeros);
        char oper = desempilhar_op(&operacoes);
        empilhar_num(&numeros, aplica_op(a, b, oper)); 
    }
    printf("%d\n", desempilhar_num(&numeros));
    return 0;
}
