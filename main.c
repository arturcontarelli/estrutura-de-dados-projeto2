#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ABB.h"

void menu();
void InserirNovaVenda(Arv *arv);
void ListarVendas(Arv *arv);
void BuscarVendedor(Arv *arv);
void ListarVendaPorValor(Arv *A, float valorBusca, int maiorMenor);
void ExibirEstatisticas(Arv *arv);
void RemoverVenda(Arv *arv);

int GerarID();
int IDExiste(Arv *arv, int id);
int GerarIDUnico(Arv *arv);
void auxPrintVendasMaior(NoArv *no, float valorBusca);
void auxPrintVendasMenor(NoArv *no, float valorBusca);

void GerarMatricula(char matricula[5]);
void GerarMatriculaUnica(Arv *arv, char matricula[5]);
int MatriculaExiste(Arv *arv, char matricula[5]);
int auxVerificarMatricula(NoArv* no, char matricula[5]);

int ProcessarVendedorExistente(Arv *arv, char matricula[5], char nomeVendedor[51]);
int ProcessarNovoVendedor(Arv *arv, char matricula[5], char nomeVendedor[51]);
Venda CriarVenda(char matricula[5], char nomeVendedor[51], Arv *arv);
int BuscarDadosVendedorPorMatricula(Arv *arv, char matricula[5], char nomeEncontrado[51]);
int auxBuscarDadosVendedor(NoArv* no, char matricula[5], char nomeEncontrado[51]);

int auxImprimirVendasPorNome(NoArv *no, char vendedor[51], int *cabecalhoImpresso);
int auxImprimirVendasPorMatricula(NoArv *no, char matricula[5], int *cabecalhoImpresso);

int main() {
    srand(123);
    menu();
    return 0;
}

void menu() {
    Arv* arvore = CriaArvore();
    int opcao;
    int entradaValida;

    if (arvore == NULL) {
        printf("ERRO: Falha ao inicializar o sistema!\n");
        return;
    }
    do {
        system("cls");
        printf("\n =============================================\n");
        printf("||           SISTEMA DE VENDAS               || \n");
        printf(" =============================================\n");
        printf(" > 1.  Inserir nova venda \n");
        printf(" > 2.  Listar todas as vendas \n");
        printf(" > 3.  Buscar vendas de um vendedor \n");
        printf(" > 4.  Filtrar vendas por valor \n");
        printf(" > 5.  Exibir estatisticas \n");
        printf(" > 6.  Remover uma venda por ID\n");
        printf(" > 7.  Finalizar sistema \n");
        printf("=============================================\n");
        printf("--- Selecione uma opcao (1-7): ---\n");

        entradaValida = scanf("%d", &opcao);
        while (getchar() != '\n');

        if (!entradaValida) {
            printf("\n ERRO: Digite apenas numeros!\n");
            printf(" Pressione ENTER para continuar...");
            getchar();
            continue;
        }

        printf("\n");

        switch (opcao) {
            case 1:
                system("cls");
                InserirNovaVenda(arvore);
                break;

            case 2:
                system("cls");
                if (VaziaArvore(arvore)) {
                    printf(" Nenhuma venda cadastrada ainda.\n");
                } else {
                    ListarVendas(arvore);
                }
                break;

            case 3:
                system("cls");
                if (VaziaArvore(arvore)) {
                    printf(" Nenhuma venda cadastrada para buscar.\n");
                } else {
                    BuscarVendedor(arvore);
                }
                break;

            case 4: {
                system("cls");
                if (VaziaArvore(arvore)) {
                    printf(" Nenhuma venda cadastrada para filtrar.\n");
                } else {
                    float valor;
                    int tipoFiltro;

                    printf(" === FILTRAR VENDAS POR VALOR ===\n");
                    printf("Digite o valor de referência: R$ ");

                    if (scanf("%f", &valor) != 1 || valor < 0) {
                        while (getchar() != '\n');
                        printf(" Valor invalido! Use numeros positivos.\n");
                        break;
                    }

                    printf("\nTipo de filtro:\n");
                    printf("1 - Vendas ACIMA de R$ %.2f\n", valor);
                    printf("2 - Vendas ABAIXO de R$ %.2f\n", valor);
                    printf("Escolha (1 ou 2): ");
                    scanf("%d", &tipoFiltro);

                    if (tipoFiltro != 1 && tipoFiltro != 2) {
                        while (getchar() != '\n');
                        printf(" Opcao invalida! Escolha 1 ou 2.\n");
                        break;
                    }

                    printf("\n Buscando vendas...\n");
                    ListarVendaPorValor(arvore, valor, tipoFiltro);
                }
                break;
            }

            case 5:
                system("cls");
                if (VaziaArvore(arvore)) {
                    printf(" Nenhuma venda cadastrada para gerar estatisticas.\n");
                } else {
                    printf(" Calculando estatisticas...\n");
                    ExibirEstatisticas(arvore);
                }
                break;

            case 6:
                system("cls");
                if (VaziaArvore(arvore)) {
                    printf(" Nenhuma venda cadastrada para remover.\n");
                } else {
                    RemoverVenda(arvore);
                }
                break;

            case 7:
                system("cls");
                printf(" Finalizando sistema...\n");
                LiberarArvore(arvore);
                break;

            default:
                system("cls");
                printf(" OPCAO INVALIDA!\n");
                printf(" Escolha um numero entre 1 e 7.\n");
                break;
        }

        if (opcao != 7) {
            system("pause");
        }

    } while (opcao != 7);
}

