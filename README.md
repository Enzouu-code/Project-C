# Sistema de Negociação de Criptomoedas em C

Projeto acadêmico desenvolvido em linguagem C para a disciplina **Desenvolvimento de Algoritmos**, com o objetivo de simular um sistema de negociação de criptomoedas, incluindo cadastro de usuários, autenticação, gerenciamento de saldo, operações financeiras e acompanhamento de cotações.

**Autor:** Enzo Oliveira Fonseca  
**RA:** 221260235  
**Disciplina:** Desenvolvimento de Algoritmos

---

## 1. Sobre o projeto

O programa simula uma plataforma de negociação de criptomoedas, permitindo que diferentes usuários tenham suas próprias contas, saldo em reais e quantidades de criptomoedas.

O sistema possui capacidade para armazenar até **100 usuários**, mantendo os dados de cada cadastro em uma estrutura própria.

As cotações das criptomoedas são atualizadas por meio de valores pseudoaleatórios, simulando variações de mercado.

## 2. Funcionalidades

- Cadastro de usuários.
- Login e autenticação por CPF e senha.
- Gerenciamento individual de saldo em reais.
- Armazenamento de até três tipos de criptomoedas por usuário.
- Consulta de cotações.
- Simulação de variações no mercado.
- Compra e venda de criptomoedas.
- Atualização dos saldos após as operações.
- Registro de transações com data e horário.
- Consulta do extrato de operações.
- Navegação por menus no terminal.

## 3. Estrutura do programa

O projeto utiliza uma estrutura chamada `Usuario`, responsável por armazenar as informações de cada usuário:

```c
typedef struct {
    char cpf[12];
    char senha[7];
    char nome[50];
    double reais;
    double cripto[3];
} Usuario;
```

O armazenamento dos usuários é realizado por meio de um vetor com capacidade para 100 posições:

```c
Usuario usuarios[100];
int qtd = 0;
Usuario *u;
```

- `usuarios[100]`: armazena os dados dos usuários cadastrados.
- `qtd`: controla a quantidade de usuários registrados.
- `Usuario *u`: ponteiro utilizado para acessar os dados do usuário autenticado.

## 4. Bibliotecas utilizadas

| Biblioteca | Aplicação |
|---|---|
| `stdio.h` | Entrada e saída de dados, além da manipulação de arquivos. |
| `stdlib.h` | Utilizada para funções como `rand()`, `srand()` e `system()`. |
| `string.h` | Manipulação e comparação de textos, como CPF, senha e nome. |
| `time.h` | Utilizada para trabalhar com data e horário e inicializar a geração pseudoaleatória. |

## 5. Funcionamento técnico

### Atualização das cotações

A função `atualizarCotacao()` utiliza números pseudoaleatórios para simular variações nos preços das criptomoedas.

As variações são aplicadas por meio de um multiplicador entre `0.95` e `1.05`, representando oscilações de até -5% ou +5%.

### Registro de transações

A função `registrar()` utiliza recursos da biblioteca `time.h` para obter a data e o horário das operações e registra as informações em arquivo por meio de `fprintf()`.

### Limpeza do terminal

O programa utiliza `system()` para executar comandos de limpeza do terminal, permitindo atualizar a interface entre os menus e facilitar a navegação.

## 6. Tecnologias utilizadas

- **Linguagem:** C
- **Bibliotecas:** `stdio.h`, `stdlib.h`, `string.h` e `time.h`
- **Ambiente:** Terminal
- **Conceitos aplicados:** estruturas, vetores, ponteiros, funções, condicionais, repetições, manipulação de arquivos e geração de números pseudoaleatórios.

## 7. Objetivo acadêmico

O desenvolvimento do projeto permitiu aplicar conceitos fundamentais da programação estruturada em C, integrando diferentes recursos da linguagem na construção de um sistema funcional.

O trabalho reúne **16 funções**, organizando as operações do programa em partes específicas e facilitando a leitura, manutenção e execução do código.
