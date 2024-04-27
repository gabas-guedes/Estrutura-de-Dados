#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    float x;
    float y;
} ponto;

float areatriangulo(ponto A, ponto B, ponto C)
{
    return fabs((A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)) / 2.0);
}

float areapoligono(ponto vertices[], int numvertices)
{
    float areatotal = 0;
    ponto primeirovertice = vertices[0];

    for (int i = 1; i < numvertices - 1; i++)
    {
        areatotal += areatriangulo(primeirovertice, vertices[i], vertices[i + 1]);
    }
    return areatotal;
}

int main()
{
    int numvertices;

    printf("Digite o numero de vertices do poligono: ");
    scanf("%d", &numvertices);

    ponto *vertices = (ponto *)malloc(numvertices * sizeof(ponto));

    if (vertices == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    printf("Digite as coordenadas dos vertices (formato: x y):\n");
    for (int i = 0; i < numvertices; i++)
    {
        printf("Vertice %d: ", i + 1);
        scanf("%f %f", &vertices[i].x, &vertices[i].y);
    }

    FILE *arquivo;
    char nomearquivo[] = "vertices.txt";

    arquivo = fopen(nomearquivo, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao criar o arquivo.\n");
        return 1;
    }

    fprintf(arquivo, "%d\n", numvertices);
    for (int i = 0; i < numvertices; i++)
    {
        fprintf(arquivo, "%.2f %.2f\n", vertices[i].x, vertices[i].y);
    }

    fclose(arquivo);

    float area = areapoligono(vertices, numvertices);

    printf("A area do poligono e %.2f\n", area);

    free(vertices);
    return 0;
}
