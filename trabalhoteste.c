#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMO_STUDANTES 100
#define TAMANHO_MAXIMO_NOME 100
#define MEDIA_MAXIMA 5

typedef struct
{
    char nome[TAMANHO_MAXIMO_NOME];
    char celular[15];
    char curso[TAMANHO_MAXIMO_NOME];
    float media[MEDIA_MAXIMA];
    int num_media;
} estudante;

float calcularmedia(float media[], int num_media)
{
    float soma_media = 0;
    for (int i = 0; i < num_media; i++)
    {
        soma_media += media[i];
    }
    return soma_media / num_media;
}

int main()
{
    FILE *arquivo_entrada, *arquivo_saida;
    char arquivo_entrada_nome[] = "DadosEntrada.csv";
    char arquivo_saida_nome[] = "SituacaoFinal.csv";
    estudante estudantes[MAXIMO_STUDANTES];
    int num_estudantes = 0;

    
    arquivo_entrada = fopen(arquivo_entrada_nome, "r");
    if (arquivo_entrada == NULL)
    {
        printf("Erro ao abrir arquivo de entrada.\n");
        return 1;
    }

    // pular a primeira linha do arquivo de input
    char linha[TAMANHO_MAXIMO_NOME + 35];
    if (fgets(linha, sizeof(linha), arquivo_entrada) == NULL)
    {
        printf("Error: o arquivo de entrada está vazio ou contém dados inválidos.\n");
        return 1;
    }

    
    while (fscanf(arquivo_entrada, "%[^,],%[^,],%[^,],", estudantes[num_estudantes].nome, estudantes[num_estudantes].celular, estudantes[num_estudantes].curso) != EOF && num_estudantes < MAXIMO_STUDANTES)
    {
        int i = 0;
        while (fscanf(arquivo_entrada, "%f,", &estudantes[num_estudantes].media[i]) == 1)
        {
            i++;
        }
        estudantes[num_estudantes].num_media = i;
        num_estudantes++;
    }

    // fechar o arquivo de input
    fclose(arquivo_entrada);

    // abrir o arquivo de saida
    arquivo_saida = fopen(arquivo_saida_nome, "w");
    if (arquivo_saida == NULL)
    {
        printf("Error creating output file.\n");
        return 1;
    }

    // escrever informaçoes dos estudantes no arquivo de saida
    for (int i = 0; i < num_estudantes; i++)
    {
        float media = calcularmedia(estudantes[i].media, estudantes[i].num_media);
        char status[20];
        if (media >= 7.0)
            strcpy(status, "APPROVADO");
        else
            strcpy(status, "REPROVADO");
        fprintf(arquivo_saida, "%s,%.2f,%s\n", estudantes[i].nome, media, status);
    }

    // fechar o arquivo de output
    fclose(arquivo_saida);

    printf("Arquivo SituacaoFinal.csv gerado com sucesso.\n");

    return 0;
}
