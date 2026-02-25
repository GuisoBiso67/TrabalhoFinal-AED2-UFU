#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreBinaria.h"

int main(void) {
    ArvBin *arvore = cria_ArvBin(); // arvore = raiz;

    struct Municipio municipios[27] = {
        {"Rio Branco", 8835.15, 389341},
        {"Maceio", 509.55, 957916},
        {"Macapa", 6407.12, 512902},
        {"Manaus", 11401.06, 2063547},
        {"Salvador", 692.82, 2417678},
        {"Fortaleza", 312.35, 2428678},
        {"Brasilia", 5760.78, 2817381},
        {"Vitoria", 97.12, 322869},
        {"Goiania", 739.49, 1437366},
        {"Sao Luis", 583.06, 1014837},
        {"Cuiaba", 5077.18, 650912},
        {"Campo Grande", 8092.95, 897938},
        {"Belo Horizonte", 331.40, 2315560},
        {"Belem", 1059.46, 1303403},
        {"Joao Pessoa", 211.48, 817511},
        {"Curitiba", 434.89, 1773733},
        {"Recife", 218.44, 1488920},
        {"Teresina", 1391.98, 866300},
        {"Rio de Janeiro", 1200.33, 6211223},
        {"Natal", 167.40, 751300},
        {"Porto Alegre", 495.39, 1332845},
        {"Porto Velho", 34090.95, 460434},
        {"Boa Vista", 5687.02, 419652},
        {"Florianopolis", 674.84, 537211},
        {"Sao Paulo", 1521.11, 11451999},
        {"Aracaju", 181.86, 602757},
        {"Palmas", 2226.57, 306296}
    };

    for (int i = 0; i < 27; i++) {
        insere_ArvBin(arvore, municipios[i]);
    }

    printAlfabeticamente_ArvBin(arvore);
    printf("-----------------\n");
    printf("Numero de Municipios: %d", contarMunicipios(arvore));
    printf("-----------------\n");
    printf("Cidades com mais de 1.000.000 habitantes:\n");
    mostrarPopulacaoMaiorQue(arvore, 1000000);
    printf("-----------------\n");
    printf("Densidade Populacional:\n");
    mostrarDensidade(arvore);
    printf("-----------------\n");
    printf("Area em relacao ao Brasil: %.2lf\n", percentualBrasil(arvore));
    printf("-----------------\n");
    printAlfabeticamenteCompleto_ArvBin(arvore);
    printf("-----------------\n");
    struct Municipio maiorPopulacao = cidadeMaiorPopulacao(arvore);
    printf("Cidade com maior populacao: %s, com %d habitantes\n", maiorPopulacao.nome, maiorPopulacao.populacao);
    printf("-----------------\n");
    int achou = buscaPorNome(arvore, "Uberlandia");
    if (achou == 1) {
        printf("Uberlandia esta arvore!\n");
    }else {
        printf("Uberlandia nao esta na arvore!\n");
    }
    printf("-----------------\n");
    removeMunicipio(arvore, "Aracaju");
    printAlfabeticamente_ArvBin(arvore);
    printf("-----------------\n");
    printf("-----------------\n");
    printf("-----------------\n");
    printf("-----------------\n");

    libera_ArvBin(arvore);
}