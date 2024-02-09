#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main() {
    int i;
    int N = -1; 
    while(N <= 0)
    {
        printf("Digite um valor (maior que 0) para o tamanho da base de dados:");
        scanf("%d", &N);
    }
    float dados[N];
    float media = 0.0, sum_desvio = 0.0;

    for (i = 0; i < N; i++) {
        dados[i] = (float)rand() / RAND_MAX;  
    }

    printf("Base de floats: ");
    for(i = 0; i < N; i++)
    {
        printf(" %f ", dados[i]);
    }
    printf("/n");

    #pragma omp parallel for reduction(+:media)
    for (i = 0; i < N; i++) {
        media += dados[i];
    }
    media /= N;

    #pragma omp parallel for reduction(+:sum_desvio)
    for (i = 0; i < N; i++) {
        sum_desvio += (dados[i] - media) * (dados[i] - media);
    }

    float desvio_padrao = sqrt(sum_desvio / N);

    printf("Desvio Padrão: %.6f\n", desvio_padrao);

    return 0;
}
