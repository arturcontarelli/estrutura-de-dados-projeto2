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
int BuscarVenda(Arv *A, int id);
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
int auxBuscar(NoArv* no, int id);
NoArv* auxRemover(NoArv* no, int id, int* removido);
NoArv* EncontrarMinimo(NoArv* no);
NoArv* EncontrarMaximo(NoArv* no);
void auxLiberar(NoArv* no);
int QuantidadeVendas(NoArv* pai);
float SomaVendas (NoArv* pai);
int BuscarVendasPorNome(NoArv* no, char vendedor[51]);
int BuscarVendasPorMatricula(NoArv* no, char matricula[5]);

// ========== IMPLEMENTAÇÕES ==========

// 1. CRIAR ÁRVORE -> igual em aula
Arv* CriaArvore() {
    Arv* a = (Arv*) malloc(sizeof(Arv));
    a->raiz = NULL; 
    return a;
}

// 2. VERIFICA SE A ÁRVORE ESTÁ VAZIA
int VaziaArvore(Arv *A) {
    if (A->raiz == NULL) {
        return 1; //se raiz for NULL nao tem elemento
    } 
    return 0;
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

// 6. IMPRIMIR ÁRVORE
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
    }

    
    printf("===========================\n\n");
}

// 7. BUSCAR UM ELEMENTO NA ÁRVORE POR VALOR (ID)
int BuscarVenda(Arv *A, int id) {           
    if (VaziaArvore(A)) {
        return 0;
    }
    return auxBuscar(A->raiz, id);             
}

// Auxiliar - Busca recursiva
int auxBuscar(NoArv* pai, int id) {
    if (pai->venda.id == id) {
        return 1; // 1 se achou
    }
    
    if (id < pai->venda.id) {
        if (pai->esq != NULL) {
            return auxBuscar(pai->esq, id);
        }
        return 0; // se n tiver ja sai
    }
    if (id > pai->venda.id) {
        if (pai->dir != NULL) {
            return auxBuscar(pai->esq, id);
        }
        return 0; // se n tiver ja sai
    }
    
}

// buscar venda por nome ou matricula
int BuscarVendasPorNome(NoArv* no, char vendedor[51]) {
    if (no == NULL) return 0;
    
    int count = (strcmp(no->venda.vendedor, vendedor) == 0) ? 1 : 0;
    return count + BuscarVendasPorNome(no->dir, vendedor) + 
                   BuscarVendasPorNome(no->esq, vendedor);
}

int BuscarVendasPorMatricula(NoArv* no, char matricula[5]) {
    if (no == NULL) return 0;
    
    int count = (strcmp(no->venda.matricula, matricula) == 0) ? 1 : 0;
    return count + BuscarVendasPorMatricula(no->dir, matricula) + 
                   BuscarVendasPorMatricula(no->esq, matricula);
}

// 8. INSERIR
int InserirVenda(Arv *A, Venda venda) {
    // Aloca espaço e inicializa
    NoArv* novo = CriaNo(venda);
    // Se a raiz da árvore está vazia, novo é a raiz
    if (VaziaArvore(A)) {
        A->raiz = novo;
        return 1;
    } else {
        // Cria um pai para não perder a raiz 
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
    if (!VaziaArvore(A)) {
        auxLiberar(A->raiz);
        free(A);
    }
}

// Auxiliar - Liberar memória recursivamente
void auxLiberar(NoArv* no) {
    if(no -> esq != NULL) auxLiberar(no->esq);
    if(no -> dir != NULL) auxLiberar(no->dir);
    free(no);
}

int QuantidadeVendas(NoArv* pai) {
    // qnd acabar retorna 0 q n tem mais nó
    if (pai == NULL)
        return 0;

    // conta o nó atual (1) + nós da esquerda + nós da direita
    return 1 + QuantidadeVendas(pai->esq) + QuantidadeVendas(pai->dir);
}

float SomaVendas (NoArv* pai) {
    if(pai == NULL) return 0.0;
    // vai somando os valores de transação
    float S = pai->venda.valorTransacao;
    if (pai->dir != NULL) {
        S += SomaVendas(pai->dir);
    }
    if (pai->esq != NULL) {
        S += SomaVendas(pai->esq);
    }
    return S; // retorna valor total
}


#endif // ARVORE_H_INCLUDED