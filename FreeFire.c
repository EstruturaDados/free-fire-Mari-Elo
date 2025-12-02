//NIVEL AVENTUREIRO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- DEFINIÇÃO DAS ESTRUTURAS ---

// A Struct Item (O dado em si)
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// A Struct No (Para a Lista Encadeada)
typedef struct No {
    Item dado;
    struct No* proximo;
} No;

// Variáveis Globais para o VETOR
#define MAX_VETOR 10
Item vetorMochila[MAX_VETOR];
int qtdVetor = 0;

// Variável Global para a LISTA ENCADEADA (Ponteiro para o início)
No* cabecaLista = NULL;

// --- PROTÓTIPOS DAS FUNÇÕES ---
void limparBuffer();

// Funções do Vetor
void inserirVetor();
void removerVetor();
void listarVetor();
void buscarSequencialVetor();
void ordenarVetor(); // Bubble Sort
void buscarBinariaVetor();

// Funções da Lista Encadeada
void inserirLista();
void removerLista();
void listarLista();
void buscarSequencialLista();

// --- FUNÇÃO PRINCIPAL (MAIN) ---
int main() {
    int escolhaEstrutura = 0;
    int opcao = 0;

    do {
        printf("\n=== SISTEMA DE GESTAO DE INVENTARIO ===\n");
        printf("1. Usar VETOR (Permite Busca Binaria)\n");
        printf("2. Usar LISTA ENCADEADA (Dinamica)\n");
        printf("0. Sair\n");
        printf("Escolha a estrutura: ");
        scanf("%d", &escolhaEstrutura);
        limparBuffer();

        if (escolhaEstrutura == 0) break;

        if (escolhaEstrutura == 1) {
            // MENU VETOR
            do {
                printf("\n--- MODO VETOR (Itens: %d/%d) ---\n", qtdVetor, MAX_VETOR);
                printf("1. Inserir Item\n");
                printf("2. Remover Item\n");
                printf("3. Listar Itens\n");
                printf("4. Busca Sequencial\n");
                printf("5. Ordenar e Busca Binaria (Rapida)\n");
                printf("0. Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcao);
                limparBuffer();

                switch(opcao) {
                    case 1: inserirVetor(); break;
                    case 2: removerVetor(); break;
                    case 3: listarVetor(); break;
                    case 4: buscarSequencialVetor(); break;
                    case 5: 
                        ordenarVetor(); 
                        buscarBinariaVetor(); 
                        break;
                }
            } while (opcao != 0);
        } 
        else if (escolhaEstrutura == 2) {
            // MENU LISTA ENCADEADA
            do {
                printf("\n--- MODO LISTA ENCADEADA ---\n");
                printf("1. Inserir Item\n");
                printf("2. Remover Item\n");
                printf("3. Listar Itens\n");
                printf("4. Busca Sequencial\n");
                printf("0. Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcao);
                limparBuffer();

                switch(opcao) {
                    case 1: inserirLista(); break;
                    case 2: removerLista(); break;
                    case 3: listarLista(); break;
                    case 4: buscarSequencialLista(); break;
                }
            } while (opcao != 0);
        }

    } while (escolhaEstrutura != 0);

    return 0;
}

// --- IMPLEMENTAÇÃO: VETOR ---

void inserirVetor() {
    if (qtdVetor >= MAX_VETOR) {
        printf("Erro: Mochila (Vetor) cheia!\n");
        return;
    }
    printf("Nome: "); scanf("%[^\n]", vetorMochila[qtdVetor].nome); limparBuffer();
    printf("Tipo: "); scanf("%[^\n]", vetorMochila[qtdVetor].tipo); limparBuffer();
    printf("Qtd: "); scanf("%d", &vetorMochila[qtdVetor].quantidade); limparBuffer();
    qtdVetor++;
    printf("Item inserido no vetor.\n");
}

void removerVetor() {
    char nome[30];
    printf("Nome para remover: "); scanf("%[^\n]", nome); limparBuffer();
    
    for (int i = 0; i < qtdVetor; i++) {
        if (strcmp(vetorMochila[i].nome, nome) == 0) {
            // Deslocamento (Shift left)
            for (int j = i; j < qtdVetor - 1; j++) {
                vetorMochila[j] = vetorMochila[j+1];
            }
            qtdVetor--;
            printf("Item removido.\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

void listarVetor() {
    printf("\n[ Inventario Vetor ]\n");
    for(int i=0; i<qtdVetor; i++) {
        printf("%d. %s (%s) - Qtd: %d\n", i+1, vetorMochila[i].nome, vetorMochila[i].tipo, vetorMochila[i].quantidade);
    }
}

void buscarSequencialVetor() {
    char nome[30];
    int comparacoes = 0;
    printf("Busca Sequencial (Nome): "); scanf("%[^\n]", nome); limparBuffer();

    for(int i=0; i<qtdVetor; i++) {
        comparacoes++;
        if (strcmp(vetorMochila[i].nome, nome) == 0) {
            printf("ENCONTRADO: %s (Comparacoes: %d)\n", vetorMochila[i].nome, comparacoes);
            return;
        }
    }
    printf("Nao encontrado. (Comparacoes: %d)\n", comparacoes);
}

// Algoritmo Bubble Sort para ordenar por Nome
void ordenarVetor() {
    Item temp;
    for (int i = 0; i < qtdVetor - 1; i++) {
        for (int j = 0; j < qtdVetor - i - 1; j++) {
            // Se o nome atual for "maior" alfabeticamente que o proximo, troca
            if (strcmp(vetorMochila[j].nome, vetorMochila[j+1].nome) > 0) {
                temp = vetorMochila[j];
                vetorMochila[j] = vetorMochila[j+1];
                vetorMochila[j+1] = temp;
            }
        }
    }
    printf("\n[INFO] Vetor ordenado alfabeticamente.\n");
}

// Busca Binária (Requer vetor ordenado)
void buscarBinariaVetor() {
    char nome[30];
    printf("Busca Binaria (Nome): "); scanf("%[^\n]", nome); limparBuffer();
    
    int inicio = 0;
    int fim = qtdVetor - 1;
    int meio;
    int comparacoes = 0;
    int encontrado = 0;

    while (inicio <= fim) {
        comparacoes++;
        meio = (inicio + fim) / 2;
        
        int resultado = strcmp(vetorMochila[meio].nome, nome);

        if (resultado == 0) {
            printf("ENCONTRADO: %s no indice %d\n", vetorMochila[meio].nome, meio);
            encontrado = 1;
            break;
        } else if (resultado < 0) {
            inicio = meio + 1; // Procura na metade direita
        } else {
            fim = meio - 1; // Procura na metade esquerda
        }
    }

    printf("Total de Comparacoes na Busca Binaria: %d\n", comparacoes);
    if (!encontrado) printf("Item nao existe.\n");
}

// --- IMPLEMENTAÇÃO: LISTA ENCADEADA ---

void inserirLista() {
    // Aloca memoria dinamicamente para um novo nó
    No* novoNo = (No*)malloc(sizeof(No));
    
    printf("Nome: "); scanf("%[^\n]", novoNo->dado.nome); limparBuffer();
    printf("Tipo: "); scanf("%[^\n]", novoNo->dado.tipo); limparBuffer();
    printf("Qtd: "); scanf("%d", &novoNo->dado.quantidade); limparBuffer();
    novoNo->proximo = NULL;

    // Inserção no início (mais simples e rápido O(1))
    if (cabecaLista == NULL) {
        cabecaLista = novoNo;
    } else {
        novoNo->proximo = cabecaLista;
        cabecaLista = novoNo;
    }
    printf("Item inserido na lista.\n");
}

void removerLista() {
    char nome[30];
    printf("Nome para remover: "); scanf("%[^\n]", nome); limparBuffer();

    No* atual = cabecaLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dado.nome, nome) == 0) {
            // Achou o item
            if (anterior == NULL) {
                // É o primeiro da lista
                cabecaLista = atual->proximo;
            } else {
                // É um item do meio ou fim
                anterior->proximo = atual->proximo;
            }
            free(atual); // Libera a memória! Importante em listas.
            printf("Item removido da lista.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item nao encontrado na lista.\n");
}

void listarLista() {
    printf("\n[ Inventario Lista Encadeada ]\n");
    No* atual = cabecaLista;
    int i = 1;
    while (atual != NULL) {
        printf("%d. %s (%s) - Qtd: %d\n", i, atual->dado.nome, atual->dado.tipo, atual->dado.quantidade);
        atual = atual->proximo;
        i++;
    }
}

void buscarSequencialLista() {
    char nome[30];
    int comparacoes = 0;
    printf("Busca na Lista (Nome): "); scanf("%[^\n]", nome); limparBuffer();

    No* atual = cabecaLista;
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dado.nome, nome) == 0) {
            printf("ENCONTRADO: %s (Comparacoes: %d)\n", atual->dado.nome, comparacoes);
            return;
        }
        atual = atual->proximo;
    }
    printf("Nao encontrado. (Comparacoes: %d)\n", comparacoes);
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}