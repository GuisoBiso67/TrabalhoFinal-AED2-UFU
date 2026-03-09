#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arvoreBinaria.h"

struct NO{
    struct Municipio info;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin(){
    ArvBin* raiz = malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

// liberar memoria
void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada no;
    free(raiz);//libera a raiz;
}

// FUNÇÕES AUXILIARES PARA INSERÇÃO AVL

int altura_NO(struct NO* no){
    if(no == NULL) return -1;
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return (altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y){
    if(x > y) return x;
    return y;
}

int altura_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));

    if (alt_esq > alt_dir) return (alt_esq + 1);
    else return(alt_dir + 1);
}

// acontece quando a árvore fica muito pesada para a esquerda;
void RotacaoLL(ArvBin *A){
    printf("RotacaoLL\n");
    struct NO *B;
    B = (*A)->esq; // B vira o novo topo;
    (*A)->esq = B->dir; // A passa a ser filho direito de B;
    B->dir = *A; // O filho direito de B vira filho esquerdo de A

    // recalcula altura;
    (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B; // B vira a raiz daquela subárvore.
}

// um espelho de RotacaoLL; // acontece quando a arvore fica muito pesada para a direita;
void RotacaoRR(ArvBin *A){
    printf("RotacaoRR\n");
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

// inseriu na esquerda, mas foi na direita da esquerda;
// nao da para resolver com uma rotacao simples;
void RotacaoLR(ArvBin *A) {
    RotacaoRR(&(*A)->esq); // RotacaoRR na subarvore esquerda
    RotacaoLL(A); // RotacaoLL na raiz;
}

// espelho de ROtacaoLR;
void RotacaoRL(ArvBin *A){
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}
// ------------------------------------------

int insere_ArvBin(ArvBin* raiz, struct Municipio info){
    int res;
    if(raiz == NULL) // ponteiro valido;
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL) return 0;

    novo->info = info;
    novo->altura = 0;
    novo->dir = NULL;
    novo->esq = NULL;

    struct NO *atual = *raiz;

    if(*raiz == NULL) { // arvore vazia
        *raiz = novo;
        return 1;
    }else {
        if (strcmp(info.nome, atual->info.nome) < 0) {
            if ((res = insere_ArvBin(&(*raiz)->esq, info)) == 1) {
                if (fatorBalanceamento_NO(atual) >= 2) {
                    if (strcmp(info.nome, (*raiz)->esq->info.nome) < 0) { // se info.nome vier antes de raiz->info.nome;
                        RotacaoLL(raiz);
                    }else {
                        RotacaoLR(raiz);
                    }
                }
            }
        }else {
            if (strcmp(info.nome, atual->info.nome) > 0) {
                if ((res = insere_ArvBin(&(*raiz)->dir, info)) == 1) {
                    if (fatorBalanceamento_NO(atual) <= -2) {
                        if (strcmp((*raiz)->dir->info.nome, info.nome) < 0) {
                            RotacaoRR(raiz);
                        }else {
                            RotacaoRL(raiz);
                        }
                    }
                }
            }else {
                printf("Valor Duplicado!\n");
                return 0;
            }
        }
    }
    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;
    return res;
}

struct NO* remove_atual(struct NO* atual) {
    struct NO *no1, *no2;
    if(atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }
    // no2 eh o no anterior a r na ordem e-r-d;
    // no1 eh o pai de no2;
    if(no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int remove_ArvBin(ArvBin *raiz, struct Municipio info){
    if(raiz == NULL)
        return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(strcmp(info.nome, atual->info.nome) == 0){
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else{
                if(ant->dir == atual) ant->dir = remove_atual(atual);
                else ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if(strcmp(info.nome, atual->info.nome) > 0) atual = atual->dir;
        else atual = atual->esq;
    }
    return 0;
}

int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

void printAlfabeticamente_ArvBin(ArvBin *raiz){ // impressão emOrdem
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printAlfabeticamente_ArvBin(&((*raiz)->esq));
        printf("%s, altura: %d\n",(*raiz)->info.nome, altura_NO((*raiz)));
        printAlfabeticamente_ArvBin(&((*raiz)->dir));
    }
}

int contarMunicipios(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int qtd_esq = contarMunicipios(&((*raiz)->esq));
    int qtd_dir = contarMunicipios(&((*raiz)->dir));
    return(qtd_esq + qtd_dir + 1);
}

void mostrarPopulacaoMaiorQue(ArvBin* raiz, int x) {
    if(raiz == NULL) return;
    if(*raiz == NULL) return;

    if ((*raiz)->info.populacao > x) {
        printf("%s: %d habitantes\n", (*raiz)->info.nome, (*raiz)->info.populacao);
    }
    mostrarPopulacaoMaiorQue(&(*raiz)->esq, x);
    mostrarPopulacaoMaiorQue(&(*raiz)->dir, x);
}

double calculaDensidade(ArvBin *raiz){
    if(raiz == NULL) return 0;
    if(*raiz == NULL) return 0;

    return (*raiz)->info.populacao/(*raiz)->info.area;
}

void mostrarDensidade(ArvBin* raiz) {
    if(raiz == NULL) return;
    if(*raiz == NULL) return;

    printf("%s: %.2lf por km^2\n", (*raiz)->info.nome, calculaDensidade(raiz));

    mostrarDensidade(&(*raiz)->esq);
    mostrarDensidade(&(*raiz)->dir);
}

double somaAreas(ArvBin *raiz) {
    if (raiz == NULL) return 0;
    if (*raiz == NULL) return 0;

    return (*raiz)->info.area + somaAreas(&(*raiz)->dir) + somaAreas(&(*raiz)->esq);
}

double percentualBrasil(ArvBin* raiz) {
    if(raiz == NULL) return 0;
    if(*raiz == NULL) return 0;

    return (somaAreas(raiz) / 8510000.0) * 100;
}

void printAlfabeticamenteCompleto_ArvBin(ArvBin *raiz){ // impressão emOrdem
    if(raiz == NULL) return;
    if(*raiz == NULL) return;
    printAlfabeticamenteCompleto_ArvBin(&((*raiz)->esq));

    printf("Nome: %s\n",(*raiz)->info.nome);
    printf("Area: %.2lf\n",(*raiz)->info.area);
    printf("Populacao: %d\n",(*raiz)->info.populacao);
    printf("Densidade: %.2lf hab/km^2 \n",calculaDensidade(raiz));
    printf("---------------------------\n");

    printAlfabeticamenteCompleto_ArvBin(&((*raiz)->dir));
}

struct Municipio cidadeMaiorPopulacao(ArvBin* raiz) {
    if(raiz == NULL) {
        struct Municipio vazia = {"", 0, 0};
        return vazia;
    }
    if(*raiz == NULL) {
        struct Municipio vazia = {"", 0, 0};
        return vazia;
    }

    struct Municipio maiorAtual = (*raiz)->info;
    struct Municipio maiorEsq = cidadeMaiorPopulacao(&(*raiz)->esq);
    struct Municipio maiorDir = cidadeMaiorPopulacao(&(*raiz)->dir);

    if (maiorAtual.populacao >= maiorEsq.populacao && maiorAtual.populacao >= maiorDir.populacao) {
        return maiorAtual;
    }
    if (maiorEsq.populacao >= maiorAtual.populacao && maiorEsq.populacao >= maiorDir.populacao) {
        return maiorEsq;
    }
    return maiorDir;
}

/* FUNÇÕES EXTRAS */
int buscaPorNome(ArvBin* raiz, char* nome) {
    if(raiz == NULL) return 0;
    if(*raiz == NULL) return 0;
    if (strcmp((*raiz)->info.nome, nome) == 0) {
        return 1; // cidade encontrada
    }
    if (buscaPorNome(&(*raiz)->esq, nome)) {
        return 1;
    }
    return buscaPorNome(&(*raiz)->dir, nome);

    // 0 = cidade nao encontrada
}

struct NO* encontrarMinimo(struct NO* no) {
    if (no == NULL) return NULL;

    struct NO* ant = no;
    struct NO* atual = no->esq;

    while (atual != NULL) {
        ant = atual;
        atual = atual->esq;
    }
    return ant;
}

struct NO* removeMunicipio(ArvBin* raiz, char* nome) {
    if(raiz == NULL) return NULL;
    if(*raiz == NULL) return NULL;

    // navega até o nó que precisa ser removido;
    if (strcmp((*raiz)->info.nome, nome) > 0) {
        (*raiz)->esq = removeMunicipio(&(*raiz)->esq, nome);
    }else if (strcmp((*raiz)->info.nome, nome) < 0) {
        (*raiz)->dir = removeMunicipio(&(*raiz)->dir, nome);
    }else {
        if ((*raiz)->esq == NULL) {
            struct NO* temp = (*raiz)->dir;
            free(*raiz);
            return temp; // retorna só a raiz da sub-arvore direita
        }else if ((*raiz)->dir == NULL) {
            struct NO* temp = (*raiz)->esq;
            free(*raiz);
            return temp; // retorna só a raiz da sub-arvore esquerda
        }

        // se o nó a ser removido tem filho esq e dir, ele caminha até o menor elemento da sub-arvore direita
        struct NO* temp = encontrarMinimo((*raiz)->dir);
        // copia info do menor da subárvore direita (sucessor); é como se ele trocasse o removido com o ultimo de lugar; pra EU lembrar: tipo um heap;
        (*raiz)->info = temp->info;
        /*
        A linha "(*raiz)->dir = removeMunicipio(&(*raiz)->dir, temp->info);" é o que faz funcionar.
        Ela faz uma nova chamada recursiva para deletar o nó que acabou de ser copiado.
        Como o sucessor é, por regra, o menor da direita, ele nunca terá um filho à esquerda,
        o que significa que essa segunda chamada de remoção cairá obrigatoriamente no caso 1 ou 2,
        sendo resolvida instantaneamente.
         */
        (*raiz)->dir = removeMunicipio(&(*raiz)->dir, temp->info.nome); // vai cair no caso em que um dos filhos é null;
    }

    // rebalanceando a arvore:
    if (*raiz == NULL) return *raiz; // para nao dar problema em atualizar a altura;
    (*raiz)->altura = 1 + maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir));
    int fb = fatorBalanceamento_NO(*raiz);

    if (fb > 1 && fatorBalanceamento_NO((*raiz)->esq) >= 0) RotacaoRR(raiz);
    else if (fb > 1 && fatorBalanceamento_NO((*raiz)->esq) < 0) RotacaoLR(raiz);
    else if (fb < -1 && fatorBalanceamento_NO((*raiz)->dir) <= 0) RotacaoLL(raiz);
    else if (fb < -1 && fatorBalanceamento_NO((*raiz)->dir) > 0) RotacaoRL(raiz);

    return *raiz;
}

// auxiliar para mediaPopulação
int somaPopulacao(ArvBin* raiz) {
        if (raiz == NULL) return 0;
        if (*raiz == NULL) return 0;

        return (*raiz)->info.populacao + somaPopulacao(&(*raiz)->dir) + somaPopulacao(&(*raiz)->esq);
}

double mediaPopulacao(ArvBin* raiz) {
    int denominador = contarMunicipios(raiz);
    int numerador = somaPopulacao(raiz);
    return (double) numerador / denominador;
}

int carregar_municipios(ArvBin *A, const char *filename) {
    if (A == NULL) return 0;
    //if (*A == NULL) return 0;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo");
        return 0;
    }

    struct Municipio m;
    char linha[200];
    fgets(linha, sizeof(linha), file); // ignora linha do cabeçalho;

    while (fgets(linha, sizeof(linha), file)) {
        linha[strcspn(linha, "\n")] = '\0';

        strcpy(m.nome, strtok(linha, ",")); // separa o nome
        m.area = strtof(strtok(NULL, ","), NULL);
        m.populacao = strtol(strtok(NULL, ","), NULL, 10);

        //trim(m.nome); // retira espaços
        insere_ArvBin(A, m);
    }
    fclose(file);
    return 1;
}

