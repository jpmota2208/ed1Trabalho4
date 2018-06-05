//Alunos: Fabiana Luiza Vasconcelos Pfeilsticker Ribas  16/0005736
//        Joao Pedro Mota Jardim                        16/0031982
//        Marcelo Araujo dos Santos                     16/0035481

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define UnTempo 5


typedef struct voo{
  char identificacao[7];
  char tipo;
  int combA;

  struct voo *prox;
} Voo;

typedef struct fila{
  Voo *primeiro,*ultimo;
} Fila;

typedef struct pista{
  int numero;
  Voo *ocupado;
  int tempo;
} Pista;

//#include "./funcoes/funcoes.h"
//int pegaHoraLocal()
void geraVoos(int *nVoos,int *nAproximacoes,int *nDecolagens);
void carregaFila(Fila *fila,int nVoos,int nAproximacoes,int nDecolagens,char codigos[][7]);
void embaralhar(Voo *vetor,int nVoos);
void insereNaFila(Fila *fila,Voo *voo);
void rolaEvento(Fila *fila, Pista pistas[3],int *desvio);
void decresceCombustivel(Fila *fila);
void verificaEmergencia(Fila *fila,int *desvio);

int main(){
  Fila fila;
  Voo *aux;
  Pista pistas[3];
  int i,hora = 5,min = 0,minInicio,horaInicio,cont = 0,desvio = 0;

  char codigos[64][7] = {"VG3001","JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009",
                         "AZ1008","AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880",
                         "AL0012","TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002",
                         "AZ1002","AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403",
                         "AZ1001","LN7003", "AZ1004", "TG1504", "AZ1005", "TG1502", "GL7601",
                         "TT4500", "RL7801", "JJ4410", "GL7607", "AL0029", "VV3390","VV3392",
                         "GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920","AZ1065",
                         "LF0978", "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434","TG1510",
                         "TT1020", "AZ1098", "BA2312", "VG3030", "BA2304", "KL5609","KL5610", "KL5611"};
  int nVoos,nAproximacoes,nDecolagens;
  fila.primeiro = NULL;
  fila.ultimo = NULL;
  geraVoos(&nVoos,&nAproximacoes,&nDecolagens);
  carregaFila(&fila,nVoos,nAproximacoes,nDecolagens,codigos);
  for(i = 0; i < 3; i++){
    pistas[i].numero = i+1;
    pistas[i].ocupado = NULL;
    pistas[i].tempo = 0;
  }
  puts("---------------------------------------------------------------------------------");
  puts("Aeroporto Internacional de Brasília");
  printf("Hora Inicial: %dh",hora);
  if(min < 10)
    printf("0%d\n",min);
  else
    printf("%d\n",min);
  printf("Fila de Pedidos: ");
  for(aux = fila.primeiro;aux != NULL;aux = aux->prox){
    printf("[%s – %c – %d] ; ",aux->identificacao,aux->tipo,aux->combA);
  }
  printf("\n\nNVoos: %d\n",nVoos);
  printf("Naproximações: %d \n",nAproximacoes);
  printf("NDecolagens: %d\n",nDecolagens);
  puts("---------------------------------------------------------------------------------");
  printf("Listagem de eventos:\n\n");
  rolaEvento(&fila,pistas,&desvio);
  do{
    for(i = 0; i < 3; i++){
      if(pistas[i].tempo == 0){
        printf("Código do voo: %s \n",pistas[i].ocupado->identificacao);
        printf("Status: ");
        if(pistas[i].ocupado->tipo == 'D'){
          printf("aeronave decolou\n");
          horaInicio = hora;
          minInicio = min - 2*UnTempo;
          if(minInicio < 0){
            minInicio = minInicio + 60;
            horaInicio = horaInicio - 1;
          }
          if(horaInicio < 0)
            horaInicio = horaInicio + 24;
        }
        else{
          printf("aeronave pousou\n");
          horaInicio = hora;
          minInicio = min - 3*UnTempo;
          if(minInicio < 0){
            minInicio = minInicio + 60;
            horaInicio = horaInicio - 1;
          }
          if(horaInicio < 0)
            horaInicio = horaInicio + 24;
        }
        printf("Horário do início do procedimento: %dh",horaInicio);
        if(minInicio < 10)
          printf("0%d\n",minInicio);
        else
          printf("%d\n",minInicio);
        printf("Número da pista: %d\n\n",pistas[i].numero);
        free(pistas[i].ocupado);
      }
      //printf("Tempo da pista %d: %d min\n",pistas[i].numero,pistas[i].tempo);
    }
    cont++;
    if(cont > 9){
      decresceCombustivel(&fila);
      cont = 0;
      //printf("RESETOU O CONTADOR E REDUZIU 1 COMBUSTIVEL\n");
    }
    verificaEmergencia(&fila,&desvio);
    //printf("\n\npassou o tempo CONTADOR = %d\n\n",cont);
    min = min + UnTempo;
    if(min >= 60){
      hora++;
      min = min - 60;
    }
    if(hora >= 24)
      hora = hora - 24;
    rolaEvento(&fila,pistas,&desvio);
    for(i = 0; i < 3; i++)
      pistas[i].tempo = pistas[i].tempo - 1*UnTempo;
  }while(fila.primeiro != NULL || (pistas[0].tempo != 0 && pistas[1].tempo != 0 && pistas[2].tempo != 0));

  //for(aux = fila.primeiro;aux != NULL;aux = aux->prox){
  /*aux = fila.primeiro;
  for(i = 0; i < nVoos;i++){
      printf("Código do voo: %s \n",aux->identificacao);
      printf("Status: ");
      if(aux->tipo == 'D')
        printf("aeronave decolou\n");
      else{
        printf("aeronave pousou\n");
        printf("Nivel de combustivel: %d \n",aux->combA);
      }
      printf("Horário do início do procedimento: %dh",hora);
      if(min < 10)
        printf("0%d\n",min);
      else
        printf("%d\n",min);
      aux = aux->prox;
      min = min + UnTempo;
      if(min >= 60){
        hora++;
        min = min - 60;
      }
      if(hora >= 24)
        hora = hora - 24;
    printf("Número da pista: %d\n\n\n",pistas[i].numero);
  }*/
  return 0;
}