Venda CriarVenda(char matricula[5], char nomeVendedor[51], Arv *arv) {
    Venda novaVenda;
    int dia, mes, ano;
    int dataValida = 0;

    novaVenda.id = GerarIDUnico(arv);

    strcpy(novaVenda.vendedor, nomeVendedor);
    strcpy(novaVenda.matricula, matricula);

    printf("\n--- DADOS DA VENDA ---\n");
    printf("Nome do cliente: ");
    fgets(novaVenda.cliente, 51, stdin);
    novaVenda.cliente[strcspn(novaVenda.cliente, "\n")] = 0;

    do {
        printf("Data da transacão (DD MM AAAA): ");
        int lidos = scanf("%d %d %d", &dia, &mes, &ano);

        if (lidos != 3) {
            printf("Entrada invalida! Digite apenas numeros no formato DD MM AAAA.\n");
            while (getchar() != '\n');
            continue;
        }

        if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900) {
            printf("Data fora do intervalo valido. Tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }

        dataValida = 1;
        while (getchar() != '\n');

    } while (!dataValida);

    novaVenda.dataTransacao.dia = dia;
    novaVenda.dataTransacao.mes = mes;
    novaVenda.dataTransacao.ano = ano;

    printf("Valor da transacão: R$ ");
    scanf("%f", &novaVenda.valorTransacao);

    return novaVenda;
}

int GerarID() {
    return (rand() % 9000) + 1000;
}

int IDExiste(Arv *arv, int id) {
    int resultado = BuscarVenda(arv, id);
    return resultado;
}

int GerarIDUnico(Arv *arv) {
    int id;
    do {
        id = GerarID();
    } while (IDExiste(arv, id));
    return id;
}

void GerarMatricula(char matricula[5]) {
    int numero = 100 + rand() % 900;  
    char numeroStr[4];                
    
 
    itoa(numero, numeroStr, 10);     
    
    matricula[0] = 'V';               
    strcpy(matricula + 1, numeroStr); 
    
}

int MatriculaExiste(Arv *arv, char matricula[5]) {
    if (VaziaArvore(arv)) {
        return 0;
    }
    return auxVerificarMatricula(arv->raiz, matricula);
}

int auxVerificarMatricula(NoArv* no, char matricula[5]) {
    if (no == NULL) {
        return 0;
    }

    if (strcmp(no->venda.matricula, matricula) == 0) {
        return 1;
    }

    return auxVerificarMatricula(no->esq, matricula) || auxVerificarMatricula(no->dir, matricula);
}

void GerarMatriculaUnica(Arv *arv, char matricula[5]) {
    int tentativas = 0;
    const int MAX_TENTATIVAS = 800;
    int continuar = 1;

    do {
        GerarMatricula(matricula);
        tentativas++;

        if (tentativas >= MAX_TENTATIVAS) {
            matricula[0] = 'E';
            matricula[1] = 'R';
            matricula[2] = 'R';
            matricula[3] = 'O';
            matricula[4] = '\0';
            continuar = 0;
        }

    } while (continuar && MatriculaExiste(arv, matricula));
}

void InserirNovaVenda(Arv *arv) {
    char matricula[5];
    char nomeVendedor[51];
    int opcaoVendedor;

    do {
        printf("\n=== INSERIR NOVA VENDA ===\n");
        printf("1 - Vendedor existente | 2 - Novo vendedor\n");
        printf("Escolha: ");
        scanf("%d", &opcaoVendedor);

        if (opcaoVendedor != 1 && opcaoVendedor != 2) {
            system("cls");
            printf("Opcao invalida! Digite 1 ou 2.\n");
        }

    } while (opcaoVendedor != 1 && opcaoVendedor != 2);

    int vendedorOK;
    if(opcaoVendedor == 1){
        vendedorOK = ProcessarVendedorExistente(arv, matricula, nomeVendedor);
    } else{
        vendedorOK = ProcessarNovoVendedor(arv, matricula, nomeVendedor);
    }

    if(!vendedorOK) {
        printf("Operacao cancelada.\n");
    }
    else {
        Venda novaVenda = CriarVenda(matricula, nomeVendedor, arv);

        if (InserirVenda(arv, novaVenda)) {
            printf("\nVENDA INSERIDA COM SUCESSO!\n");
            ImprimirVenda(novaVenda);
        } else {
            printf("\nERRO: Falha ao inserir venda!\n");
        }
    }
}

int ProcessarVendedorExistente(Arv *arv, char matricula[5], char nomeVendedor[51]) {
    int confirma;
    char nomeExistente[51];

    do{
        printf("Digite a matricula do vendedor (formato V000): ");
        scanf("%s", matricula);

     }while(strlen(matricula) != 4 || matricula[0] != 'V');

    if (!MatriculaExiste(arv, matricula)) {
        printf("ERRO: Matricula %s nao encontrada!\n", matricula);
        printf("Dica: Use a opcao 2 para cadastrar novo vendedor.\n");
        return 0;
    }

    int vendedorExiste = BuscarDadosVendedorPorMatricula(arv, matricula, nomeExistente);

    if(vendedorExiste){
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
                printf("Operacao cancelada pelo usuario.\n");
                return 0;

            default:
                printf("Opcao invalida. Operacao cancelada.\n");
                return 0;
        }
    } else{
        return 0;
    }
}

