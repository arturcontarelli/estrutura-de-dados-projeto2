#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct Venda {
    int id;
    char cliente[51];
    char vendedor[51];
    char matricula[5];
    Data dataTransacao;
    float valorTransacao;
} Venda;

typedef struct no_Arv{
    Venda venda;
    struct no_Arv *esq;
    struct no_Arv *dir;
} NoArv;

typedef struct Arvore_Binaria{
    NoArv *raiz;
} Arv;

Arv* CriaArvore();
int VaziaArvore(Arv *A);
NoArv* CriaNo(Venda v);
int InserirVenda(Arv *A, Venda v);
int BuscarVenda(Arv *A, int id);
Arv *RemoverVendaPorID(Arv *A, int id);
void LiberarArvore(Arv *A);
void ImprimirArvore(Arv *A, int procedimento);
void ImprimirVenda(Venda v);
void imprimirVendaDeVendedor(Venda v);
void auxPreOrder(NoArv *no);
void auxInOrder(NoArv *no);
void auxPosOrder(NoArv *no);
void auxInOrderDecrescente(NoArv *no);
int auxBuscar(NoArv* no, int id);
NoArv* remover_aux(NoArv* no, int id);
NoArv* EncontrarMinimo(NoArv* no);
NoArv* EncontrarMaximo(NoArv* no);
void auxLiberar(NoArv* no);
int QuantidadeVendas(NoArv* pai);
float SomaVendas (NoArv* pai);
int BuscarVendasPorNome(NoArv* no, char vendedor[51]);
int BuscarVendasPorMatricula(NoArv* no, char matricula[5]);
void strParaMinusculo(char *str);

Arv* CriaArvore() {
    Arv* a = (Arv*) malloc(sizeof(Arv));
    a->raiz = NULL;
    return a;
}

int VaziaArvore(Arv *A) {
    if (A->raiz == NULL) {
        return 1;
    }
    return 0;
}

