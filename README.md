# AED1-Trabalho-de-Aquecimento: Simulador de Propagação de Incêndios e Fuga de Animal

Trabalho de Aquecimento da disciplina de Algoritmos e Estruturas de Dados 1. O trabalho consiste em simular um incêndio em uma floresta representada por uma matriz, com propagação controlada por configurações de vento e número máximo de iterações, e inclui também a lógica de movimentação de um animal que tenta escapar das chamas.

---

## Características Principais

- **Leitura e escrita de arquivos** via módulo de entrada/saída (`entrada_saida.c` / `entrada_saida.h`).
- **Propagação do fogo** ortogonal (acima, abaixo, esquerda, direita), configurável em `config.h`.
- **Movimentação do animal** procurando água e áreas seguras, com regras de permanência e morte por cerco.
- **Modularização** clara: cada responsabilidade isolada em um módulo (`config.h`, `fogo.c`, `animal.c`, `main.c`).
- **Makefile** com alvos `clean`, `all` (ou `make`), e `run` para compilar e executar facilmente.

---

## Ambiente de Desenvolvimento

- **Sistema Operacional Host:** Windows 11
- **Subsistema Linux (WSL):** Ubuntu (via WSL 2)
- **Editor/IDE:** Visual Studio Code
- Terminal integrado do VSCode apontado para WSL Ubuntu.

---

## Pré-requisitos

- `gcc` (versão compatível com C11)
- `make`
- WSL Ubuntu instalado (caso use Windows)

---

## Como Compilar e Executar

No terminal (WSL / Ubuntu), dentro da pasta raiz do projeto:

```bash
# Remove artefatos anteriores
make clean

# Compila todos os módulos
make

# Executa a simulação
make run
```

O executável gerado chama-se `simula` e irá ler `input.dat`, rodar até o fogo não propagar mais ou atingir `MAX_ITERACOES` (definido em `config.h`), e gerar `output.dat` com o estado a cada iteração. Ao final, exibe no console a matriz final e a condição do animal.

---

## Estrutura de Arquivos

```
seu_projeto/
├── Makefile
├── output.dat         # gerado a cada execução
├── input.dat          # arquivo de entrada (mapa inicial)
├── include/
│   ├── config.h       # configurações globais da simulação
│   ├── entrada_saida.h
│   ├── fogo.h
│   └── animal.h
└── src/
    ├── main.c         # orquestra leitura, loop e saída
    ├── entrada_saida.c
    ├── fogo.c         # lógica de propagação de fogo
    └── animal.c       # lógica de movimentação do animal
```

---

## Descrição dos Módulos

- **config.h**
  - Define `MAX_ITERACOES` e flags de propagação (`PROPAGA_CIMA`, etc.).

- **entrada_saida**
  - `ler_input(const char* caminho)`: lê dimensões, ponto inicial do fogo e matriz de `input.dat`.
  - `escrever_output(const char* caminho, Floresta* f, int iteracao)`: anexa o estado atual ao `output.dat`.
  - `liberar_floresta(Floresta* f)`: desaloca memória.

- **fogo.c / fogo.h**
  - `propagar_fogo(Floresta* f, int* spread)`: executa uma iteração de fogo, queima árvores saudáveis (`1 → 2`) e transforma chamas (`2 → 3`).

- **animal.c / animal.h**
  - `init_animal(Floresta* f)`: posiciona o animal na primeira célula vazia (`0`).
  - `move_animal(Floresta* f, Animal* a)`: movimenta ou mantém o animal conforme prioridade (água > vazio/árvore saudável > queimado), conta permanência e detecta morte.

- **main.c**
  1. Lê `input.dat`.
  2. Inicializa o animal.
  3. Loop de até `MAX_ITERACOES`:
     - Move o animal.
     - Propaga o fogo.
     - Grava estado.
     - Interrompe se o fogo não se espalhar mais.
  4. Exibe matriz final e condição do animal.

---

## Observações

Este projeto foi testado e executado em Windows 11 com WSL Ubuntu, utilizando o terminal integrado do VSCode. Não foram necessários ajustes adicionais para rodar em sistemas Linux nativos.

> **Autor:** Michael Yoshiaki Todoroki
> **Data:** 20 de Abril de 2025