int ProcessarNovoVendedor(Arv *arv, char matricula[5], char nomeVendedor[51]) {
    printf("Digite o nome do novo vendedor: ");
    getchar();
    fgets(nomeVendedor, 51, stdin);
    nomeVendedor[strcspn(nomeVendedor, "\n")] = 0;

    if (strlen(nomeVendedor) == 0) {
        printf("ERRO: Nome do vendedor não pode estar vazio!\n");
        return 0;
    }

    int tentativas = 0;
    do {
        GerarMatriculaUnica(arv, matricula);
        tentativas++;

        if (tentativas > 10) {
            printf("ERRO: Falha ao gerar matricula apos varias tentativas.\n");
            return 0;
        }
    } while (strcmp(matricula, "ERRO") == 0);

    printf("Novo vendedor cadastrado!\n");
    printf("Nome: %s\n", nomeVendedor);
    printf("Matricula: %s\n", matricula);

    return 1;
}

int BuscarDadosVendedorPorMatricula(Arv *arv, char matricula[5], char nomeEncontrado[51]) {
    strcpy(nomeEncontrado, "");

    if (!VaziaArvore(arv)) {
        int encontrou = auxBuscarDadosVendedor(arv->raiz, matricula, nomeEncontrado);
        return encontrou;
    } else{
        return 0;
    }
}

int auxBuscarDadosVendedor(NoArv* no, char matricula[5], char nomeEncontrado[51]) {
    int encontrou = 0;
    if (strcmp(no->venda.matricula, matricula) == 0) {
        strcpy(nomeEncontrado, no->venda.vendedor);
        encontrou = 1;
        return encontrou;
    }

    if(no->esq != NULL){
        encontrou = auxBuscarDadosVendedor(no->esq, matricula, nomeEncontrado);
    }
    if(no->dir != NULL && encontrou == 0){
        encontrou = auxBuscarDadosVendedor(no->dir, matricula, nomeEncontrado);
    }
    return encontrou;
}

