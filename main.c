#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ABB.h"

// === Protótipos de funções ===
int GerarID();
int IDExiste(Arv *arv, int id);
int GerarIDUnico(Arv *arv);
int SelecionarImpressao();
NoArv* InserirNovaVenda(Arv *arv, Venda venda);
void ListarVendas(Arv *arv);
void GerarMatriculaVendedor(char* matricula);



// === Função main ===
int main (){

}

// === Funções Auxiliares ===

// == gerar ID aleatório ==

int GerarID(){
    srand(time(NULL));
    return (rand() % 9000) + 1000; // Gera ID entre 1000 e 9999
}
// == Verificar se ID já existe ==

int IDExiste(Arv *arv, int id){
    NoArv* resultado = BuscarVenda(arv, id);
    return (resultado != NULL);
}

// == Gera ID único ==
int GerarIDUnico(Arv *arv){
    int id;
    do {
        id = GerarID();
    } while (IDExiste(arv, id));
    return id;
}

int GerarMatricula(){
    srand(time(NULL));
    atoi(matricula);
    return (rand() % 900) + 100; // Gera número entre 100 e 999
}


// == Selecionar tipo de impressão, crescente ou decrescente ==
int SelecionarImpressao(){
    int escolha;
    printf("Selecione o tipo de impressao \n 1 - Crescente \n 2 - Decrescente\n");
    scanf("%d", &escolha);
    switch(escolha){
        case 1:
            return 1; // Crescente
        case 2:
            return 2; // Decrescente
        default:
            printf("Escolha invalida. Selecionando crescente por padrao.\n");
            return 1;
    }

}

// == Gerar matrícula de vendedor no formato V + 3 dígitos ==
void GerarMatriculaVendedor(char* matricula){
    srand((unsigned int)time(NULL));
    int numero = rand() % 1000; // Gera número entre 0 e 999
    // Cada vendedor terá matrícula única no sistema, porem pode ter diferente número de ID de vendas
    sprintf(matricula, "V%03d", numero); // Formata como V + 3 dígitos
}

// === Funcionalidades do sistema ===
 
// 1. Inserir nova venda 

NoArv* InserirNovaVenda(Arv *arv, Venda venda){
    venda.id = GerarIDUnico(arv);
    if (InserirVenda(arv, venda)) {
        printf("Venda inserida com sucesso! ID: %d\n", venda.id);
        return BuscarVenda(arv, venda.id);
    } else {
        printf("Falha ao inserir venda.\n");
        return NULL;
    }
}

// 2. Listar todas as vendas (crescete ou decrescente)
// no formato ID | Vendedor | Matrícula |Cliente | Data de Transação| Valor(R$)

void ListarVendas(Arv *arv){
    int ordem = SelecionarImpressao();
    switch(ordem){
        case 1:
            ImprimirArvore(arv, 2); // Em ordem crescente
            break;
        case 2:
            ImprimirArvore(arv, 4); // Em ordem decrescente
            break;
        default:
            printf("Ordem invalida.\n");
            break;
    }
}

