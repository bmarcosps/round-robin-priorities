/*
*  rrprio.h - Header da API algoritmo Round Robin com Prioridades
*
*  Autor: Marcelo Moreno
*  Projeto: Trabalho Pratico I - Sistemas Operacionais
*  Organizacao: Universidade Federal de Juiz de Fora
*  Departamento: Dep. Ciencia da Computacao
*
*  => TENTE MODIFICAR APENAS A STRUCT rrprio_params <=
*
*/

#ifndef RRPRIO_H
#define RRPRIO_H

#include "sched.h"

typedef struct rrprio_params {
    int prio;
    int done;
        //...
} RRPrioParams;

//Funcao chamada pela inicializacao do S.O. para a incializacao do escalonador
//conforme o algoritmo Round Robin com Prioridades
//Deve envolver a inicializacao de possiveis parametros gerais
//Deve envolver o registro do algoritmo junto ao escalonador
void rrpInitSchedInfo(void);

//Inicializa os parametros de escalonamento de um processo p, chamada
//normalmente quando o processo e' associado ao slot de RRPrio
void rrpInitSchedParams(Process *p, void *params);

//Retorna o proximo processo a obter a CPU, conforme o algortimo RRPrio
Process* rrpSchedule(Process *plist);

//Libera os parametros de escalonamento de um processo p, chamada
//normalmente quando o processo e' desassociado do slot de RRPrio
int rrpReleaseParams(Process *p);

//Modifica a prioridade de um processo para um novo valor
//Retorna o valor da prioridade anteriormente atribuida ao processo
int rrpSetPrio(Process *p, int prio);

#endif