void ListarVendas(Arv *arv){
    int escolha;
    printf("Selecione o tipo de impressao \n 1 - Decrescente \n 2 - Crescente\n");
    fflush(stdin);
    scanf("%d", &escolha);
    switch(escolha){
        case 1:
                system("cls");
                ImprimirArvore(arv, 2);
                break;
        case 2:
                system("cls");
                ImprimirArvore(arv, 4);
                break;
        default:
            system("cls");
            printf("Escolha invalida. Selecionando crescente por padrao.\n");
            ImprimirArvore(arv, 4);
            break;
    }
}

void ListarVendaPorValor(Arv *A, float valorBusca, int maiorMenor) {
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
        if(no ->dir != NULL)auxPrintVendasMaior(no -> dir, valorBusca);
        if(no -> venda.valorTransacao > valorBusca){
            ImprimirVenda(no ->venda);
        }
        if(no ->esq != NULL) auxPrintVendasMaior(no -> esq, valorBusca);
    }
}

void auxPrintVendasMenor(NoArv *no, float valorBusca){
    if(no != NULL){
        if(no ->dir != NULL)auxPrintVendasMenor(no -> dir, valorBusca);
        if(no -> venda.valorTransacao < valorBusca){
            ImprimirVenda(no ->venda);
        }
        if(no ->esq != NULL) auxPrintVendasMenor(no -> esq, valorBusca);
    }
}

void ExibirEstatisticas(Arv *arv) {
    int qnt = QuantidadeVendas(arv->raiz);
    float somaFaturamento = SomaVendas(arv->raiz);
    char resposta;

    printf("Estatisticas:\n");
    printf("Quantidade Total de Vendas: %d\n", qnt);
    printf("Soma Total das Vendas: %.2f\n", somaFaturamento);

    printf("Deseja verificar o número de vendas de um vendedor (s/n)? ");
    scanf(" %c", &resposta);

    if (resposta == 'S' || resposta == 's') {
        char vendedor[51];
        printf("\n Como deseja encotrar seu vendedor (1=Nome, 2=Matricula): ");
        int opcao;
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("\nDigite o nome do vendedor: ");
                getchar();
                fgets(vendedor, sizeof(vendedor), stdin);
                vendedor[strcspn(vendedor, "\n")] = '\0';

                if (strlen(vendedor) == 0) {
                    printf("Nome do vendedor não pode estar vazio!\n");
                    break;
                }
                int cont = BuscarVendasPorNome(arv->raiz, vendedor);
                printf("Vendedor %s encontrado\n Vendas realizadas: %d\n", vendedor, cont);
                break;

           case 2: {
                char matricula[5];
                char nomeVendedor[51];

                do {
                    printf("\nDigite a matricula do vendedor (formato V000): ");
                    scanf("%s", matricula);
                } while (strlen(matricula) != 4 || matricula[0] != 'V');

                if (!BuscarDadosVendedorPorMatricula(arv, matricula, nomeVendedor)) {
                    printf("Matricula %s nao encontrada!\n", matricula);
                    break;
                }

                int cont2 = BuscarVendasPorMatricula(arv->raiz, matricula);

                printf("\nVendedor: %s\nMatricula: %s\nVendas realizadas: %d\n",
                    nomeVendedor, matricula, cont2);

                break;
            }

            default:
                printf("Opcão invalida!\n");
                return;
        }
    }
}

