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
    int id;                    // Chave primária (1000-9999)
    char cliente[51];          // Nome do cliente
    char vendedor[51];         // Nome do vendedor
    char matricula[5];         // Matrícula (V + 3 dígitos)
    Data dataTransacao;        // Data da venda
    float valorTransacao;      // Valor da venda
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
NoArv* BuscarVenda(Arv *A, int id);
int RemoverVenda(Arv *A, int id);
void LiberarArvore(Arv *A);

void ImprimirArvore(Arv *A, int procedimento);
void ImprimirVenda(Venda v);
void imprimirVendaDeVendedor(Venda v);
void auxPreOrder(NoArv *no);
void auxInOrder(NoArv *no);
void auxPosOrder(NoArv *no);
void auxInOrderDecrescente(NoArv *no);

NoArv* auxBuscar(NoArv* no, int id);
NoArv* auxInserir(NoArv* no, Venda v, int* sucesso);
NoArv* auxRemover(NoArv* no, int id, int* removido);
NoArv* EncontrarMinimo(NoArv* no);
NoArv* EncontrarMaximo(NoArv* no);
void auxLiberar(NoArv* no);
int qtdVendas(NoArv* pai);
float somaVendas (NoArv* pai);
int BuscarVendasPorNome(NoArv* no, char vendedor[51]);
int BuscarVendasPorMatricula(NoArv* no, char matricula[5]);

Arv* CriaArvore() {
    Arv* a = (Arv*) malloc(sizeof(Arv));
    if (a != NULL) {
        a->raiz = NULL;
    }
    return a;
}

int VaziaArvore(Arv *A) {
    return (A == NULL || A->raiz == NULL);
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

void auxPreOrder(NoArv *no) {
    ImprimirVenda(no->venda);
    if(no -> esq != NULL) auxPreOrder(no->esq);
    if(no -> dir != NULL) auxPreOrder(no->dir);
}

void auxInOrder(NoArv *no) {
    if(no -> esq != NULL) auxInOrder(no->esq);
    ImprimirVenda(no->venda);
    if(no -> dir != NULL) auxInOrder(no->dir);
}

void auxPosOrder(NoArv *no) {
    if(no -> esq != NULL) auxPosOrder(no->esq);
    if(no -> dir != NULL) auxPosOrder(no->dir);
    ImprimirVenda(no->venda);
}

void auxInOrderDecrescente(NoArv *no) {
    if(no -> dir != NULL) auxInOrderDecrescente(no->dir);
    ImprimirVenda(no->venda);
    if(no -> esq != NULL) auxInOrderDecrescente(no->esq);
}

void ImprimirArvore(Arv *A, int procedimento){
    if (VaziaArvore(A)) {
        printf("Arvore vazia.\n");
    } else{
        switch(procedimento){
            case 1:
                printf("Impressão Pre-Ordem:\n");
                auxPreOrder(A->raiz);
                break;
            case 2:
                printf("Impressão Em Ordem (Crescente por ID):\n");
                auxInOrder(A->raiz);
                break;
            case 3:
                printf("Impressão Pos-Ordem:\n");
                auxPosOrder(A->raiz);
                break;
            case 4:
                printf("Impressão Em Ordem Decrescente por ID:\n");
                auxInOrderDecrescente(A->raiz);
                break;
            default:
                printf("Procedimento inválido. Use: 1=Pre-ordem, 2=Em ordem, 3=Pos-ordem\n");
        }
        printf("===========================\n\n");
    }
}

NoArv* BuscarVenda(Arv *A, int id) {
    if (VaziaArvore(A)) {
        return NULL;
    }
    return auxBuscar(A->raiz, id);
}

NoArv* auxBuscar(NoArv* no, int id) {
    if (no == NULL || no->venda.id == id) {
        return no;
    }

    if (id < no->venda.id) {
        return auxBuscar(no->esq, id);
    } else {
        return auxBuscar(no->dir, id);
    }
}

int BuscarVendasPorNome(NoArv* no, char vendedor[51]) {
    if (no == NULL) return 0;

    int count = (strcmp(no->venda.vendedor, vendedor) == 0) ? 1 : 0;
    return count + BuscarVendasPorNome(no->esq, vendedor) +
                   BuscarVendasPorNome(no->dir, vendedor);
}

int BuscarVendasPorMatricula(NoArv* no, char matricula[5]) {
    if (no == NULL) return 0;

    int count = (strcmp(no->venda.matricula, matricula) == 0) ? 1 : 0;
    return count + BuscarVendasPorMatricula(no->esq, matricula) +
                   BuscarVendasPorMatricula(no->dir, matricula);
}

int InserirVenda(Arv *A, Venda venda) {
    if (A == NULL) {
        return 0;
    }

    int sucesso = 0;
    A->raiz = auxInserir(A->raiz, venda, &sucesso);
    return sucesso;
}

NoArv* auxInserir(NoArv* no, Venda v, int* sucesso) {
    if (no == NULL) {
        *sucesso = 1;
        return CriaNo(v);
    }

    if (v.id < no->venda.id) {
        no->esq = auxInserir(no->esq, v, sucesso);
    } else if (v.id > no->venda.id) {
        no->dir = auxInserir(no->dir, v, sucesso);
    } else {
        *sucesso = 0;
    }

    return no;
}

int RemoverVenda(Arv *A, int id) {
    if (VaziaArvore(A)) {
        return 0;
    }

    int removido = 0;
    A->raiz = auxRemover(A->raiz, id, &removido);
    return removido;
}

NoArv* EncontrarMaximo(NoArv* no) {
    while (no->dir != NULL) {
        no = no->dir;
    }
    return no;
}


NoArv* auxRemover(NoArv* no, int id, int* removido) {
    if (no == NULL) {
        *removido = 0;
        return no;
    }

    if (id < no->venda.id) {
        no->esq = auxRemover(no->esq, id, removido);
    } else if (id > no->venda.id) {
        no->dir = auxRemover(no->dir, id, removido);
    } else {
        *removido = 1;

        if (no->esq == NULL) {
            NoArv* temp = no->dir;
            free(no);
            return temp;
        } else if (no->dir == NULL) {
            NoArv* temp = no->esq;
            free(no);
            return temp;
        }

        NoArv* temp = EncontrarMaximo(no->esq);
        no->venda = temp->venda;
        no->esq = auxRemover(no->esq, temp->venda.id, removido);
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

int qntVendas(NoArv* pai) {
    if (pai == NULL)
        return 0;

    return 1 + qntVendas(pai->esq) + qntVendas(pai->dir);
}


float somaVendas(NoArv* pai) {
    float S = pai->venda.valorTransacao;
    if (pai->dir != NULL) {
        S += somaVendas(pai->dir);
    }
    if (pai->esq != NULL) {
        S += somaVendas(pai->esq);
    }
    return S;
}

int buscarVendas(NoArv* pai, char *vendedor) {
    if (pai == NULL)
        return 0;

    int qnt = 0;

    if (strcmp(pai->venda.vendedor, vendedor) == 0) { qnt++; }

    qnt += buscarVendas(pai->esq, vendedor);
    qnt += buscarVendas(pai->dir, vendedor);

    return qnt;
}

#endif
