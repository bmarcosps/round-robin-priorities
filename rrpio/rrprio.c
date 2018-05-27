/*
*  rrprio.c - Implementacao do algoritmo Round Robin com Prioridades
*
*  Autores: Bruno Marcos Pinheiro da Silva
			Pedro Henrique Gasparetto Lugão
			Warley Almeida Silva
*  Projeto: Trabalho Pratico I - Sistemas Operacionais
*  Organizacao: Universidade Federal de Juiz de Fora
*  Departamento: Dep. Ciencia da Computacao
*
*
*/

#include "rrprio.h"
#include <stdio.h>
#include <string.h>

//Nome unico do algoritmo. Deve ter 4 caracteres.
const char rrprioName[]="RRPr";

//=====Funcoes Auxiliares=====






//=====Funcoes da API=====

//Funcao chamada pela inicializacao do S.O. para a incializacao do escalonador
//conforme o algoritmo Round Robin com Prioridades
//Deve envolver a inicializacao de possiveis parametros gerais
//Deve envolver o registro do algoritmo junto ao escalonador
void rrpInitSchedInfo() {
	//...
    SchedInfo * rrp = malloc(sizeof(SchedInfo));
	for(unsigned int i = 0; i<4;i++)
		rrp->name[i] = rrprioName[i];
	rrp->initParamsFn = rrpInitSchedParams;
	rrp->scheduleFn = rrpSchedule;
	rrp->releaseParamsFn = rrpReleaseParams;
	schedRegisterScheduler(rrp);
}

//Inicializa os parametros de escalonamento de um processo p, chamada
//normalmente quando o processo e' associado ao slot de RRPrio
void rrpInitSchedParams(Process *p, void *params) {
	//...
	RRPrioParams * newParams = params;
	newParams->done = 0;
	processSetSchedParams(p,newParams);
}

//Retorna o proximo processo a obter a CPU, conforme o algortimo RRPrio
Process* rrpSchedule(Process *plist) {
	//...
	Process* p;
	int prio = 7;
	int found = 0;
	int chance = 0;
	while(prio>=0){
		p = plist;
		while(p!=NULL){
			RRPrioParams * params = processGetSchedParams(p);
			if(params->prio == prio && params->done == 0){
				if(processGetStatus(p) == PROC_READY || processGetStatus(p) == PROC_RUNNING)
					found = 1;
                params->done = 1;
                Process* next = processGetNext(p);
                while(next!=NULL){ //search for next process
                    RRPrioParams * nextParams = processGetSchedParams(next);
                    if(nextParams->prio == prio){
                        break;
                    }
                    next = processGetNext(next);
                }
                if(next == NULL){ //last process done -> undone all process with given priority
                    Process * undoneAll = plist;
                    while(undoneAll!=NULL){
                        RRPrioParams * undoneParams = processGetSchedParams(undoneAll);
                        if(undoneParams->prio == prio){
                            undoneParams->done = 0;
                        }
                        undoneAll = processGetNext(undoneAll);
                    }
                }
                if(found) break;
			}
			p = processGetNext(p);
		}
		if(found) break;
		if(!found && chance){
            prio--;
            chance = 0;
        }else{
            chance = 1;
        }
	}
	return p;
}

//Libera os parametros de escalonamento de um processo p, chamada
//normalmente quando o processo e' desassociado do slot de RRPrio
int rrpReleaseParams(Process *p) {
	//...
	free(processGetSchedParams(p));
	return 0;
}

//Modifica a prioridade de um processo para um novo valor
//Retorna o valor da prioridade anteriormente atribuida ao processo
int rrpSetPrio(Process *p, int prio) {
	//...
	RRPrioParams * params = processGetSchedParams(p);
	int oldPrio = params->prio;
	params->prio = prio;
	return oldPrio;
}
