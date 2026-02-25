//
// Created by guiso on 2/25/2026.
//

#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

typedef struct NO* ArvBin;


struct Municipio {
    char nome[100];
    float area; // em km²
    int populacao;
};

ArvBin* cria_ArvBin();

void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, struct Municipio info);
void printAlfabeticamente_ArvBin(ArvBin *raiz); // esq -> raiz -> direita
int remove_ArvBin(ArvBin *raiz, struct Municipio info);

int contarMunicipios(ArvBin *raiz);
void mostrarPopulacaoMaiorQue(ArvBin* raiz, int x);
double calculaDensidade(ArvBin *raiz);
void mostrarDensidade(ArvBin* raiz);
double somaAreas(ArvBin *raiz);
double percentualBrasil(ArvBin* raiz);
void printAlfabeticamenteCompleto_ArvBin(ArvBin *raiz);
struct Municipio cidadeMaiorPopulacao(ArvBin* raiz);




int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int consulta_ArvBin(ArvBin *raiz, struct Municipio info);

void preOrdem_ArvBin(ArvBin *raiz); // raiz -> esq -> dir
void posOrdem_ArvBin(ArvBin *raiz); // esq -> dir -> raiz

#endif //ARVOREBINARIA_H
