#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ABB.h"

// === Protótipos de funções principais ===
void InserirNovaVenda(Arv *arv);
void ListarVendas(Arv *arv);

// === Protótipos de funções auxiliares ===
int GerarID();
int IDExiste(Arv *arv, int id);
int GerarIDUnico(Arv *arv);
int SelecionarImpressao();

// Protótipos para matrícula
void GerarMatricula(char matricula[5]);
void GerarMatriculaUnica(Arv *arv, char matricula[5]);
int MatriculaExiste(Arv *arv, char matricula[5]);
void auxVerificarMatricula(NoArv* no, char matricula[5], int* existe);

// Protótipos para vendedores
int ProcessarVendedorExistente(Arv *arv, char matricula[5], char nomeVendedor[51]);
int ProcessarNovoVendedor(Arv *arv, char matricula[5], char nomeVendedor[51]);
Venda CriarVenda(char matricula[5], char nomeVendedor[51], Arv *arv);  // ✅ Adicionado
void BuscarDadosVendedorPorMatricula(Arv *arv, char matricula[5], char nomeEncontrado[51]);
void auxBuscarDadosVendedor(NoArv* no, char matricula[5], char nomeEncontrado[51], int* encontrou);


void listarVendaPorValor(Arv *A, float valorBusca, int maiorMenor);
void auxPrintVendasMaior(NoArv *no, float valorBusca);
void auxPrintVendasMaior(NoArv *no, float valorBusca);


// === Função main ===
int main() {

    Arv *A1 = CriaArvore();

    menu(A1);

    return 0;
}

// === Função para chamar o menu ===

