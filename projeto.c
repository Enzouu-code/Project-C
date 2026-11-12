
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char cpf[12], senha[7], nome[50];
    double reais;
    double cripto[3];
} Usuario;

Usuario usuarios[100];
int qtd = 0;
Usuario *u;

char *nomes[3] = {"BTC", "ETH", "XRP"};
double cotacao[3] = {350000, 18000, 3};
double taxaCompra[3] = {0.02, 0.01, 0.01};
double taxaVenda[3] = {0.03, 0.02, 0.01};

/* ---------- arquivos ---------- */

void carregar() {
    FILE *f = fopen("usuarios.txt", "r");

    if (f == NULL) {
        strcpy(usuarios[0].cpf, "12345678900");
        strcpy(usuarios[0].senha, "123456");
        strcpy(usuarios[0].nome, "Usuario_Teste");

        usuarios[0].reais = 0;
        usuarios[0].cripto[0] = 0;
        usuarios[0].cripto[1] = 0;
        usuarios[0].cripto[2] = 0;

        qtd = 1;
    } else {
        while (qtd < 100 &&
               fscanf(f, "%11s %6s ", usuarios[qtd].cpf,
                      usuarios[qtd].senha) == 2) {

            if (fscanf(f, "%49[^;]; %lf %lf %lf %lf",
                       usuarios[qtd].nome,
                       &usuarios[qtd].reais,
                       &usuarios[qtd].cripto[0],
                       &usuarios[qtd].cripto[1],
                       &usuarios[qtd].cripto[2]) == 5) {
                qtd++;
            } else {
                break;
            }
        }

        fclose(f);
    }

    f = fopen("cotacoes.txt", "r");

    if (f != NULL) {
        fscanf(f, "%lf %lf %lf",
               &cotacao[0], &cotacao[1], &cotacao[2]);
        fclose(f);
    }
}

void salvar() {
    int i;
    FILE *f = fopen("usuarios.txt", "w");

    for (i = 0; i < qtd; i++)
        fprintf(f, "%s %s %s; %.8f %.8f %.8f %.8f\n",
                usuarios[i].cpf, usuarios[i].senha, usuarios[i].nome,
                usuarios[i].reais, usuarios[i].cripto[0],
                usuarios[i].cripto[1], usuarios[i].cripto[2]);

    fclose(f);

    f = fopen("cotacoes.txt", "w");
    fprintf(f, "%.2f %.2f %.4f\n",
            cotacao[0], cotacao[1], cotacao[2]);
    fclose(f);
}

/* ---------- extrato ---------- */

void registrar(char sinal, double valor, char *moeda, double ct, double tx) {
    char arq[40];
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    FILE *f;

    sprintf(arq, "extrato_%s.txt", u->cpf);
    f = fopen(arq, "a");

    fprintf(f, "%02d-%02d-%d %02d:%02d %c %.2f %s CT: %.2f TX: %.2f "
               "REAL: %.2f BTC: %.4f ETH: %.4f XRP: %.4f\n",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
            t->tm_hour, t->tm_min, sinal, valor, moeda, ct, tx,
            u->reais, u->cripto[0], u->cripto[1], u->cripto[2]);

    fclose(f);
}

/* ---------- funcoes auxiliares ---------- */

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

int pedirSenha() {
    char s[20];

    printf("Senha (6 digitos): ");
    scanf("%19s", s);

    if (strcmp(s, u->senha) == 0) return 1;

    printf("Senha incorreta!\n");
    return 0;
}

void mostrarSaldo() {
    printf("\n");
    printf("====================================\n");
    printf("          CRYPTEX - SALDO           \n");
    printf("====================================\n");
    printf("Nome: %s\nCPF: %s\n", u->nome, u->cpf);
    printf("------------------------------------\n");
    printf("Reais:    R$ %.2f\n", u->reais);
    printf("Bitcoin:     %.4f BTC\n", u->cripto[0]);
    printf("Ethereum:    %.4f ETH\n", u->cripto[1]);
    printf("Ripple:      %.4f XRP\n", u->cripto[2]);
    printf("====================================\n");
}

void mostrarCotacoes() {
    printf("\n");
    printf("====================================\n");
    printf("         COTACOES DO MERCADO         \n");
    printf("====================================\n");
    printf("[1] Bitcoin : R$ %.2f\n", cotacao[0]);
    printf("[2] Ethereum: R$ %.2f\n", cotacao[1]);
    printf("[3] Ripple  : R$ %.4f\n", cotacao[2]);
    printf("====================================\n");
}

/* ---------- operacoes ---------- */

void consultarSaldo() {
    if (pedirSenha()) mostrarSaldo();
}

void consultarExtrato() {
    char arq[40], linha[300];
    FILE *f;

    if (!pedirSenha()) return;

    printf("\n");
    printf("====================================\n");
    printf("         CRYPTEX - EXTRATO          \n");
    printf("====================================\n");
    printf("Nome: %s\nCPF: %s\n\n", u->nome, u->cpf);

    sprintf(arq, "extrato_%s.txt", u->cpf);
    f = fopen(arq, "r");

    if (f == NULL) {
        printf("Nenhuma operacao registrada.\n");
        return;
    }

    while (fgets(linha, sizeof linha, f) != NULL)
        printf("%s", linha);

    fclose(f);
}

