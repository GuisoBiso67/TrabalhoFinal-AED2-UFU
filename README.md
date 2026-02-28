# TrabalhoFinal-AED2-UFU
# 🌳 Árvore AVL -- Cadastro de Municípios

Implementação de uma **Árvore AVL (Árvore Binária de Busca Balanceada)**
em C para armazenamento e gerenciamento de municípios, organizados
alfabeticamente pelo nome.

Projeto desenvolvido para a disciplina de Estrutura de Dados.

------------------------------------------------------------------------

## 📌 Descrição

O sistema armazena municípios em uma **Árvore AVL**, garantindo:

-   Inserção balanceada automática\
-   Busca eficiente\
-   Remoção balanceada\
-   Impressão ordenada (in-order)\
-   Manipulação dinâmica de memória

A estrutura utiliza o **nome do município como chave**, permitindo
ordenação alfabética e busca otimizada.

------------------------------------------------------------------------

## 🧠 Estrutura de Dados

Cada nó da árvore contém:

``` c
typedef struct no{
    Municipio info;
    struct no *esq;
    struct no *dir;
    int altura;
} No;
```

A árvore mantém o fator de balanceamento:

-1 ≤ FB ≤ 1

Quando necessário, são aplicadas rotações para manter a estrutura
balanceada.

------------------------------------------------------------------------

## 🔄 Rotações Implementadas

-   Rotação simples à direita (LL)\
-   Rotação simples à esquerda (RR)\
-   Rotação dupla esquerda-direita (LR)\
-   Rotação dupla direita-esquerda (RL)

Essas rotações garantem altura **O(log n)**.

------------------------------------------------------------------------

## ⚙️ Funcionalidades

### ✔ Obrigatórias

-   Inserção balanceada\
-   Busca por município\
-   Remoção\
-   Impressão em ordem alfabética\
-   Liberação da memória\
-   Cálculo de altura

### ✔ Opcionais (também implementadas)

-   Busca da cidade com maior população\
-   Impressão detalhada dos dados\
-   Carregamento via arquivo\
-   Funções auxiliares adicionais

------------------------------------------------------------------------

## 📈 Complexidade

  Operação   Complexidade
  ---------- --------------
  Inserção   O(log n)
  Busca      O(log n)
  Remoção    O(log n)
  Percurso   O(n)

------------------------------------------------------------------------

## 🧾 Justificativa da Chave

O **nome do município** foi escolhido como chave por:

-   Ser identificador textual intuitivo\
-   Permitir ordenação alfabética automática\
-   Facilitar buscas pelo usuário\
-   Garantir critério consistente de comparação com `strcmp`

------------------------------------------------------------------------

## 🔍 Discussão

Se os nomes forem inseridos já em ordem alfabética:

-   Em uma BST simples → a árvore se tornaria uma lista encadeada
    (O(n)).\
-   Na AVL → rotações mantêm a altura O(log n).

Isso garante eficiência independentemente da ordem de inserção.

------------------------------------------------------------------------

## ▶️ Compilação

``` bash
gcc main.c arvoreAVL.c -o programa
./programa
```

------------------------------------------------------------------------

## 👨‍💻 Autor

Guilherme Cotrim
