#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Requisitos Não Funcionais: Uso de constantes para Manutenibilidade
#define TAMANHO 10      // Tabuleiro 10x10
#define AGUA 0          // Posição de água (livre)
#define NAVIO 3         // Posição ocupada por navio
#define MAX_TENTATIVAS 50 // Limite de tentativas para posicionamento aleatório

// Função: Inicializa a matriz do tabuleiro com o valor AGUA (0)
void InicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função: Exibe o tabuleiro completo (Requisito Funcional: Exibição)
void ExibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    // Cabeçalho de colunas
    printf("\n  ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", j);
    }
    printf("\n");

    // Linhas
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", i); // Índice de linha
        for (int j = 0; j < TAMANHO; j++) {
            // Se NAVIO (3), exibe 'N'. Se AGUA (0), exibe 'O'.
            if (tabuleiro[i][j] == NAVIO) {
                printf("N ");
            } else {
                printf("O ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

/*
 * Função: Verifica se o navio pode ser posicionado nas coordenadas e direção escolhidas.
 * Requisito Não Funcional: Performance e Manutenibilidade - Lógica otimizada para diagonais.
 */
bool VerificarPosicao(int tabuleiro[TAMANHO][TAMANHO], int start_x, int start_y, int tamanho, int direcao) {
    int dx = 0; // Mudança na linha (delta x)
    int dy = 0; // Mudança na coluna (delta y)

    // Lógica para as 4 orientações (Horizontal, Vertical, 2x Diagonal)
    if (direcao == 0) { // Horizontal: direita
        dx = 0; dy = 1;
    } else if (direcao == 1) { // Vertical: baixo
        dx = 1; dy = 0;
    } else if (direcao == 2) { // Diagonal Crescente (baixo-direita)
        dx = 1; dy = 1;
    } else if (direcao == 3) { // Diagonal Decrescente (baixo-esquerda)
        dx = 1; dy = -1;
    } else {
        return false; // Direção inválida (segurança)
    }

    // Loop para checar cada parte do navio
    for (int i = 0; i < tamanho; i++) {
        int x = start_x + i * dx;
        int y = start_y + i * dy;

        // 1. Verificar Limites da Matriz
        if (x < 0 || x >= TAMANHO || y < 0 || y >= TAMANHO) {
            return false;
        }

        // 2. Verificar Sobreposição (se a posição já está ocupada)
        if (tabuleiro[x][y] != AGUA) {
            return false;
        }
    }

    return true; // Posição válida
}

// Função: Posiciona um navio no tabuleiro
void PosicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int tamanho, int direcao) {
    int start_x, start_y;
    int dx = 0;
    int dy = 0;
    bool posicionado = false;
    int tentativas = 0;

    // Gerar a lógica de deslocamento novamente para o posicionamento
    if (direcao == 0) { // Horizontal
        dx = 0; dy = 1;
    } else if (direcao == 1) { // Vertical
        dx = 1; dy = 0;
    } else if (direcao == 2) { // Diagonal Crescente
        dx = 1; dy = 1;
    } else if (direcao == 3) { // Diagonal Decrescente
        dx = 1; dy = -1;
    }

    // Loop de posicionamento aleatório
    while (!posicionado && tentativas < MAX_TENTATIVAS) {
        // Gera coordenadas aleatórias dentro do limite 0 a TAMANHO-1
        start_x = rand() % TAMANHO;
        start_y = rand() % TAMANHO;

        // Tenta verificar se a posição é válida
        if (VerificarPosicao(tabuleiro, start_x, start_y, tamanho, direcao)) {
            // Se for válida, coloca o navio na matriz
            for (int i = 0; i < tamanho; i++) {
                tabuleiro[start_x + i * dx][start_y + i * dy] = NAVIO;
            }
            posicionado = true;
        }
        tentativas++;
    }

    if (!posicionado) {
        printf("Erro: Não foi possível posicionar navio de tamanho %d (direcao %d) após %d tentativas.\n", tamanho, direcao, MAX_TENTATIVAS);
    }
}

// Função principal do Nível Aventureiro
void NivelAventureiro() {
    int tabuleiro[TAMANHO][TAMANHO];
    
    // Seed para números aleatórios (para o posicionamento ser diferente a cada vez)
    srand(time(NULL));

    InicializarTabuleiro(tabuleiro);
    printf("--- Batalha Naval: Nível Aventureiro ---\n");
    printf("Posicionando 4 navios no tabuleiro 10x10 (N = Navio, O = Água).\n");
    
    // Configuração dos 4 Navios (Requisito Funcional: Posicionamento de Quatro Navios)
    // Direções: 0=Horizontal, 1=Vertical, 2=Diag. Crescente, 3=Diag. Decrescente
    
    // Navio 1: Horizontal (Tamanho 3)
    PosicionarNavio(tabuleiro, 3, 0); 

    // Navio 2: Vertical (Tamanho 2)
    PosicionarNavio(tabuleiro, 2, 1);
    
    // Navio 3: Diagonal (Tamanho 3 - Diag. Crescente)
    PosicionarNavio(tabuleiro, 3, 2); 

    // Navio 4: Diagonal (Tamanho 2 - Diag. Decrescente)
    PosicionarNavio(tabuleiro, 2, 3);
    
    // Exibe o Tabuleiro completo com os navios posicionados
    printf("\nTabuleiro Aventureiro (Completo):\n");
    ExibirTabuleiro(tabuleiro);
    
    // *******************************************************************
    // LÓGICA DE ATAQUE SIMPLES (continuação do Nível Novato)
    // Opcional, mas aqui está a base para o ataque e o fim do jogo.
    // *******************************************************************
    
    int acertos_necessarios = 3 + 2 + 3 + 2; // Total de 10 acertos
    int acertos_feitos = 0;
    int x_tiro, y_tiro;

    printf("\n--- Início do Jogo ---\n");
    printf("Tente acertar todos os 10 pontos de navio!\n");

    while (acertos_feitos < acertos_necessarios) {
        printf("Tiro #%d. Digite as coordenadas (Linha Coluna, 0-9): ", acertos_feitos + 1);
        // Requisito Funcional: Entrada de Dados (simulação interativa)
        if (scanf("%d %d", &x_tiro, &y_tiro) != 2) {
            printf("Entrada inválida. Tente novamente.\n");
            // Limpa o buffer de entrada em caso de erro
            while (getchar() != '\n'); 
            continue;
        }

        // Validação de Limites
        if (x_tiro < 0 || x_tiro >= TAMANHO || y_tiro < 0 || y_tiro >= TAMANHO) {
            printf("Coordenadas fora do limite (0 a 9).\n");
            continue;
        }
        
        // Lógica de Tiro
        if (tabuleiro[x_tiro][y_tiro] == NAVIO) {
            printf(">> ACERTOU na posição (%d, %d)!\n", x_tiro, y_tiro);
            tabuleiro[x_tiro][y_tiro] = 9; // Marca como ACERTO (usando 9 para evitar conflito com 3)
            acertos_feitos++;
        } else if (tabuleiro[x_tiro][y_tiro] == 9) {
            printf(">> Você já atirou aqui e acertou!\n");
        } else if (tabuleiro[x_tiro][y_tiro] == 1) {
            printf(">> Você já atirou aqui e errou (Água)!\n");
        } else { // AGUA (0)
            printf(">> ÁGUA na posição (%d, %d)!\n", x_tiro, y_tiro);
            tabuleiro[x_tiro][y_tiro] = 1; // Marca como ERRO (usando 1 para evitar conflito com 0)
        }
    }

    printf("\n*** PARABÉNS! Você afundou todos os %d pontos de navio! ***\n", acertos_necessarios);
}

int main() {
    NivelAventureiro();
    return 0;
}
