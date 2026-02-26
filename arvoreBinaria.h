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
void printAlfabeticamente_ArvBin(ArvBin *raiz); // esq -> raiz -> direita = emOrdem

int contarMunicipios(ArvBin *raiz);
void mostrarPopulacaoMaiorQue(ArvBin* raiz, int x);
double calculaDensidade(ArvBin *raiz);
void mostrarDensidade(ArvBin* raiz);
double somaAreas(ArvBin *raiz);
double percentualBrasil(ArvBin* raiz);
void printAlfabeticamenteCompleto_ArvBin(ArvBin *raiz);
struct Municipio cidadeMaiorPopulacao(ArvBin* raiz);

/* FUNÇÕES EXTRAS */
int buscaPorNome(ArvBin* raiz, char* nome);
struct NO* encontrarMinimo(struct NO* no);
struct NO* removeMunicipio(ArvBin* raiz, char* nome);
int somaPopulacao(ArvBin* raiz);
double mediaPopulacao(ArvBin* raiz);
int carregar_municipios(ArvBin *A, const char *filename);

// auxiliares para inserção AVL;
int altura_NO(struct NO* no);
int fatorBalanceamento_NO(struct NO* no);
int maior(int x, int y);
int altura_ArvBin(ArvBin *raiz);
void RotacaoLL(ArvBin *A);
void RotacaoRR(ArvBin *A);
void RotacaoLR(ArvBin *A);
void RotacaoRL(ArvBin *A);
// --------------------------------------;
// converter para AVL vou fazer na inserção;
// ler arquivos de .csv


// remover depois?
struct NO* remove_atual(struct NO* atual);
int remove_ArvBin(ArvBin *raiz, struct Municipio info);
int estaVazia_ArvBin(ArvBin *raiz);
int consulta_ArvBin(ArvBin *raiz, struct Municipio info);

void preOrdem_ArvBin(ArvBin *raiz); // raiz -> esq -> dir
void posOrdem_ArvBin(ArvBin *raiz); // esq -> dir -> raiz

#endif //ARVOREBINARIA_H