void geraVoos(int *nVoos,int *nAproximacoes,int *nDecolagens){
  srand(time(NULL));
  *nVoos = rand() % 64;
  if (*nVoos < 20)
    *nVoos = *nVoos + 20;
  *nAproximacoes = rand() % (*nVoos-10);
  if (*nAproximacoes < 10)
    *nAproximacoes = 10;
  *nDecolagens = *nVoos - *nAproximacoes;
}

/*int pegaHoraLocal()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  //printf ( "Data atual do sistema é: %s", asctime (timeinfo) );
}*/

void carregaFila(Fila *fila,int nVoos,int nAproximacoes,int nDecolagens,char codigos[][7]){
  Voo voo[nVoos];
  int i;
  for(i = 0; i < nAproximacoes;i++){
    strcpy(voo[i].identificacao,codigos[i]);
    voo[i].tipo = 'A';
    voo[i].combA = rand() % 12;
    voo[i].prox = NULL;
  }
  for(i = nAproximacoes; i < nAproximacoes+nDecolagens;i++){
    strcpy(voo[i].identificacao,codigos[i]);
    voo[i].tipo = 'D';
    voo[i].combA = -1;
    voo[i].prox = NULL;
  }
  embaralhar(voo,nVoos);
  for(i = 0; i < nVoos;i++){
    Voo *novoVoo = (Voo*)malloc(sizeof(Voo));
    strcpy(novoVoo->identificacao,voo[i].identificacao);
    novoVoo->tipo = voo[i].tipo;
    novoVoo->combA = voo[i].combA;
    novoVoo->prox = NULL;
    insereNaFila(fila,novoVoo);
  }
}
void embaralhar(Voo *vetor,int nVoos) {
  int i, aleat;
  Voo aux;

  srand(time(NULL));
  // embaralha vetor
  for(i=0;i <nVoos; i++){
    aleat = rand() % nVoos;
    aux = vetor[i];
    vetor[i] = vetor[aleat];
    vetor[aleat] = aux;
  }
}
void insereNaFila(Fila *fila,Voo *voo){
  if (fila->primeiro == NULL){
    fila->primeiro = voo;
    fila->ultimo = voo;
    voo->prox = NULL;
  }
  else{
    fila->ultimo->prox = voo;
    fila->ultimo = voo;
  }
}

