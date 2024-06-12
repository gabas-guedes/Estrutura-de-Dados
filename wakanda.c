#include "cidades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Função de troca de cidades
void trocarCidades(Cidade *a, Cidade *b) {
    Cidade temp = *a;
    *a = *b;
    *b = temp;
}

// Função de particionamento para o QuickSort
int particionar(Cidade arr[], int baixo, int alto) {
    int pivo = arr[alto].Posicao;
    int i = (baixo - 1);
    for (int j = baixo; j <= alto - 1; j++) {
        if (arr[j].Posicao < pivo) {
            i++;
            trocarCidades(&arr[i], &arr[j]);
        }
    }
    trocarCidades(&arr[i + 1], &arr[alto]);
    return (i + 1);
}

// Função QuickSort para ordenar cidades
void quickSort(Cidade arr[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(arr, baixo, alto);
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

// Função para inicializar as cidades no TAD Estrada.
Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        return NULL;
    }

    int T, N;
    fscanf(arquivo, "%d", &T);
    fscanf(arquivo, "%d", &N);

    // Verifica as restrições
    if (T < 3 || T > 1000000 || N < 2 || N > 10000) {
        fclose(arquivo);
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) {
        fclose(arquivo);
        return NULL;
    }

    estrada->N = N;
    estrada->T = T;
    estrada->C = (Cidade *)malloc(N * sizeof(Cidade));
    if (!estrada->C) {
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < N; i++) {
        fscanf(arquivo, "%d %[^\n]s", &estrada->C[i].Posicao, estrada->C[i].Nome);
    }

    fclose(arquivo);

    // Organiza as cidades em ordem crescente de posição usando QuickSort
    quickSort(estrada->C, 0, N - 1);

    return estrada;
}

// Função para calcular a menor vizinhança.
double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        return -1;
    }

    double menorVizinhanca = estrada->T;

    for (int i = 0; i < estrada->N; i++) {
        double inicio = (i == 0) ? 0 : (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
        double fim = (i == estrada->N - 1) ? estrada->T : (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
        double vizinhanca = fim - inicio;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

// Função para retornar a cidade que tem a menor vizinhança.
char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        return NULL;
    }

    double menorVizinhanca = estrada->T;
    int cidadeIndex = 0;

    for (int i = 0; i < estrada->N; i++) {
        double inicio = (i == 0) ? 0 : (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
        double fim = (i == estrada->N - 1) ? estrada->T : (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
        double vizinhanca = fim - inicio;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            cidadeIndex = i;
        }
    }

    char *nomeCidade = (char *)malloc(256 * sizeof(char));
    if (nomeCidade) {
        strcpy(nomeCidade, estrada->C[cidadeIndex].Nome);
    }

    free(estrada->C);
    free(estrada);
    return nomeCidade;
}

// Função principal para testar as implementações.
int main() {
    const char *nomeArquivo = "entrada.txt";

    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    printf("Menor vizinhança: %.2f\n", menorVizinhanca);

    char *cidade = cidadeMenorVizinhanca(nomeArquivo);
    if (cidade) {
        printf("Cidade com menor vizinhança: %s\n", cidade);
        free(cidade);
    }

    return 0;
}
