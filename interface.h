#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
    #define CLEAR "cls"
    #define PAUSE system("pause")
#else
    #include <unistd.h>
    #include <locale.h>
    #define CLEAR "clear"
    #define PAUSE printf("Pressione Enter para continuar..."); getchar()
#endif


#include "listade.h" // Inclui a estrutura de lista para poder manipular a lista de cartas.

// --- Códigos de Cor ANSI para o Terminal ---

//Cores de letras
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BLACK   "\033[30m"

//definições da mesa
#define BORDER_CHAR     "═"
#define COR_BORDA       "\033[38;5;94m"
#define JOGADOR_ATIVO   "\033[1;97m"     // Branco negrito
#define JOGADOR_INATIVO "\033[0;37m"     // Cinza
#define ICONE_ATIVO     "🂠"
#define ICONE_INATIVO   "  "

//Cores de fundo
#define BACK_WHITE      "\033[47m"
#define BACK_DARK_GREEN "\033[48;5;22m"
// Sintaxe: \033[<cor_texto>;<cor_fundo>m
#define BLACK_ON_WHITE "\033[30;47m" // Texto Preto, Fundo Branco
#define RED_ON_WHITE   "\033[31;47m" // Texto Vermelho, Fundo Branco

//Cores das cartas
#define CARD_RED    "\033[38;5;196m"
#define CARD_BLACK  "\033[38;5;16m"
#define CARD_BG     "\033[48;5;231m"

void limparTela() {
    system(CLEAR);
}


// Converte o nome de um naipe (ex: "Copas") para seu símbolo gráfico (ex: ♥).
// Usa códigos UTF-8, que funcionarão corretamente após a mudança no main.c
static const char* obter_simbolo_naipe(const char* naipe) {
    if (strcmp(naipe, "Copas") == 0) return "♥";
    if (strcmp(naipe, "Ouros") == 0) return "♦";
    if (strcmp(naipe, "Espadas") == 0) return "♠";
    if (strcmp(naipe, "Paus") == 0) return "♣";
    return "?"; // Retorna "?" se o naipe for desconhecido.
}

// --- FUNÇÃO MODIFICADA PARA DESENHAR CARTAS COM CORES ---
static void desenhar_cartas(tp_listad *lista, const char* titulo) {
    if (!lista || listad_vazia(lista)) {
        if (titulo) printf("\n--- %s ---\n(Vazio)\n", titulo);
        return;
    }

    if (titulo) printf("\n--- %s ---\n", titulo);

    int num_cartas = 0;
    tp_no_lista* nos_cartas[10];
    tp_no_lista* atu = lista->ini;
    while(atu != NULL && num_cartas < 10) {
        nos_cartas[num_cartas++] = atu;
        atu = atu->prox;
    }

    // Arrays para guardar as cores de cada carta
    const char* cores_cartas[10];
    for (int i = 0; i < num_cartas; i++) {
        const char* naipe = nos_cartas[i]->info.naipe;
        if (strcmp(naipe, "Copas") == 0 || strcmp(naipe, "Ouros") == 0) {
            cores_cartas[i] = RED_ON_WHITE; // Define a cor para vermelho sobre branco
        } else {
            cores_cartas[i] = BLACK_ON_WHITE; // Define a cor para preto sobre branco
        }
    }

    // O desenho é feito linha por linha.
    // A principal modificação é imprimir o espaço entre as cartas APÓS resetar a cor.

    // Linha 1: Topo das cartas
    for (int i = 0; i < num_cartas; i++) {
        printf("%s .-------. %s", cores_cartas[i], RESET);
        printf(" "); // Espaço entre as cartas com fundo padrão
    }
    printf("\n");

    // Linha 2: Valor no canto superior
    for (int i = 0; i < num_cartas; i++) {
        const char* valor = nos_cartas[i]->info.valor;
        if (strcmp(valor, "10") == 0) {
            printf("%s |%s     | %s", cores_cartas[i], valor, RESET);
        } else {
            printf("%s |%-2s     | %s", cores_cartas[i], valor, RESET);
        }
        printf(" "); // Espaço entre as cartas com fundo padrão
    }
    printf("\n");

    // Linha 3: Espaço em branco
    for (int i = 0; i < num_cartas; i++) {
        printf("%s |       | %s", cores_cartas[i], RESET);
        printf(" "); // Espaço entre as cartas com fundo padrão
    }
    printf("\n");

    // Linha 4: Símbolo do naipe no centro
    for (int i = 0; i < num_cartas; i++) {
        const char* simbolo = obter_simbolo_naipe(nos_cartas[i]->info.naipe);
        printf("%s |   %s   | %s", cores_cartas[i], simbolo, RESET);
        printf(" "); // Espaço entre as cartas com fundo padrão
    }
    printf("\n");

    // Linha 5: Espaço em branco
    for (int i = 0; i < num_cartas; i++) {
        printf("%s |       | %s", cores_cartas[i], RESET);
        printf(" "); // Espaço entre as cartas com fundo padrão
    }
    printf("\n");
    
    // Linha 6: Valor no canto inferior
    for (int i = 0; i < num_cartas; i++) {
        const char* valor = nos_cartas[i]->info.valor;
        if (strcmp(valor, "10") == 0) {
            printf("%s |     %s| %s", cores_cartas[i], valor, RESET);
        } else {
            printf("%s |     %-2s| %s", cores_cartas[i], valor, RESET);
        }
        printf(" "); // Espaço entre as cartas com fundo padrão
    }
    printf("\n");

    // Linha 7: Base das cartas
    for (int i = 0; i < num_cartas; i++) {
        printf("%s '-------' %s", cores_cartas[i], RESET);
        printf(" "); // Espaço entre as cartas com fundo padrão
    }
    printf("\n");
}

