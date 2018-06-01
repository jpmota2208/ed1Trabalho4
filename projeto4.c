//Alunos: Fabiana Luiza Vasconcelos Pfeilsticker Ribas
//        Joao Pedro Mota Jardim
//        Marcelo Araujo dos Santos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct voo{
  char identificacao[7];
  char tipo;
  int aproximacao;

  struct voo *ant;
  struct voo *prox;
} Voo;

//#include "./funcoes/funcoes.h"

void geraVoos(int *qtdVoosTotal,int *qtdVoosA,int *qtdVoosD){
  srand(time(NULL));
  *qtdVoosTotal = rand() % 64;
  if (*qtdVoosTotal < 20)
    *qtdVoosTotal = *qtdVoosTotal + 20;
  *qtdVoosA = rand() % (*qtdVoosTotal-10);
  if (*qtdVoosA < 10)
    *qtdVoosA = 10;
  *qtdVoosD = *qtdVoosTotal - *qtdVoosA;
  printf("Total = %d, Aterrissagem = %d, Decolagem = %d\n",*qtdVoosTotal,*qtdVoosA,*qtdVoosD);
}
int main(){
  int qtdVoosTotal,qtdVoosA,qtdVoosD;
  geraVoos(&qtdVoosTotal,&qtdVoosA,&qtdVoosD);
  
  return 0;
}
