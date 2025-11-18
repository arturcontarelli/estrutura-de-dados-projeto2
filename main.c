#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ABB.h"

// === Protótipos de funções principais ===
void InserirNovaVenda(Arv *arv);  
void ListarVendas(Arv *arv);
void BuscarVendedor();
void ListarVendaPorValor(Arv *A, float valorBusca, int maiorMenor);
void ExibirEstatisticas(Arv *arv);
void RemoverVenda();

// === Protótipos de funções auxiliares ===
int GerarID();
int IDExiste(Arv *arv, int id);
int GerarIDUnico(Arv *arv);
int SelecionarImpressao();

// Protótipos para matrícula
void GerarMatricula(char matricula[5]);
void GerarMatriculaUnica(Arv *arv, char matricula[5]);
int MatriculaExiste(Arv *arv, char matricula[5]);
int auxVerificarMatricula(NoArv* no, char matricula[5]);

// Protótipos para vendedores
int ProcessarVendedorExistente(Arv *arv, char matricula[5], char nomeVendedor[51]);
int ProcessarNovoVendedor(Arv *arv, char matricula[5], char nomeVendedor[51]);
Venda CriarVenda(char matricula[5], char nomeVendedor[51], Arv *arv);  
void BuscarDadosVendedorPorMatricula(Arv *arv, char matricula[5], char nomeEncontrado[51]);
void auxBuscarDadosVendedor(NoArv* no, char matricula[5], char nomeEncontrado[51], int* encontrou);


// === Função main ===
int main() {
    srand(123);

    menu();

    return 0;
}

// === Função para chamar o menu ===

void menu() {
    Arv* arvore = CriaArvore(); // Criar árvore principal
    int opcao;
    int entradaValida;

    if (arvore == NULL) {
        printf("ERRO: Falha ao inicializar o sistema!\n");
        return;
    }

    printf("\n SISTEMA DE VENDAS INICIALIZADO COM SUCESSO!\n");

    do {
        system("cls");   

        printf("\n=============================================\n");
        printf(" ||           SISTEMA DE VENDAS               || \n");
        printf("  =============================================\n");
        printf("\t > 1.  Inserir nova venda <\n");
        printf("\t > 2.  Listar todas as vendas <\n");
        printf("\t > 3.  Buscar vendas de um vendedor <\n");
        printf("\t > 4.  Filtrar vendas por valor <\n");
        printf("\t > 5.  Exibir estatísticas <\n");
        printf("\t > 6.   Remover uma venda <\n");
        printf("\t > 7.  Finalizar sistema <\n");
        printf("=============================================\n");
        printf("👉 Selecione uma opção (1-7): ");

        // Validação de entrada 
        entradaValida = scanf("%d", &opcao);
        
        // Limpar buffer em caso de entrada inválida
        while (getchar() != '\n');

        if (!entradaValida) {
            printf("\n ERRO: Digite apenas números!\n");
            printf(" Pressione ENTER para continuar...");
            getchar();
        }

        printf("\n"); 

        switch (opcao) {
            case 1: {
                printf(" Carregando inserção de venda...\n");
                InserirNovaVenda(arvore);
                break;
            }

            case 2: {
                if (VaziaArvore(arvore)) {
                    printf(" Nenhuma venda cadastrada ainda.\n");
                } else {
                    printf(" Carregando lista de vendas...\n");
                    ListarVendas(arvore);
                }
                break;
            }

            case 3: {
                if (VaziaArvore(arvore)) {
                    printf(" Nenhuma venda cadastrada para buscar.\n");
                } else {
                    printf(" Carregando busca por vendedor...\n");
                    BuscarVendedor(arvore);
                }
                break;
            }

            case 4: {
                if (VaziaArvore(arvore)) {
                    printf(" Nenhuma venda cadastrada para filtrar.\n");
                } else {
                    float valor;
                    int tipoFiltro;
                    
                    printf(" === FILTRAR VENDAS POR VALOR ===\n");
                    printf("Digite o valor de referência: R$ ");
                    
                    if (scanf("%f", &valor) != 1 || valor < 0) {
                        while (getchar() != '\n'); // Limpar buffer
                        printf(" Valor inválido! Use números positivos.\n");
                        break;
                    }
                    
                    printf("\nTipo de filtro:\n");
                    printf("1 - Vendas ACIMA de R$ %.2f\n", valor);
                    printf("2 - Vendas ABAIXO de R$ %.2f\n", valor);
                    printf("Escolha (1 ou 2): ");
                    scanf("%d", &tipoFiltro);
                    
                    if (tipoFiltro != 1 && tipoFiltro != 2) {
                        while (getchar() != '\n');
                        printf(" Opção inválida! Escolha 1 ou 2.\n");
                        break;
                    }
                    
                    printf("\n Buscando vendas...\n");
                    ListarVendaPorValor(arvore, valor, tipoFiltro);
                }
                break;
            }

            case 5: {
                if (VaziaArvore(arvore)) {
                    printf(" Nenhuma venda cadastrada para gerar estatísticas.\n");
                } else {
                    printf(" Calculando estatísticas...\n");
                    ExibirEstatisticas(arvore);
                }
                break;
            }

            case 6: {
                if (VaziaArvore(arvore)) {
                    printf(" Nenhuma venda cadastrada para remover.\n");
                } else {
                    printf(" Carregando remoção de venda...\n");
                    RemoverVenda(arvore);
                }
                break;
            }

            case 7: {
                printf(" Finalizando sistema...\n");
                printf(" Liberando memória...\n");
                LiberarArvore(arvore);
                break;
            }

            default: {
                printf(" OPÇÃO INVÁLIDA!\n");
                printf(" Escolha um número entre 1 e 7.\n");
                break;
            }
        }

        // Pausa para o usuário ler as mensagens (exceto na saída)
        if (opcao != 7) {
            printf("\n Pressione ENTER para voltar ao menu...");
            getchar();
        }

    } while (opcao != 7);
}


