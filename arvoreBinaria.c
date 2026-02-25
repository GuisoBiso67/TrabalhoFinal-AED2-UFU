#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreBinaria.h"

/*
struct Municipio {
    char nome[100];
    float area; // em km²
    int populacao;
};
*/


struct NO{
    struct Municipio info;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin(){
    ArvBin* raiz = malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

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

int insere_ArvBin(ArvBin* raiz, struct Municipio info){
    if(raiz == NULL) // ponteiro valido;
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;

    novo->info = info;
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL) // arvore vazia
        *raiz = novo;
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;

        while(atual != NULL){
            ant = atual;

            if(strcmp(novo->info.nome, atual->info.nome) == 0){ // se for igual, nem coloca o elemento, ele ja existe;
                free(novo);
                return 0; //elemento ja existe;
            }

            if(strcmp(novo->info.nome, atual->info.nome) > 0) atual = atual->dir; // vai para direita
            else atual = atual->esq; // vai para esquerda
        }

        if(strcmp(novo->info.nome, ant->info.nome) > 0) ant->dir = novo;
        else ant->esq = novo;
    }
    return 1;
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
        printf("%s\n",(*raiz)->info.nome);
        printAlfabeticamente_ArvBin(&((*raiz)->dir));
    }
}

int contarMunicipios(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = contarMunicipios(&((*raiz)->esq));
    int alt_dir = contarMunicipios(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
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

int consulta_ArvBin(ArvBin *raiz, struct Municipio info){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if (strcmp(info.nome, atual->info.nome) == 0) return 1;

        if (strcmp(info.nome, atual->info.nome) > 0) atual = atual->dir;
        else atual = atual->esq;
    }
    return 0;
}

// ver se precisa depois

/*
void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%s\n",(*raiz)->info.nome);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

void posOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%s\n",(*raiz)->info.nome);
    }
}
*/

