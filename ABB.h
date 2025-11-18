#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Biblioteca de Árvores Binárias de Busca para Sistema de Vendas
Funcionalidades:
    - Buscar por ID
    - Inserir venda
    - Remover venda
    - Liberar memória
    - Imprimir árvore
*/

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

// ========== PROTÓTIPOS DAS FUNÇÕES ==========

// Funções principais
Arv* CriaArvore();
int VaziaArvore(Arv *A);
NoArv* CriaNo(Venda v);
int InserirVenda(Arv *A, Venda v);
NoArv* BuscarVenda(Arv *A, int id);
int RemoverVenda(Arv *A, int id);
void LiberarArvore(Arv *A);

// Funções de impressão
void ImprimirArvore(Arv *A, int procedimento);
void ImprimirVenda(Venda v);     
void imprimirVendaDeVendedor(Venda v);               
void auxPreOrder(NoArv *no);
void auxInOrder(NoArv *no);
void auxPosOrder(NoArv *no);
void auxInOrderDecrescente(NoArv *no);

// Funções auxiliares
NoArv* auxBuscar(NoArv* no, int id);
NoArv* auxInserir(NoArv* no, Venda v, int* sucesso);
NoArv* auxRemover(NoArv* no, int id, int* removido);
NoArv* EncontrarMinimo(NoArv* no);
NoArv* EncontrarMaximo(NoArv* no);
void auxLiberar(NoArv* no);

// ========== IMPLEMENTAÇÕES ==========

// 1. CRIAR ÁRVORE
Arv* CriaArvore() {
    Arv* a = (Arv*) malloc(sizeof(Arv));
    if (a != NULL) {
        a->raiz = NULL;                        
    }
    return a;
}

// 2. VERIFICA SE A ÁRVORE ESTÁ VAZIA
int VaziaArvore(Arv *A) {
    return (A == NULL || A->raiz == NULL);     
}

// 3. CRIAR NÓ
NoArv* CriaNo(Venda v) {                       
    NoArv* novo = (NoArv*) malloc(sizeof(NoArv));
    if (novo != NULL) {
        novo->venda = v;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

// 4.1 IMPRIMIR VENDA
void ImprimirVenda(Venda v) {                  
    printf("ID: %-5d | Vendedor: %-20s | Matrícula: %s | Cliente: %s | Data: %02d/%02d/%04d | Valor: R$ %.2f\n", 
           v.id, v.vendedor, v.matricula, v.cliente, v.dataTransacao.dia, v.dataTransacao.mes, v.dataTransacao.ano, v.valorTransacao);
    printf("----------------------------------------\n");
}

// 4.2 IMPRIMIR VENDA DE DETERMINADO VENDEDOR
void imprimirVendaDeVendedor(Venda v) {
    printf("ID: %-5d | Cliente: %-20s | Data: %02d/%02d/%04d | Valor: R$ %.2f\n", 
           v.id, v.cliente, v.dataTransacao.dia, v.dataTransacao.mes, v.dataTransacao.ano,  v.valorTransacao);
    printf("----------------------------------------\n");
}

// 5. FUNÇÕES DE IMPRESSÃO AUXILIAR
void auxPreOrder(NoArv *no) {
    if (no != NULL) {
        ImprimirVenda(no->venda);
        auxPreOrder(no->esq);
        auxPreOrder(no->dir);
    }
}

void auxInOrder(NoArv *no) {
    if (no != NULL) {
        auxInOrder(no->esq);
        ImprimirVenda(no->venda);
        auxInOrder(no->dir);
    }
}

void auxPosOrder(NoArv *no) {
    if (no != NULL) {
        auxPosOrder(no->esq);
        auxPosOrder(no->dir);
        ImprimirVenda(no->venda);
    }
}

void auxInOrderDecrescente(NoArv *no) {
    if (no != NULL) {
        auxInOrderDecrescente(no->dir);
        ImprimirVenda(no->venda);
        auxInOrderDecrescente(no->esq);
    }
}

// 6. IMPRIMIR ÁRVORE
void ImprimirArvore(Arv *A, int procedimento){
    // CORREÇÃO: Verificar se árvore está vazia primeiro
    if (VaziaArvore(A)) {
        printf("Arvore vazia.\n");
        return;
    }

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
            return;
    }
    printf("===========================\n\n");
}

// 7. BUSCAR UM ELEMENTO NA ÁRVORE POR VALOR (ID)
NoArv* BuscarVenda(Arv *A, int id) {           
    if (VaziaArvore(A)) {
        return NULL;
    }
    return auxBuscar(A->raiz, id);             
}

// Auxiliar - Busca recursiva
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

// 8. INSERIR
int InserirVenda(Arv *A, Venda venda) {       
    if (A == NULL) {
        return 0; // Falha: árvore não inicializada
    }
    
    int sucesso = 0;
    A->raiz = auxInserir(A->raiz, venda, &sucesso);  
    return sucesso;
}

// Auxiliar - Inserção recursiva
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
        // ID já existe
        *sucesso = 0;
    }
    
    return no;
}

// 9. REMOVER
int RemoverVenda(Arv *A, int id) {            
    if (VaziaArvore(A)) {
        return 0; // Falha: árvore vazia
    }
    
    int removido = 0;
    A->raiz = auxRemover(A->raiz, id, &removido);    
    return removido;
}

// Auxiliar - Encontrar mínimo
// NoArv* EncontrarMinimo(NoArv* no) {            
//     while (no && no->esq != NULL) {
//         no = no->esq;
//     }
//     return no;
// }

NoArv* EncontrarMaximo(NoArv* no) {
    while (no->dir != NULL) {
        no = no->dir;
    }
    return no;
}


// Auxiliar - Remoção recursiva
NoArv* auxRemover(NoArv* no, int id, int* removido) { //obs remove apenas o id 
    if (no == NULL) {
        *removido = 0; //caso arvore vazia
        return no;
    }
    
    if (id < no->venda.id) {
        no->esq = auxRemover(no->esq, id, removido);
    } else if (id > no->venda.id) {
        no->dir = auxRemover(no->dir, id, removido);
    } else {
        // Nó encontrado para remoção
        *removido = 1;
        
        // Caso 1: Nó folha ou com apenas um filho
        if (no->esq == NULL) {
            NoArv* temp = no->dir;
            free(no);
            return temp;
        } else if (no->dir == NULL) {
            NoArv* temp = no->esq;
            free(no);
            return temp;
        }
        
        // Caso 2: Nó com dois filhos
        NoArv* temp = EncontrarMaximo(no->esq); //maior valor da subárvore esquerda
        no->venda = temp->venda;
        no->esq = auxRemover(no->esq, temp->venda.id, removido);
    }
    
    return no;
}
// 10. LIBERAR ÁRVORE
void LiberarArvore(Arv *A) {
    if (A != NULL) {
        auxLiberar(A->raiz);                   
        free(A);
    }
}

// Auxiliar - Liberar memória recursivamente
void auxLiberar(NoArv* no) {                  
    if (no != NULL) {
        auxLiberar(no->esq);
        auxLiberar(no->dir);
        free(no);
    }
}

#endif // ARVORE_H_INCLUDED