// === Funções Auxiliares ===



// == gerar ID aleatório ==

int GerarID(){
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
    int numero = 100 + rand() % 900;  // Ex: numero = 456
    
    // Separar cada dígito do número
    int centena = (numero / 100) % 10;  // 456/100 = 4, 4%10 = 4
    int dezena = (numero / 10) % 10;    // 456/10 = 45, 45%10 = 5  
    int unidade = numero % 10;          // 456%10 = 6
    
    // Montar a matrícula
    // compilador não funciona com itoa pois isso transfrorma int em string, nao em caractere
    // então fiz manualmente para garantir que funcione, somando o 0 ASCII ao valor inteiro
    // Exemplo: '0' = 48 em ASCII, 4 + 48 = 52 que é '4' em ASCII
    matricula[0] = 'V';                 
    matricula[1] = (char)(centena + (int)'0');       // 4 + '0' = '4'
    matricula[2] = (char)(dezena + (int)'0');        // 5 + '0' = '5'
    matricula[3] = (char)(unidade + (int)'0');       // 6 + '0' = '6'
    matricula[4] = '\0';                // Terminador de string
    
    // Resultado: "V456"
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
int auxVerificarMatricula(NoArv* no, char matricula[5]) {
    if (no == NULL) {
        return 0; // Não encontrou
    }
    
    if (strcmp(no->venda.matricula, matricula) == 0) {
        return 1; // Encontrou
    }
    
    // Verifica se encontrou em alguma das subárvores
    return auxVerificarMatricula(no->esq, matricula) || auxVerificarMatricula(no->dir, matricula);
}

// == Gerar matrícula única ==
void GerarMatriculaUnica(Arv *arv, char matricula[5]) {
    int tentativas = 0;
    const int MAX_TENTATIVAS = 800; // Limite de tentativas
    int continuar = 1;
    
    do {
        GerarMatricula(matricula);
        tentativas++;
        
        if (tentativas >= MAX_TENTATIVAS) {
            printf("ERRO: Não foi possível gerar matrícula única!\n");
            // Matrícula de erro
            matricula[0] = 'E'; //o Primeiro caractere será E ao inves de V, indicando o erro
            matricula[1] = 'R';
            matricula[2] = 'R';
            matricula[3] = 'O';
            matricula[4] = '\0';
            continuar = 0;
        }
        
    } while (continuar && MatriculaExiste(arv, matricula));
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
    }
    else {
        // Criar e inserir venda
        Venda novaVenda = CriarVenda(matricula, nomeVendedor, arv);
        
        if (InserirVenda(arv, novaVenda)) {
            printf("\nVENDA INSERIDA COM SUCESSO!\n");
            ImprimirVenda(novaVenda);
        } else {
            printf("\nERRO: Falha ao inserir venda!\n");
        }
    }
}

// 1.1 Auxiliar - Processar vendedor existente
int ProcessarVendedorExistente(Arv *arv, char matricula[5], char nomeVendedor[51]) {
    int confirma;
    char nomeExistente[51];
    
    do{
    printf("Digite a matrícula do vendedor (formato V000): ");
    scanf("%s", matricula);

     }while(matricula[0] != 'V');
    
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

// 1.4 Auxiliar recursivo para buscar dados do vendedor
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


void BuscarVendedor() {
    printf("\n[buscarVendedor] Ainda nao implementada.\n");
}

// 4. Listar vendas acima ou abaixo de um valor
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
// 4.1 Auxiliares para listar vendas por valor
void auxPrintVendasMaior(NoArv *no, float valorBusca){
    if(no ->dir != NULL)auxPrintVendasMaior(no -> dir, valorBusca);
    if(no -> venda.valorTransacao > valorBusca){
        ImprimirVenda(no ->venda);
    }
    if(no ->esq != NULL) auxPrintVendasMaior(no -> esq, valorBusca);
}

// 4.2 Auxiliares para listar vendas por valor
void auxPrintVendasMenor(NoArv *no, float valorBusca){
    if(no ->dir != NULL)auxPrintVendasMenor(no -> dir, valorBusca);
    if(no -> venda.valorTransacao < valorBusca){
        ImprimirVenda(no ->venda);
    }
    if(no ->esq != NULL) auxPrintVendasMenor(no -> esq, valorBusca);
}


// 5. Exibir estatísticas
void ExibirEstatisticas(Arv *arv) {
    int qnt = qntVendas(arv->raiz);
    float somaFaturamento = somaVendas(arv->raiz);
    char resposta;

    printf("Estatísticas:\n");
    printf("Quantidade Total de Vendas: %d\n", qnt);
    printf("Soma Total das Vendas: %.2f\n", somaFaturamento);

    printf("Deseja verificar o número de vendas de um vendedor (s/n)? ");
    scanf(" %c", &resposta); // espaço antes de %c para ignorar \n pendente

    if (resposta == 'S' || resposta == 's') {
        char vendedor[51];

        printf("\nDigite o nome do vendedor: ");
        getchar(); // limpa o \n deixado no buffer (por segurança)
        fgets(vendedor, sizeof(vendedor), stdin);
        vendedor[strcspn(vendedor, "\n")] = '\0'; // remove o \n do final

        int vendasVendedor = buscarVendas(arv->raiz, vendedor);
        printf("\nO vendedor %s realizou %d venda(s).\n", vendedor, vendasVendedor);
    }

    // se não digitar 's', apenas encerra
}

void RemoverVenda() {
    printf("\n[removerVenda] Ainda nao implementada.\n");
}