void menu(Arv *A) {
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
//                listarVendaPorValor(A, valorBusca, maiorMenor);
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

// == Gerar matrícula de vendedor no formato V + 3 dígitos ==
void GerarMatricula(char matricula[5]) {
    int inicializado = 0;

    // Inicializar srand apenas uma vez
    if (!inicializado) {
        srand(time(NULL));
        inicializado = 1;
    }

    // Gerar número entre 100 e 999
    int numero = 100 + rand() % 900;

    // Preencher o vetor de caracteres
    matricula[0] = 'V';                    // Primeira posição: 'V'
    matricula[1] = '0' + (numero / 100);   // Centena
    matricula[2] = '0' + ((numero / 10) % 10); // Dezena
    matricula[3] = '0' + (numero % 10);    // Unidade
    matricula[4] = '\0';                   // Terminador de string
}


// == Verificar se matrícula já existe ==
int MatriculaExiste(Arv *arv, char matricula[5]) {
    if (VaziaArvore(arv)) {
        return 0; // Árvore vazia, matrícula não existe
    }

    int existe = 0;
    auxVerificarMatricula(arv->raiz, matricula, &existe);
    return existe;
}

// == Auxiliar recursivo para verificar matrícula ==
void auxVerificarMatricula(NoArv* no, char matricula[5], int* existe) {
    if (no != NULL && !(*existe)) {
        // Comparar strings caractere por caractere
        int iguais = 1;
        for (int i = 0; i < 4; i++) {
            if (no->venda.matricula[i] != matricula[i]) {
                iguais = 0;
                break;
            }
        }

        if (iguais) {
            *existe = 1;
            return;
        }

        // Continuar busca
        auxVerificarMatricula(no->esq, matricula, existe);
        auxVerificarMatricula(no->dir, matricula, existe);
    }
}

// == Gerar matrícula única ==
void GerarMatriculaUnica(Arv *arv, char matricula[5]) {
    int tentativas = 0;
    const int MAX_TENTATIVAS = 800; // Limite de tentativas

    do {
        GerarMatricula(matricula);
        tentativas++;

        if (tentativas >= MAX_TENTATIVAS) {
            printf("ERRO: Não foi possível gerar matrícula única!\n");
            // Matrícula de erro
            matricula[0] = 'E';
            matricula[1] = 'R';
            matricula[2] = 'R';
            matricula[3] = 'O';
            matricula[4] = '\0';
            return;
        }

    } while (MatriculaExiste(arv, matricula));
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



// === Funcionalidades do sistema ===

// 1. Inserir nova venda na árvore
void InserirNovaVenda(Arv *arv) {
    char matricula[5];
    char nomeVendedor[51];
    int opcaoVendedor;

    printf("\n=== INSERIR NOVA VENDA ===\n");
    printf("1 - Vendedor existente | 2 - Novo vendedor\n");
    printf("Escolha: ");
    scanf("%d", &opcaoVendedor);

    // Processar vendedor
    int vendedorOK = (opcaoVendedor == 1) ?
        ProcessarVendedorExistente(arv, matricula, nomeVendedor) :
        ProcessarNovoVendedor(arv, matricula, nomeVendedor);

    if (!vendedorOK) {
        printf("Operação cancelada.\n");
        return;
    }

    // Criar e inserir venda
    Venda novaVenda = CriarVenda(matricula, nomeVendedor, arv);

    if (InserirVenda(arv, novaVenda)) {
        printf("\nVENDA INSERIDA COM SUCESSO!\n");
        ImprimirVenda(novaVenda);
    } else {
        printf("\nERRO: Falha ao inserir venda!\n");
    }
}

// 1.1 Auxiliar - Processar vendedor existente
int ProcessarVendedorExistente(Arv *arv, char matricula[5], char nomeVendedor[51]) {
    int confirma;
    char nomeExistente[51];

    printf("Digite a matrícula do vendedor (formato V000): ");
    scanf("%s", matricula);

    // Verificar se matrícula existe
    if (!MatriculaExiste(arv, matricula)) {
        printf("ERRO: Matrícula %s não encontrada!\n", matricula);
        printf("Dica: Use a opção 2 para cadastrar novo vendedor.\n");
        return 0;
    }

    // Buscar dados do vendedor
    BuscarDadosVendedorPorMatricula(arv, matricula, nomeExistente);

    printf("Vendedor encontrado: %s\n", nomeExistente);
    printf("Confirma este vendedor?\n");
    printf("1 - Sim, continuar\n");
    printf("2 - Não, cancelar\n");
    printf("Escolha: ");
    scanf("%d", &confirma);

    switch(confirma) {
        case 1:
            strcpy(nomeVendedor, nomeExistente);
            printf("Vendedor confirmado: %s (%s)\n", nomeVendedor, matricula);
            return 1;

        case 2:
            printf("Operação cancelada pelo usuário.\n");
            return 0;

        default:
            printf("Opção inválida. Operação cancelada.\n");
            return 0;
    }
}

// 1.2 Auxiliar - Processar novo vendedor
int ProcessarNovoVendedor(Arv *arv, char matricula[5], char nomeVendedor[51]) {
    printf("Digite o nome do novo vendedor: ");
    getchar(); // Limpar buffer
    fgets(nomeVendedor, 51, stdin);
    nomeVendedor[strcspn(nomeVendedor, "\n")] = 0; // Remove quebra de linha

    // Verificar se nome não está vazio
    if (strlen(nomeVendedor) == 0) {
        printf("ERRO: Nome do vendedor não pode estar vazio!\n");
        return 0;
    }

    // Gerar matrícula única
    int tentativas = 0;
    do {
        GerarMatriculaUnica(arv, matricula);
        tentativas++;

        if (tentativas > 10) {
            printf("ERRO: Falha ao gerar matrícula após várias tentativas.\n");
            return 0;
        }
    } while (strcmp(matricula, "ERRO") == 0);

    printf("Novo vendedor cadastrado!\n");
    printf("Nome: %s\n", nomeVendedor);
    printf("Matrícula: %s\n", matricula);

    return 1;
}

Venda CriarVenda(char matricula[5], char nomeVendedor[51], Arv *arv) {
    Venda novaVenda;

    // Gerar ID único
    novaVenda.id = GerarIDUnico(arv);

    // Copiar dados do vendedor
    strcpy(novaVenda.vendedor, nomeVendedor);
    strcpy(novaVenda.matricula, matricula);

    // Coletar dados do cliente
    printf("\n--- DADOS DA VENDA ---\n");
    printf("Nome do cliente: ");
    getchar(); // Limpar buffer
    fgets(novaVenda.cliente, 51, stdin);
    novaVenda.cliente[strcspn(novaVenda.cliente, "\n")] = 0;

    // Coletar data
    printf("Data da transação (DD MM AAAA): ");
    scanf("%d %d %d", &novaVenda.dataTransacao.dia,
          &novaVenda.dataTransacao.mes, &novaVenda.dataTransacao.ano);

    // Coletar valor
    printf("Valor da transação: R$ ");
    scanf("%f", &novaVenda.valorTransacao);

    return novaVenda;
}

// 1.3 Buscar dados do vendedor por matrícula
void BuscarDadosVendedorPorMatricula(Arv *arv, char matricula[5], char nomeEncontrado[51]) {
    strcpy(nomeEncontrado, ""); // Inicializar vazio

    if (!VaziaArvore(arv)) { // Pegar o nome referente a matricula
        int encontrou = 0;
        auxBuscarDadosVendedor(arv->raiz, matricula, nomeEncontrado, &encontrou);
    }
}

// Auxiliar recursivo para buscar dados do vendedor
void auxBuscarDadosVendedor(NoArv* no, char matricula[5], char nomeEncontrado[51], int* encontrou) {
    if (no != NULL && !(*encontrou)) {
        if (strcmp(no->venda.matricula, matricula) == 0) {
            strcpy(nomeEncontrado, no->venda.vendedor);
            *encontrou = 1;
            return;
        }

        // Continuar busca recursivamente
        auxBuscarDadosVendedor(no->esq, matricula, nomeEncontrado, encontrou);
        auxBuscarDadosVendedor(no->dir, matricula, nomeEncontrado, encontrou);
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

void listarVendaPorValor(Arv *A, float valorBusca, int maiorMenor) {
    if(!VaziaArvore(A)){
        switch(maiorMenor){
            case 1:
                auxPrintVendasMaior(A -> raiz, valorBusca);
                break;
            case 2:
                auxPrintVendasMenor(A -> raiz, valorBusca);
                break;
        }
    }
}

void auxPrintVendasMaior(NoArv *no, float valorBusca){
    if(no != NULL){
        auxPrintVendasMaior(no -> dir, valorBusca);
        if(no -> venda.valorTransacao > valorBusca){
            ImprimirVenda(no ->venda);
        }
        auxPrintVendasMaior(no -> esq, valorBusca);
    }
}

void auxPrintVendasMenor(NoArv *no, float valorBusca){
    if(no != NULL){
        auxPrintVendasMenor(no -> dir, valorBusca);
        if(no -> venda.valorTransacao < valorBusca){
            ImprimirVenda(no ->venda);
        }
        auxPrintVendasMenor(no -> esq, valorBusca);
    }
}

void exibirEstatisticas() {
    printf("\n[exibirEstatisticas] Ainda nao implementada.\n");
}

void removerVenda() {
    printf("\n[removerVenda] Ainda nao implementada.\n");
}


