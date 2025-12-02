//NIVEL NOVATO
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição de constantes para facilitar a manutenção
#define MAX_ITENS 10

// --- 1. Definição da Struct (O Molde do Item) ---
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// --- Variáveis Globais (A Mochila) ---
// Criamos a mochila com capacidade máxima definida
Item mochila[MAX_ITENS];
// Variável para controlar quantos itens estão ocupados atualmente
int totalItens = 0;

// --- Protótipos das Funções ---
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void limparBuffer(); // Função auxiliar para evitar erros de leitura

// --- Função Principal (Main) ---
int main() {
    int opcao;

    do {
        // Menu de Usabilidade Clara
        printf("\n=== MOCHILA DE SOBREVIVENCIA (Itens: %d/%d) ===\n", totalItens, MAX_ITENS);
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Inventario\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o "Enter" que sobra no teclado

        switch(opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("A fechar a mochila... Boa sorte no jogo!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

// 1. Inserir Item
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n[ALERTA] Mochila cheia! Voce precisa remover algo antes.\n");
        return;
    }

    printf("\n--- Novo Loot ---\n");
    
    printf("Nome do item (ex: AK-47): ");
    // O scanf com %[^\n] lê a linha inteira até o Enter, permitindo espaços
    scanf("%[^\n]", mochila[totalItens].nome);
    limparBuffer();

    printf("Tipo (ex: Arma, Municao, Cura): ");
    scanf("%[^\n]", mochila[totalItens].tipo);
    limparBuffer();

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    limparBuffer();

    totalItens++; // Aumentamos o contador de itens na mochila
    printf("[SUCESSO] Item guardado na mochila!\n");
}

// 2. Remover Item
void removerItem() {
    char nomeParaRemover[30];
    int encontrado = 0; // 0 = falso, 1 = verdadeiro

    if (totalItens == 0) {
        printf("\n[AVISO] A mochila esta vazia.\n");
        return;
    }

    printf("\nNome do item para remover: ");
    scanf("%[^\n]", nomeParaRemover);
    limparBuffer();

    // Busca sequencial para encontrar o item
    for (int i = 0; i < totalItens; i++) {
        // strcmp compara strings. Se for 0, são iguais.
        if (strcmp(mochila[i].nome, nomeParaRemover) == 0) {
            
            // Lógica de remoção: Deslocar itens da frente para trás
            // Exemplo: Se removo o item 1, o item 2 vira o 1, o 3 vira o 2...
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            
            totalItens--; // Diminuimos o total de itens
            encontrado = 1;
            printf("[SUCESSO] %s foi jogado fora.\n", nomeParaRemover);
            break; // Paramos o loop pois já removemos
        }
    }

    if (!encontrado) {
        printf("[ERRO] Item nao encontrado na mochila.\n");
    }
}

// 3. Listar Itens
void listarItens() {
    printf("\n--- Conteudo da Mochila ---\n");
    if (totalItens == 0) {
        printf(" (Vazia) \n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("Slot %d: %s | Tipo: %s | Qtd: %d\n", 
               i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("---------------------------\n");
}

// 4. Buscar Item (Busca Sequencial)
void buscarItem() {
    char nomeBusca[30];
    int encontrado = 0;

    printf("\nQual item procura? ");
    scanf("%[^\n]", nomeBusca);
    limparBuffer();

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n[ENCONTRADO] Detalhes do Item:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break; // Item achado, não precisa continuar procurando
        }
    }

    if (!encontrado) {
        printf("[INFO] Voce nao possui esse item.\n");
    }
}

// Função auxiliar para limpar o buffer do teclado (Windows/Linux compativel)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

