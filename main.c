#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ABB.h"

// ===  Funções ===
void menu();
void inserirVenda();
void listarVendas();
void buscarVendedor();
void listarVendaPorValor();
void exibirEstatisticas();
void removerVenda();


// === Protótipos de funções ===
int GerarID();
int IDExiste(Arv *arv, int id);
int GerarIDUnico(Arv *arv);
int SelecionarImpressao();
NoArv* InserirNovaVenda(Arv *arv, Venda venda);
void ListarVendas(Arv *arv);


// === Função main ===
int main() {

    menu();

    return 0;
}

// === Função para chamar o menu ===

void menu() {
    int opcao;

    do {
        printf("\n=============================================\n");
        printf("                    MENU\n");
        printf("=============================================\n");
        printf("1. Inserir nova venda\n");
        printf("2. Listar todas as vendas (crescente/decrescente)\n");
        printf("3. Buscar vendas de um vendedor\n");
        printf("4. Listar vendas acima ou abaixo de um valor\n");
        printf("5. Exibir estatísticas\n");
        printf("6. Remover uma venda\n");
        printf("7. Finalizar sistema\n");
        printf("=============================================\n");
        printf("Selecione uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirVenda();
                break;

            case 2:
                listarVendas();
                break;

            case 3:
                buscarVendedor();
                break;

            case 4:
                listarVendaPorValor();
                break;

            case 5:
                exibirEstatisticas();
                break;

            case 6:
                removerVenda();
                break;

            case 7:
            //Todo: dar free nas arvores 
                printf("\nFinalizando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 7);
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

void inserirVenda() {
    printf("\n[inserirVenda] Ainda nao implementada.\n");
}

void listarVendas() {
    printf("\n[listarVendas] Ainda nao implementada.\n");
}

void buscarVendedor() {
    printf("\n[buscarVendedor] Ainda nao implementada.\n");
}

void listarVendaPorValor() {
    printf("\n[listarVendaPorValor] Ainda nao implementada.\n");
}

void exibirEstatisticas() {
    printf("\n[exibirEstatisticas] Ainda nao implementada.\n");
}

void removerVenda() {
    printf("\n[removerVenda] Ainda nao implementada.\n");
}


