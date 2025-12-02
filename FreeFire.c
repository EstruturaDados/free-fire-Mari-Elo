//NIVEL NIVEL MESTRE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Necessário para medir o tempo (clock)

// --- 1. DEFINIÇÃO DAS ESTRUTURAS ---
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 (Baixa) a 10 (Alta)
} Componente;

// Variáveis Globais
#define MAX_COMPONENTES 20
Componente lista[MAX_COMPONENTES];
int qtdAtual = 0;

// Variável de controle para saber se está ordenado por nome (necessário para busca binária)
int ordenadoPorNome = 0; 

// --- PROTÓTIPOS ---
void limparBuffer();
void removerQuebraLinha(char *str);
void cadastrarComponente();
void listarComponentes();
void cargaInicial(); // Dados de teste

// Algoritmos de Ordenação
void bubbleSortNome();
void insertionSortTipo();
void selectionSortPrioridade();

// Busca
void buscaBinariaNome();

// --- FUNÇÃO PRINCIPAL ---
int main() {
    int opcao;
    
    // Carrega alguns dados para teste imediato
    cargaInicial();

    do {
        printf("\n=== SISTEMA DE TORRE DE RESGATE (Itens: %d/%d) ===\n", qtdAtual, MAX_COMPONENTES);
        printf("1. Cadastrar Novo Componente\n");
        printf("2. Listar Componentes\n");
        printf("3. Ordenar por NOME (Bubble Sort)\n");
        printf("4. Ordenar por TIPO (Insertion Sort)\n");
        printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6. Buscar Componente (Busca Binaria - Requer Nome Ordenado)\n");
        printf("0. Sair\n");
        printf("Escolha sua estrategia: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1: cadastrarComponente(); break;
            case 2: listarComponentes(); break;
            case 3: bubbleSortNome(); break;
            case 4: insertionSortTipo(); break;
            case 5: selectionSortPrioridade(); break;
            case 6: buscaBinariaNome(); break;
            case 0: printf("Encerrando sistema... Boa sorte na fuga!\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// Utilitários
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removerQuebraLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void cargaInicial() {
    // Adiciona alguns itens automaticamente para testar os algoritmos
    if(qtdAtual + 5 <= MAX_COMPONENTES) {
        strcpy(lista[0].nome, "Gerador de Pulso"); strcpy(lista[0].tipo, "Energia"); lista[0].prioridade = 10;
        strcpy(lista[1].nome, "Antena Longo Alcance"); strcpy(lista[1].tipo, "Comunicacao"); lista[1].prioridade = 8;
        strcpy(lista[2].nome, "Cabo de Aco"); strcpy(lista[2].tipo, "Suporte"); lista[2].prioridade = 5;
        strcpy(lista[3].nome, "Chip Processador"); strcpy(lista[3].tipo, "Controle"); lista[3].prioridade = 9;
        strcpy(lista[4].nome, "Base de Titanio"); strcpy(lista[4].tipo, "Suporte"); lista[4].prioridade = 7;
        qtdAtual = 5;
    }
}

void cadastrarComponente() {
    if (qtdAtual >= MAX_COMPONENTES) {
        printf("Erro: Capacidade maxima de componentes atingida!\n");
        return;
    }
    printf("Nome do Componente: "); 
    fgets(lista[qtdAtual].nome, 30, stdin); 
    removerQuebraLinha(lista[qtdAtual].nome);

    printf("Tipo (Ex: controle, suporte): "); 
    fgets(lista[qtdAtual].tipo, 20, stdin); 
    removerQuebraLinha(lista[qtdAtual].tipo);

    printf("Prioridade (1-10): "); 
    scanf("%d", &lista[qtdAtual].prioridade);
    limparBuffer();

    qtdAtual++;
    ordenadoPorNome = 0; // Ao inserir, a lista pode perder a ordenação
    printf("Componente cadastrado com sucesso!\n");
}

void listarComponentes() {
    printf("\n--- Lista de Componentes ---\n");
    printf("%-25s | %-15s | %s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < qtdAtual; i++) {
        printf("%-25s | %-15s | %d\n", lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
}

// --- ALGORITMOS DE ORDENAÇÃO ---

// 1. Bubble Sort -> Ordenar por NOME
void bubbleSortNome() {
    clock_t inicio = clock(); // Inicia contagem de tempo
    long comparacoes = 0;
    Componente temp;
    
    printf("\n[Processando] Executando Bubble Sort por Nome...\n");

    for (int i = 0; i < qtdAtual - 1; i++) {
        for (int j = 0; j < qtdAtual - i - 1; j++) {
            comparacoes++;
            // strcmp > 0 significa que a string da esquerda é "maior" alfabeticamente
            if (strcmp(lista[j].nome, lista[j+1].nome) > 0) {
                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }

    clock_t fim = clock(); // Fim da contagem
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    ordenadoPorNome = 1; // Flag ativada para permitir busca binária
    printf("Ordenacao concluida!\n");
    printf("Comparacoes: %ld | Tempo: %f segundos\n", comparacoes, tempoGasto);
    listarComponentes();
}

// 2. Insertion Sort -> Ordenar por TIPO
void insertionSortTipo() {
    clock_t inicio = clock();
    long comparacoes = 0;
    Componente chave;
    int j;

    printf("\n[Processando] Executando Insertion Sort por Tipo...\n");

    for (int i = 1; i < qtdAtual; i++) {
        chave = lista[i];
        j = i - 1;

        // Move os elementos que são "maiores" que a chave para frente
        while (j >= 0) {
            comparacoes++;
            if (strcmp(lista[j].tipo, chave.tipo) > 0) {
                lista[j + 1] = lista[j];
                j = j - 1;
            } else {
                break; 
            }
        }
        lista[j + 1] = chave;
    }

    clock_t fim = clock();
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    ordenadoPorNome = 0; // Perdeu a ordenação por nome
    printf("Ordenacao concluida!\n");
    printf("Comparacoes: %ld | Tempo: %f segundos\n", comparacoes, tempoGasto);
    listarComponentes();
}

// 3. Selection Sort -> Ordenar por PRIORIDADE
void selectionSortPrioridade() {
    clock_t inicio = clock();
    long comparacoes = 0;
    int minIndex;
    Componente temp;

    printf("\n[Processando] Executando Selection Sort por Prioridade...\n");

    for (int i = 0; i < qtdAtual - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < qtdAtual; j++) {
            comparacoes++;
            // Procura a menor prioridade (ordem crescente)
            // Para ordem decrescente (maior prioridade primeiro), mude para <
            if (lista[j].prioridade < lista[minIndex].prioridade) {
                minIndex = j;
            }
        }
        // Troca
        if (minIndex != i) {
            temp = lista[i];
            lista[i] = lista[minIndex];
            lista[minIndex] = temp;
        }
    }

    clock_t fim = clock();
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    ordenadoPorNome = 0; 
    printf("Ordenacao concluida!\n");
    printf("Comparacoes: %ld | Tempo: %f segundos\n", comparacoes, tempoGasto);
    listarComponentes();
}

// --- BUSCA BINÁRIA ---
void buscaBinariaNome() {
    if (!ordenadoPorNome) {
        printf("\n[ALERTA] A lista precisa estar ordenada por NOME para usar Busca Binaria.\n");
        printf("Por favor, execute a opcao 3 (Bubble Sort) primeiro.\n");
        return;
    }

    char chave[30];
    printf("Digite o nome do componente-chave para a montagem: ");
    fgets(chave, 30, stdin);
    removerQuebraLinha(chave);

    clock_t inicio = clock();
    int esquerda = 0;
    int direita = qtdAtual - 1;
    int meio;
    int comparacoes = 0;
    int encontrado = 0;

    printf("\n[Busca] Procurando '%s'...\n", chave);

    while (esquerda <= direita) {
        comparacoes++;
        meio = (esquerda + direita) / 2;
        
        int resultado = strcmp(lista[meio].nome, chave);

        if (resultado == 0) {
            printf("\n>>> SUCESSO! Componente ENCONTRADO <<<\n");
            printf("Posicao: %d | Nome: %s | Tipo: %s | Prioridade: %d\n", 
                   meio+1, lista[meio].nome, lista[meio].tipo, lista[meio].prioridade);
            encontrado = 1;
            break;
        } 
        else if (resultado < 0) {
            esquerda = meio + 1; // Busca na metade direita
        } 
        else {
            direita = meio - 1; // Busca na metade esquerda
        }
    }

    clock_t fim = clock();
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    if (!encontrado) {
        printf("\n[FALHA] Componente nao encontrado na torre.\n");
    }
    printf("Comparacoes na busca: %d | Tempo: %f segundos\n", comparacoes, tempoGasto);
}