void BuscarVendedor(Arv *arv) {
    int opcao;
    char vendedor[51];
    char matricula[5];
    int cabecalho = 0;
    int encontrou = 0;

    printf("=== BUSCAR VENDAS DE UM VENDEDOR ===\n");

    if (!VaziaArvore(arv)) {

        printf("1 - Buscar pelo nome do vendedor\n");
        printf("2 - Buscar pela matricula do vendedor\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {

           do {
                printf("\nDigite o nome do vendedor: ");
                getchar();
                fgets(vendedor, sizeof(vendedor), stdin);
                vendedor[strcspn(vendedor, "\n")] = '\0';

                if (strlen(vendedor) == 0) {
                    printf("Nome do vendedor nao pode estar vazio! Tente novamente.\n");
                }

            } while (strlen(vendedor) == 0);

            encontrou = auxImprimirVendasPorNome(arv->raiz, vendedor, &cabecalho);

            if (!encontrou) {
                printf("Nenhuma venda encontrada para o vendedor \"%s\".\n", vendedor);
            }

        }
        else if (opcao == 2) {

            do {
                printf("\nDigite a matricula do vendedor (formato V000): ");
                scanf("%s", matricula);
            } while (strlen(matricula) != 4 || matricula[0] != 'V');

            encontrou = auxImprimirVendasPorMatricula(arv->raiz, matricula, &cabecalho);

            if (!encontrou) {
                printf("Nenhuma venda encontrada para a matricula %s.\n", matricula);
            }

        } else {
            printf("Opcao invalida!\n");
        }

    } else {
        printf("Nenhuma venda cadastrada.\n");
    }
}

int auxImprimirVendasPorNome(NoArv *no, char vendedor[51], int *cabecalhoImpresso) {
    int encontrou = 0;

    if (no != NULL) {

        if (auxImprimirVendasPorNome(no->esq, vendedor, cabecalhoImpresso)) {
            encontrou = 1;
        }

        char nomeNo[51];
        char nomeBuscado[51];

        strcpy(nomeNo, no->venda.vendedor);
        strcpy(nomeBuscado, vendedor);

        strParaMinusculo(nomeNo);
        strParaMinusculo(nomeBuscado);

        if (strcmp(nomeNo, nomeBuscado) == 0) {

            if (!(*cabecalhoImpresso)) {
                printf("\nVendedor: %s\n", no->venda.vendedor);
                printf("Matricula: %s\n\n", no->venda.matricula);
                *cabecalhoImpresso = 1;
            }

            imprimirVendaDeVendedor(no->venda);
            encontrou = 1;
        }

        if (auxImprimirVendasPorNome(no->dir, vendedor, cabecalhoImpresso)) {
            encontrou = 1;
        }
    }

    return encontrou;
}

int auxImprimirVendasPorMatricula(NoArv *no, char matricula[5], int *cabecalhoImpresso) {
    int encontrou = 0;

    if (no != NULL) {

        if (auxImprimirVendasPorMatricula(no->esq, matricula, cabecalhoImpresso)) {
            encontrou = 1;
        }

        if (strcmp(no->venda.matricula, matricula) == 0) {

            if (!(*cabecalhoImpresso)) {
                printf("\nVendedor: %s\n", no->venda.vendedor);
                printf("Matricula: %s\n\n", no->venda.matricula);
                *cabecalhoImpresso = 1;
            }

            imprimirVendaDeVendedor(no->venda);
            encontrou = 1;
        }

        if (auxImprimirVendasPorMatricula(no->dir, matricula, cabecalhoImpresso)) {
            encontrou = 1;
        }
    }

    return encontrou;
}

void RemoverVenda(Arv *arv) {
    int id;
    char confirma;
    int podeRemover = 1;

    printf("Digite o ID da venda que deseja remover: ");

    if (scanf("%d", &id) != 1) {
        while (getchar() != '\n');
        printf("Digite apenas numeros.\n");
        podeRemover = 0;
    } else {
        while (getchar() != '\n');
    }

    if (podeRemover) {
        if (id < 1000 || id > 9999) {
            printf("O ID deve estar entre 1000 e 9999.\n");
            podeRemover = 0;
        }
    }

    if (podeRemover) {
        if (!BuscarVenda(arv, id)) {
            printf("Venda com ID %d nao encontrada.\n", id);
            podeRemover = 0;
        }
    }

    if (podeRemover) {
        printf("Tem certeza que deseja remover a venda %d? (s/n): ", id);
        scanf(" %c", &confirma);

        if (confirma != 's' && confirma != 'S') {
            printf("Operacao cancelada pelo usuario.\n");
            podeRemover = 0;
        }
    }

    if (podeRemover) {
        RemoverVendaPorID(arv, id);
        printf("Venda com ID %d removida com sucesso.\n", id);
    }
}