//função para apresentar o menu principal do jogo
void mostrarMenu(){
    limparTela();

    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #else
        setlocale(LC_ALL, "");
    #endif
    printf("     ");
    printf(BACK_WHITE BOLD BLACK"╔═════════════════════════════════════════╗\n");
    printf(RESET"     ");
    printf(BACK_WHITE BOLD BLACK"║    ____   ___   _  __  _____  ____      ║\n");
    printf(RESET"     ");
    printf(BACK_WHITE BOLD BLACK"║   |  _ \\ / _ \\ | |/ / | ____||  _ \\     ║\n");
    printf(RESET"     ");
    printf(BACK_WHITE BOLD BLACK"║   | |_) | | | || ' /  |  _|  | |_) |    ║\n");
    printf(RESET"     ");
    printf(BACK_WHITE BOLD BLACK"║   |  __/| |_| || . \\  | |___ |  _ <     ║\n");
    printf(RESET"     ");
    printf(BACK_WHITE BOLD BLACK"║   |_|    \\___/ |_|\\_\\ |_____||_| \\_\\    ║\n");
    printf(RESET"     ");
    printf(BACK_WHITE BOLD BLACK"║                                         ║\n");
    printf(RESET"     ");
    printf(BACK_WHITE BOLD BLACK"║  ♠ ♣ "RED"♥ ♦   "BLACK"♣ "RED"♦ "BLACK"♠ "RED"♥   ♦ "BLACK"♠ ♣ "RED"♥   ♥ ♦ "BLACK"♠ ♣  ║\n");
    printf(RESET"     ");
    printf(BACK_WHITE BOLD BLACK"╚═════════════════════════════════════════╝\n" RESET);
    printf(RESET"     ");
    printf("\n");
    printf("=============== POKER TEXAS HOLD'EM ===============\n");
}