void rolaEvento(Fila *fila, Pista pistas[3], int *desvio){
  Voo *aux,*ant = NULL;
  int inseriuNoInicio = 0;
  for(aux = fila->primeiro; aux != NULL; aux = aux->prox){
    if(aux->tipo == 'D'){
      if(pistas[0].tempo == 0){
        pistas[0].ocupado = aux;
        pistas[0].tempo = 2*UnTempo;
        //Se o anterior for nulo, significa q o aux e o primeiro elemento
        if(ant == NULL){
          //printf("Primeiro da fila 1 - decolagem aviao %s\n", pistas[0].ocupado->identificacao);
          fila->primeiro = aux->prox;
          inseriuNoInicio = 1;
        }
        else{
          //printf("outro cara 1 - decolagem aviao %s\n", pistas[0].ocupado->identificacao);
          ant->prox = aux->prox;
          inseriuNoInicio = 0;
        }
      }
      else if(pistas[1].tempo == 0){
        pistas[1].ocupado = aux;
        pistas[1].tempo = 2*UnTempo;
        if(ant == NULL){
          //printf("Primeiro da fila 2 - decolagem aviao %s\n", pistas[1].ocupado->identificacao);
          fila->primeiro = aux->prox;
          inseriuNoInicio = 1;
        }
        else{
          //printf("outro cara 2 - decolagem aviao %s\n", pistas[1].ocupado->identificacao);
          ant->prox = aux->prox;
          inseriuNoInicio = 0;
        }
      }
      else if(pistas[2].tempo == 0){
        pistas[2].ocupado = aux;
        pistas[2].tempo = 2*UnTempo;
        if(ant == NULL){
          //printf("Primeiro da fila 3 - decolagem aviao %s\n", pistas[2].ocupado->identificacao);
          fila->primeiro = aux->prox;
          inseriuNoInicio = 1;
        }
        else{
          //printf("outro cara 3 - decolagem aviao %s\n", pistas[2].ocupado->identificacao);
          ant->prox = aux->prox;
          inseriuNoInicio = 0;
        }
      }
    }
    else{// Voo tipo A
      if(pistas[0].tempo == 0){
        pistas[0].ocupado = aux;
        pistas[0].tempo = 3*UnTempo;
        if(ant == NULL){
          //printf("Primeiro da fila 1 - aterrissagem aviao %s\n", pistas[0].ocupado->identificacao);
          fila->primeiro = aux->prox;
          inseriuNoInicio = 1;
        }
        else{
          //printf("outro cara 1 - aterrissagem aviao %s\n", pistas[0].ocupado->identificacao);
          ant->prox = aux->prox;
          inseriuNoInicio = 0;
        }
      }
      else if(pistas[1].tempo == 0){
        pistas[1].ocupado = aux;
        pistas[1].tempo = 3*UnTempo;
        if(ant == NULL){
          //printf("Primeiro da fila 2 - aterrissagem aviao %s\n", pistas[1].ocupado->identificacao);
          fila->primeiro = aux->prox;
          inseriuNoInicio = 1;
        }
        else{
          //printf("outro cara 2 - aterrissagem aviao %s\n", pistas[1].ocupado->identificacao);
          ant->prox = aux->prox;
          inseriuNoInicio = 0;
        }
      }
      else if(*desvio == 1){
        if(ant == NULL){// se for o primeiro
          if(pistas[2].tempo == 0){
            pistas[2].ocupado = aux;
            pistas[2].tempo = 3*UnTempo;
            //printf("Primeiro da fila 3 - aterrissagem aviao EMERGENCIAL %s\n", pistas[1].ocupado->identificacao);
            fila->primeiro = aux->prox;
            inseriuNoInicio = 1;
          }
          else{
            printf("ALERTA CRÍTICO, AERONAVE %s IRÁ CAIR\n",aux->identificacao);
            fila->primeiro = aux->prox;
            inseriuNoInicio = 1;
            free(aux);
          }
        }
      }
    }
    if(inseriuNoInicio == 1)
      ant = NULL;
    else
      ant = aux;
  }
}
void decresceCombustivel(Fila *fila){
  Voo *aux;
  for(aux = fila->primeiro; aux != NULL; aux = aux->prox){
    if(aux->tipo == 'P')
      aux->combA = aux->combA - 1;
  }
}

void verificaEmergencia(Fila *fila,int *desvio){
  Voo *aux,*ant = NULL;
  int nEmergencias = 0;
  for(aux = fila->primeiro; aux != NULL; aux = aux->prox){
    if(aux->combA == '0'){
      if(aux != fila->primeiro){ // se ele n e o primeiro, ele se torna o primeiro
        ant->prox = aux->prox;
        aux->prox = fila->primeiro;
        fila->primeiro = aux;
      }
      nEmergencias++;
    }
    ant = aux;
  }
  if(nEmergencias >= 3){
    printf("ALERTA GERAL DE DESVIO DE AERONAVE\n");
    *desvio = 1;
  }
}