void depositar() {
    double v;

    printf("\n");
    printf("====================================\n");
    printf("         CRYPTEX - DEPOSITO         \n");
    printf("====================================\n");

    printf("Valor do deposito: R$ ");
    scanf("%lf", &v);

    if (v <= 0) {
        printf("Valor invalido.\n");
        return;
    }

    u->reais += v;

    registrar('+', v, "REAL", 0.0, 0.0);
    salvar();
    mostrarSaldo();
}

void sacar() {
    double v;

    printf("\n");
    printf("====================================\n");
    printf("           CRYPTEX - SAQUE          \n");
    printf("====================================\n");

    printf("Valor do saque: R$ ");
    scanf("%lf", &v);

    if (v <= 0 || v > u->reais) {
        printf("Valor invalido ou saldo insuficiente.\n");
        return;
    }

    u->reais -= v;

    registrar('-', v, "REAL", 0.0, 0.0);
    salvar();
    mostrarSaldo();
}

void comprar() {
    int m;
    double valor, custo;

    if (!pedirSenha()) return;

    mostrarCotacoes();

    printf("\nEscolha a moeda (1-BTC, 2-ETH, 3-XRP): ");
    scanf("%d", &m);

    if (m < 1 || m > 3) {
        printf("Moeda invalida.\n");
        return;
    }

    m--;

    printf("Quanto deseja investir (em reais, sem a taxa): ");
    scanf("%lf", &valor);

    custo = valor * (1 + taxaCompra[m]);

    if (valor <= 0 || custo > u->reais) {
        printf("Valor invalido ou saldo insuficiente.\n");
        return;
    }

    u->reais -= custo;
    u->cripto[m] += valor / cotacao[m];

    registrar('+', valor, nomes[m], cotacao[m], taxaCompra[m]);

    salvar();
    mostrarSaldo();
}

void vender() {
    int m;
    double q, bruto;

    if (!pedirSenha()) return;

    mostrarCotacoes();

    printf("\nEscolha a moeda (1-BTC, 2-ETH, 3-XRP): ");
    scanf("%d", &m);

    if (m < 1 || m > 3) {
        printf("Moeda invalida.\n");
        return;
    }

    m--;

    printf("Voce possui %.8f %s. Quantidade a vender: ",
           u->cripto[m], nomes[m]);

    scanf("%lf", &q);

    if (q <= 0 || q > u->cripto[m]) {
        printf("Quantidade invalida.\n");
        return;
    }

    bruto = q * cotacao[m];

    u->cripto[m] -= q;
    u->reais += bruto * (1 - taxaVenda[m]);

    registrar('-', bruto, nomes[m], cotacao[m], taxaVenda[m]);

    salvar();
    mostrarSaldo();
}

void atualizarCotacao() {
    int i;

    for (i = 0; i < 3; i++)
        cotacao[i] *= 0.95 + (rand() % 1001) / 10000.0;

    salvar();

    printf("\n");
    printf("====================================\n");
    printf("       COTACOES ATUALIZADAS!        \n");
    printf("====================================\n");

    mostrarCotacoes();
}

/* ---------- programa principal ---------- */

int main() {
    char cpf[20], senha[20];
    int i, op;

    srand(time(NULL));
    carregar();

    printf("\n");
    printf("====================================\n");
    printf("          C R Y P T E X             \n");
    printf("        PROJETO C EXCHANGE          \n");
    printf("====================================\n");

    printf("\nCPF (somente numeros): ");
    scanf("%19s", cpf);

    printf("Senha (6 digitos): ");
    scanf("%19s", senha);

    for (i = 0; i < qtd; i++)
        if (strcmp(usuarios[i].cpf, cpf) == 0 &&
            strcmp(usuarios[i].senha, senha) == 0)
            u = &usuarios[i];

    if (u == NULL) {
        printf("\nCPF ou senha invalidos.\n");
        return 1;
    }

    do {
        limparTela();

        printf("====================================\n");
        printf("          C R Y P T E X             \n");
        printf("        PROJETO C EXCHANGE          \n");
        printf("====================================\n");
        printf(" Bem-vindo(a), %s!\n", u->nome);

        printf("-------- OPERACOES FINANCEIRAS ------\n");
        printf(" [1] Consultar saldo\n");
        printf(" [2] Consultar extrato\n");
        printf(" [3] Depositar reais\n");
        printf(" [4] Sacar reais\n");

        printf("------- MERCADO DE CRIPTOMOEDAS -----\n");
        printf(" [5] Comprar criptomoedas\n");
        printf(" [6] Vender criptomoedas\n");
        printf(" [7] Atualizar cotacoes\n");

        printf(" [8] Sair do sistema\n");
        printf("====================================\n");
        printf(" Opcao: ");

        scanf("%d", &op);

        limparTela();

        if      (op == 1) consultarSaldo();
        else if (op == 2) consultarExtrato();
        else if (op == 3) depositar();
        else if (op == 4) sacar();
        else if (op == 5) comprar();
        else if (op == 6) vender();
        else if (op == 7) atualizarCotacao();
        else if (op != 8) printf("Opcao invalida.\n");

        if (op != 8) pausar();

    } while (op != 8);

    printf("\n");
    printf("====================================\n");
    printf("       OBRIGADO POR UTILIZAR        \n");
    printf("              CRYPTEX               \n");
    printf("====================================\n");
    printf(" Ate logo, %s!\n", u->nome);

    return 0;
}