void mostraMesa(tp_listad *lista, const char* titulo) {
    // Configura a codificação do console para suportar caracteres UTF-8
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #else
        setlocale(LC_ALL, "");
    #endif

    // --- ETAPA 1: Coletar informações das cartas e calcular dimensões ---

    int num_cartas = 0;
    tp_no_lista* nos_cartas[10]; // Suporta até 10 cartas
    const char* cores_cartas[10];

    // Se uma lista de cartas foi fornecida, processa-a
    if (lista != NULL && !listad_vazia(lista)) {
        tp_no_lista* atu = lista->ini;
        while(atu != NULL && num_cartas < 10) {
            // Guarda o nó da carta
            nos_cartas[num_cartas] = atu;
            
            // Determina a cor da carta (vermelho ou preto)
            const char* naipe = atu->info.naipe;
            if (strcmp(naipe, "Copas") == 0 || strcmp(naipe, "Ouros") == 0) {
                cores_cartas[num_cartas] = RED_ON_WHITE;
            } else {
                cores_cartas[num_cartas] = BLACK_ON_WHITE;
            }
            
            num_cartas++;
            atu = atu->prox;
        }
    }

    // Define as dimensões da mesa. A largura é dinâmica.
    const int altura = 13; // Altura fixa, suficiente para a carta (7 linhas) e bordas.
    int largura;
    
    if (num_cartas > 0) {
        // Largura de 1 carta = 11. Espaço entre cartas = 2. Padding lateral = 2 de cada lado.
        largura = (num_cartas * 11) + (num_cartas > 1 ? (num_cartas - 1) * 2 : 0) + 4;
    } else {
        largura = 50; // Largura padrão se não houver cartas.
    }

    // Calcula a posição inicial para desenhar as cartas para centralizá-las
    const int altura_carta = 7;
    int linha_inicio_cartas = (altura - altura_carta) / 2;
    int padding_horizontal = (num_cartas > 0) ? 2 : 0;


    // --- ETAPA 2: Desenhar a mesa e as cartas ---

    // Exibe o título, se houver
    if (titulo) {
        printf("\n--- %s ---\n", titulo);
    }

    // Linha superior da borda
    printf(COR_BORDA "╔");
    for (int i = 0; i < largura; i++) printf("═");
    printf("╗\n");

    // Loop principal para desenhar cada linha da mesa
    for (int i = 0; i < altura; i++) {
        printf(COR_BORDA "║" BACK_DARK_GREEN); // Parede esquerda e fundo verde

        // Verifica se esta é uma linha onde as cartas devem ser desenhadas
        if (num_cartas > 0 && i >= linha_inicio_cartas && i < linha_inicio_cartas + altura_carta) {
            int linha_arte_carta = i - linha_inicio_cartas; // Qual das 7 linhas da arte da carta estamos desenhando
            
            // Desenha o padding esquerdo
            for (int p = 0; p < padding_horizontal; p++) printf(" ");

            // Loop para desenhar a linha de arte de cada carta
            for (int c = 0; c < num_cartas; c++) {
                const char* valor = nos_cartas[c]->info.valor;
                const char* simbolo = obter_simbolo_naipe(nos_cartas[c]->info.naipe);

                // Imprime a parte correta da carta
                printf("%s", cores_cartas[c]); // Aplica a cor da carta
                switch(linha_arte_carta) {
                    case 0: printf(" .-------. "); break;
                    case 1: 
                        if (strcmp(valor, "10") == 0) printf(" |%s     | ", valor);
                        else printf(" |%-2s     | ", valor);
                        break;
                    case 2: printf(" |       | "); break;
                    case 3: printf(" |   %s   | ", simbolo); break;
                    case 4: printf(" |       | "); break;
                    case 5:
                        if (strcmp(valor, "10") == 0) printf(" |     %s| ", valor);
                        else printf(" |     %-2s| ", valor);
                        break;
                    case 6: printf(" '-------' "); break;
                }
                printf("%s", RESET BACK_DARK_GREEN); // Reseta a cor da carta para o fundo verde

                // Adiciona espaço entre as cartas
                if (c < num_cartas - 1) {
                    printf("  ");
                }
            }
            
            // Desenha o padding direito
            for (int p = 0; p < padding_horizontal; p++) printf(" ");

        } else {
            // Se não for uma linha de carta, apenas preenche com o fundo verde
            for (int j = 0; j < largura; j++) printf(" ");
        }

        printf(RESET COR_BORDA "║\n" RESET); // Reseta a cor e desenha a parede direita
    }

    // Linha inferior da borda
    printf(COR_BORDA "╚");
    for (int i = 0; i < largura; i++) printf("═");
    printf("╝\n" RESET);
}
#endif // INTERFACE_H