NoArv* CriaNo(Venda v) {
    NoArv* novo = (NoArv*) malloc(sizeof(NoArv));
    if (novo != NULL) {
        novo->venda = v;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

void ImprimirVenda(Venda v) {
    printf("ID: %-5d | Vendedor: %-20s | Matrícula: %s | Cliente: %s | Data: %02d/%02d/%04d | Valor: R$ %.2f\n",
           v.id, v.vendedor, v.matricula, v.cliente, v.dataTransacao.dia, v.dataTransacao.mes, v.dataTransacao.ano, v.valorTransacao);
    printf("----------------------------------------\n");
}

void imprimirVendaDeVendedor(Venda v) {
    printf("ID: %-5d | Cliente: %-20s | Data: %02d/%02d/%04d | Valor: R$ %.2f\n",
           v.id, v.cliente, v.dataTransacao.dia, v.dataTransacao.mes, v.dataTransacao.ano,  v.valorTransacao);
    printf("----------------------------------------\n");
}

void auxPreOrder(NoArv *pai) {
    ImprimirVenda(pai->venda);
    if (pai->dir != NULL) { auxPreOrder(pai->dir); }
    if (pai->esq != NULL) { auxPreOrder(pai->esq); }
}

void auxInOrder(NoArv *pai) {
    if (pai->dir != NULL) { auxPreOrder(pai->dir); }
    ImprimirVenda(pai->venda);
    if (pai->esq != NULL) { auxPreOrder(pai->esq); }
}

void auxPosOrder(NoArv *pai) {
    if (pai->dir != NULL) { auxPreOrder(pai->dir); }
    if (pai->esq != NULL) { auxPreOrder(pai->esq); }
    ImprimirVenda(pai->venda);
}

void auxInOrderDecrescente(NoArv *pai) {
    if (pai->esq != NULL) { auxInOrderDecrescente(pai->esq); }
    ImprimirVenda(pai->venda);
    if (pai->dir != NULL) { auxInOrderDecrescente(pai->dir); }
}

void ImprimirArvore(Arv *A, int procedimento){
    if (VaziaArvore(A)) {
        printf("Arvore vazia.\n");
    } else {
        switch(procedimento) {
        case 1:
            printf("Impressão Pre-Ordem:\n");
            auxPreOrder(A->raiz);
            break;
        case 2:
            printf("Impressão Em Ordem Decrescente por ID:\n");
            auxInOrder(A->raiz);
            break;
        case 3:
            printf("Impressão Pos-Ordem:\n");
            auxPosOrder(A->raiz);
            break;
        case 4:
            printf("Impressão Em Ordem Crescente por ID:\n");
            auxInOrderDecrescente(A->raiz);
            break;
        default:
            printf("Procedimento inválido. Use: 1=Pre-ordem, 2=Em ordem, 3=Pos-ordem\n");
        }
    }
    printf("===========================\n\n");
}

int BuscarVenda(Arv *A, int id) {
    if (VaziaArvore(A)) {
        return 0;
    }
    return auxBuscar(A->raiz, id);
}

int auxBuscar(NoArv* pai, int id) {
    if (pai->venda.id == id) {
        return 1;
    }

    if (id < pai->venda.id) {
        if (pai->esq != NULL) {
            return auxBuscar(pai->esq, id);
        }
        return 0;
    }
    if (id > pai->venda.id) {
        if (pai->dir != NULL) {
            return auxBuscar(pai->dir, id);
        }
        return 0;
    }

}

void strParaMinusculo(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}

int BuscarVendasPorNome(NoArv* no, char vendedor[51]) {
    if (no == NULL) return 0;

    char nomeNo[51];
    char nomeBuscado[51];

    strcpy(nomeNo, no->venda.vendedor);
    strcpy(nomeBuscado, vendedor);

    strParaMinusculo(nomeNo);
    strParaMinusculo(nomeBuscado);

    int count = (strcmp(nomeNo, nomeBuscado) == 0) ? 1 : 0;

    return count +
           BuscarVendasPorNome(no->dir, vendedor) +
           BuscarVendasPorNome(no->esq, vendedor);
}

int BuscarVendasPorMatricula(NoArv* no, char matricula[5]) {
    if (no == NULL) return 0;

    int count = (strcmp(no->venda.matricula, matricula) == 0) ? 1 : 0;
    return count + BuscarVendasPorMatricula(no->dir, matricula) +
                   BuscarVendasPorMatricula(no->esq, matricula);
}

int InserirVenda(Arv *A, Venda venda) {
    NoArv* novo = CriaNo(venda);
    if (VaziaArvore(A)) {
        A->raiz = novo;
        return 1;
    } else {
        NoArv* Pai = A->raiz;
        while (1) {
            if (venda.id > Pai->venda.id) {
                if (Pai->dir != NULL) {
                    Pai = Pai->dir;
                } else {
                    Pai->dir = novo;
                    return 1;
                }
            } else {
                if (Pai->esq != NULL) {
                    Pai = Pai->esq;
                } else {
                    Pai->esq = novo;
                    return 1;
                }
            }
        }
    }
    return 0;
}

Arv *RemoverVendaPorID(Arv *A, int id){
    NoArv *aux= A->raiz;
    if(aux->venda.id == id && aux->dir == NULL && aux->esq == NULL){
        free(aux);
         A->raiz = NULL;
        return A;
    }
    A->raiz = remover_aux(A->raiz,id);
    return A;
}

NoArv *remover_aux(NoArv *pai, int id){
    if(pai==NULL){
        printf("\n \n Venda não encontrada no sistema \n \n");
    } else{
        if(id > pai->venda.id){
            pai->dir = remover_aux(pai->dir,id);
        } else{
            if(id < pai->venda.id){
                pai->esq = remover_aux(pai->esq,id);
            } else{
                if(pai->dir==NULL && pai->esq==NULL){
                    free(pai); pai=NULL;
                } else{
                    if (pai->esq==NULL){
                        NoArv *aux=pai; pai = pai->dir; free(aux);
                    } else{
                        if((pai->dir==NULL)){
                            NoArv *aux=pai; pai = pai->esq; free(aux);
                        } else{
                            NoArv *aux;
                            aux = pai->esq;
                            while (aux->dir !=NULL){
                                aux=aux->dir;
                            }
                            pai->venda = aux->venda;
                            pai->esq = remover_aux(pai->esq, aux ->venda.id);
                        }
                    }
                }
            }
        }
    }
    return pai;
}

NoArv* EncontrarMaximo(NoArv* no) {
    while (no->dir != NULL) {
        no = no->dir;
    }
    return no;
}

void LiberarArvore(Arv *A) {
    if (!VaziaArvore(A)) {
        auxLiberar(A->raiz);
        free(A);
    }
}

void auxLiberar(NoArv* no) {
    if(no -> esq != NULL) auxLiberar(no->esq);
    if(no -> dir != NULL) auxLiberar(no->dir);
    free(no);
}

int QuantidadeVendas(NoArv* pai) {
    if (pai == NULL)
        return 0;

    return 1 + QuantidadeVendas(pai->esq) + QuantidadeVendas(pai->dir);
}

float SomaVendas (NoArv* pai) {
    if(pai == NULL) return 0.0;
    float S = pai->venda.valorTransacao;
    if (pai->dir != NULL) {
        S += SomaVendas(pai->dir);
    }
    if (pai->esq != NULL) {
        S += SomaVendas(pai->esq);
    }
    return S;
}

#endif
