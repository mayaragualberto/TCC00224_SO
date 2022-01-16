#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h> // Para usar o syscall
#include <stdlib.h>
#include <vector>
#include <stdbool.h>
#include <time.h>      // Para calcular o tempo de execução
#include <unistd.h>    // Para colocar pausa entre impressões
#include <semaphore.h> // Para utilizar semaforo

#define TAM 5

int *vectorImparesSem;
int *vectorImpares;
int *vectorImparesSemTh;

int *vectorNaoMultiCincoSem;
int *vectorNaoMultiCinco;
int *vectorNaoMultiCincoSemTh;

// Verificação se os resultados estão corretos:

/* Utilizando duas threads e com utilização de semáforos:
---> O tempo de execução obtido foi maior que os outros programas. */

sem_t pares_lock, multiCinco_lock;

void *removeParesSem(void *vectorRandRecebido)
{
    static int s = 0;
    sem_wait(&pares_lock);
    int *vectorRand = (int *)vectorRandRecebido;
    int qtdImpares = 0;
    // Calcular o tamanho do vetor de acordo com a quantidade de números ímpares
    for (int i = 0; i <= TAM; i++)
    {
        if (vectorRand[i] % 2 != 0)
        {
            qtdImpares++;
        }
    }
    // Cria um vetor com o tamanho da quantidade de números ímpares
    vectorImparesSem = (int *)malloc(sizeof *vectorImparesSem * qtdImpares);
    // Preenche o vetor com os números ímpares, ou seja, remove os pares
    int j = 0;
    for (int i = 0; i < TAM; i++)
    {
        if (vectorRand[i] % 2 != 0)
        {
            vectorImparesSem[j] = vectorRand[i];
            j++;
        }
    }
    int op;
    printf("\nVisualizar vetor apos remocao dos multiplos de 2? [1-Sim/2-Nao]: ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
    {
        // Imprime os elementos do vetor para verificar se foi criado corretamente
        printf("Resultado --> ");
        for (int i = 0; i < qtdImpares; i++)
        {
            printf("%d ", vectorImparesSem[i]);
        }
        break;
    }
    case 2:
    {
        break;
    }
    default:
    {
        printf("\nOpcao invalida! Gentileza reiniciar programa.\n");
        break;
    }
    }
    sem_post(&pares_lock);
    return 0;
}

void *removeMultiCincoSem(void *vectorRandRecebido)
{
    static int s = 0;
    sem_wait(&multiCinco_lock);
    int *vectorRand = (int *)vectorRandRecebido;
    int qtdNaoMultiCinco = 0;
    // Calcular o tamanho do vetor de acordo com a quantidade de números que não são múltiplos de cinco
    for (int i = 0; i <= TAM; i++)
    {
        if (vectorRand[i] % 5 != 0)
        {
            ++qtdNaoMultiCinco;
        }
    }
    // Cria um vetor com o tamanho da quantidade de números que não são múltiplos de cinco
    vectorNaoMultiCincoSem = (int *)malloc(sizeof *vectorNaoMultiCincoSem * qtdNaoMultiCinco);
    // Preenche o vetor com os números que não forem múltiplos de cinco
    int j = 0;
    for (int i = 0; i < TAM; i++)
    {
        if (vectorRand[i] % 5 != 0)
        {
            vectorNaoMultiCincoSem[j] = vectorRand[i];
            j++;
        }
    }

    int op;
    printf("\nVisualizar vetor apos remocao dos multiplos de 5? [1-Sim/2-Nao]: ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
    {
        // Imprime os elementos do vetor para verificar se foi criado corretamente
        printf("Resultado --> ");
        for (int i = 0; i < qtdNaoMultiCinco - 1; i++)
        {
            printf("%d ", vectorNaoMultiCincoSem[i]);
        }
        break;
    }
    case 2:
    {
        break;
    }
    default:
    {
        printf("\nOpcao invalida! Gentileza reiniciar programa.\n");
        break;
    }
    }
    sem_post(&multiCinco_lock);
    return 0;
}

/* Utilizando duas threads e sem utilização de semáforos:
---> O tempo de execução obtido foi menor que o programa com semáforos e maior que sem threads.: */

void *removePares(void *vectorRandRecebido)
{
    int *vectorRand = (int *)vectorRandRecebido;
    int qtdImpares = 0;
    // Calcular o tamanho do vetor de acordo com a quantidade de números ímpares
    for (int i = 0; i <= TAM; i++)
    {
        if (vectorRand[i] % 2 != 0)
        {
            qtdImpares++;
        }
    }
    // Cria um vetor com o tamanho da quantidade de números ímpares
    vectorImpares = (int *)malloc(sizeof *vectorImpares * qtdImpares);
    // Preenche o vetor com os números ímpares, ou seja, remove os pares
    int j = 0;
    for (int i = 0; i < TAM; i++)
    {
        if (vectorRand[i] % 2 != 0)
        {
            vectorImpares[j] = vectorRand[i];
            j++;
        }
    }
    int op;
    printf("\nVisualizar vetor apos remocao dos multiplos de 2? [1-Sim/2-Nao]: ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
    {
        // Imprime os elementos do vetor para verificar se foi criado corretamente
        printf("Resultado --> ");
        for (int i = 0; i < qtdImpares; i++)
        {
            printf("%d ", vectorImpares[i]);
        }
        break;
    }
    case 2:
    {
        break;
    }
    default:
    {
        printf("\nOpcao invalida! Gentileza reiniciar programa.\n");
        break;
    }
    }
    return 0;
}

void *removeMultiCinco(void *vectorRandRecebido)
{
    int *vectorRand = (int *)vectorRandRecebido;
    int qtdNaoMultiCinco = 0;
    // Calcular o tamanho do vetor de acordo com a quantidade de números que não são múltiplos de cinco
    for (int i = 0; i <= TAM; i++)
    {
        if (vectorRand[i] % 5 != 0)
        {
            ++qtdNaoMultiCinco;
        }
    }
    // Cria um vetor com o tamanho da quantidade de números que não são múltiplos de cinco
    vectorNaoMultiCinco = (int *)malloc(sizeof *vectorNaoMultiCinco * qtdNaoMultiCinco);
    // Preenche o vetor com os números que não forem múltiplos de cinco
    int j = 0;
    for (int i = 0; i < TAM; i++)
    {
        if (vectorRand[i] % 5 != 0)
        {
            vectorNaoMultiCinco[j] = vectorRand[i];
            j++;
        }
    }

    int op;
    printf("\nVisualizar vetor apos remocao dos multiplos de 5? [1-Sim/2-Nao]: ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
    {
        // Imprime os elementos do vetor para verificar se foi criado corretamente
        printf("Resultado --> ");
        for (int i = 0; i < qtdNaoMultiCinco - 1; i++)
        {
            printf("%d ", vectorNaoMultiCinco[i]);
        }
        break;
    }
    case 2:
    {
        break;
    }
    default:
    {
        printf("\nOpcao invalida! Gentileza reiniciar programa.\n");
        break;
    }
    }
    return 0;
}

/* Utilizando duas threads e sem utilização de semáforos:
---> O tempo de execução obtido foi menor que a execução sem thread. */

void *removeParesSemTh(void *vectorRandRecebido)
{
    int *vectorRand = (int *)vectorRandRecebido;
    int qtdImpares = 0;
    // Calcular o tamanho do vetor de acordo com a quantidade de números ímpares
    for (int i = 0; i <= TAM; i++)
    {
        if (vectorRand[i] % 2 != 0)
        {
            qtdImpares++;
        }
    }
    // Cria um vetor com o tamanho da quantidade de números ímpares
    vectorImparesSemTh = (int *)malloc(sizeof *vectorImparesSemTh * qtdImpares);
    // Preenche o vetor com os números ímpares, ou seja, remove os pares
    int j = 0;
    for (int i = 0; i < TAM; i++)
    {
        if (vectorRand[i] % 2 != 0)
        {
            vectorImparesSemTh[j] = vectorRand[i];
            j++;
        }
    }
    int op;
    printf("\nVisualizar vetor apos remocao dos multiplos de 2? [1-Sim/2-Nao]: ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
    {
        // Imprime os elementos do vetor para verificar se foi criado corretamente
        printf("Resultado --> ");
        for (int i = 0; i < qtdImpares; i++)
        {
            printf("%d ", vectorImparesSemTh[i]);
        }
        break;
    }
    case 2:
    {
        break;
    }
    default:
    {
        printf("\nOpcao invalida! Gentileza reiniciar programa.\n");
        break;
    }
    }
    return 0;
}

void *removeMultiCincoSemTh(void *vectorRandRecebido)
{
    int *vectorRand = (int *)vectorRandRecebido;
    int qtdNaoMultiCinco = 0;
    // Calcular o tamanho do vetor de acordo com a quantidade de números que não são múltiplos de cinco
    for (int i = 0; i <= TAM; i++)
    {
        if (vectorRand[i] % 5 != 0)
        {
            ++qtdNaoMultiCinco;
        }
    }
    // Cria um vetor com o tamanho da quantidade de números que não são múltiplos de cinco
    vectorNaoMultiCincoSemTh = (int *)malloc(sizeof *vectorNaoMultiCincoSemTh * qtdNaoMultiCinco);
    // Preenche o vetor com os números que não forem múltiplos de cinco
    int j = 0;
    for (int i = 0; i < TAM; i++)
    {
        if (vectorRand[i] % 5 != 0)
        {
            vectorNaoMultiCincoSemTh[j] = vectorRand[i];
            j++;
        }
    }

    int op;
    printf("\nVisualizar vetor apos remocao dos multiplos de 5? [1-Sim/2-Nao]: ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
    {
        // Imprime os elementos do vetor para verificar se foi criado corretamente
        printf("Resultado --> ");
        for (int i = 0; i < qtdNaoMultiCinco - 1; i++)
        {
            printf("%d ", vectorNaoMultiCincoSemTh[i]);
        }
        break;
    }
    case 2:
    {
        break;
    }
    default:
    {
        printf("\nOpcao invalida! Gentileza reiniciar programa.\n");
        break;
    }
    }
    return 0;
}

int verifica(int *v1, int *v2)
{
    if (*v1 == *v2)
    {
        printf("\n--> Sao iguais!");
    }
    else
    {
        printf("\n--> Sao diferentes!");
    }
    return 0;
}

int main()
{
    pthread_t t1, t2;
    printf("**** Parte 2 *****\n");
    sleep(1);
    // Inicia um intervalo randômico
    srand(time(NULL));
    int vectorRand[TAM];
    printf("Vetor de tamanho %d criado. ", TAM);

    char view;
    printf("Deseja visualizar os numeros do vetor? [S/N]: ");
    scanf("%c", &view);
    switch (view)
    {
    case 'N':
    {
        break;
    }
    case 'S':
    {
        // Imprime os elementos do vetor para verificar se foi criado corretamente
        printf("\nOs numeros aleatorios criados foram:\n");
        for (int i = 0; i < TAM; i++)
        {
            vectorRand[i] = rand() % 100 + 1;
            printf("%d ", vectorRand[i]);
        }
        break;
    }
    default:
    {
        printf("Opcao invalida!\n");
        printf("Gentileza reiniciar programa.\n");
        break;
    }
    }
    sleep(1);
    int opcao;
    printf("\n\n*** Escolha entre as opcoes abaixo:\n");
    printf("1 - Programa COM threads COM semaforo;\n");
    printf("2 - Programa COM threads SEM semaforo;\n");
    printf("3 - Programa SEM threads.\n");
    printf("4 - Programa automatico para comparar resultados.\n");
    printf("Digite a opcao: ");

    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
    {
        printf("\n\n***Opcao 1 selecionada: Programa COM threads COM semaforo.\n\n");

        clock_t Ticks[2];
        Ticks[0] = clock();

        sem_init(&pares_lock, 0, 1);
        sem_init(&multiCinco_lock, 0, 1);

        printf("\n\nRemovendo os numeros pares do vetor...\n");
        pthread_create(&t1, NULL, &removeParesSem, (void *)vectorRand);
        pthread_join(t1, NULL);

        printf("\n\nRemovendo os numeros multiplos de 5 do vetor...\n");
        pthread_create(&t2, NULL, &removeMultiCincoSem, (void *)vectorRand);
        pthread_join(t2, NULL);

        sem_destroy(&pares_lock);
        sem_destroy(&multiCinco_lock);

        // Medição do tempo de execução gasto
        printf("\n\n--> O tempo final de execucao do programa foi:\n");
        Ticks[1] = clock();
        double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
        printf("Tempo gasto: %g ms.\n\n\n", Tempo);
        getchar();

        pthread_exit(NULL);

        return 0;

        break;
    }
    case 2:
    {
        printf("\n\n***Opcao 2 selecionada: Programa COM threads SEM semaforo.\n\n");

        clock_t Ticks[2];
        Ticks[0] = clock();

        printf("\n\nRemovendo os numeros pares do vetor...\n");
        pthread_create(&t1, NULL, &removePares, (void *)vectorRand);
        pthread_join(t1, NULL);

        printf("\n\nRemovendo os numeros multiplos de 5 do vetor...\n");
        pthread_create(&t2, NULL, &removeMultiCinco, (void *)vectorRand);
        pthread_join(t2, NULL);

        // Medição do tempo de execução gasto
        printf("\n\n--> O tempo final de execucao do programa foi:\n");
        Ticks[1] = clock();
        double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
        printf("Tempo gasto: %g ms.\n", Tempo);
        getchar();

        pthread_exit(NULL);

        return 0;

        break;
    }
    case 3:
    {
        printf("\n\n***Opcao 3 selecionada: Programa SEM threads.\n\n");

        clock_t Ticks[2];
        Ticks[0] = clock();

        removeParesSemTh(vectorRand);
        removeMultiCincoSemTh(vectorRand);

        // Medição do tempo de execução gasto
        printf("\n\n--> Tempo de execucao:\n");
        Ticks[1] = clock();
        double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
        printf("Tempo gasto: %g ms.\n", Tempo);
        getchar();

        return 0;

        break;
    }
    case 4:
    {
        printf("\n\n***Opcao 4 selecionada: Programa automatico.\n\n");

        // Programa COM threads COM semaforo
        printf("\n--> Programa COM threads COM semaforo:\n");
        clock_t Tempo_1[2];
        Tempo_1[0] = clock();

        sem_init(&pares_lock, 0, 1);
        sem_init(&multiCinco_lock, 0, 1);
        pthread_create(&t1, NULL, &removeParesSem, (void *)vectorRand);
        pthread_join(t1, NULL);
        pthread_create(&t2, NULL, &removeMultiCincoSem, (void *)vectorRand);
        pthread_join(t2, NULL);
        sem_destroy(&pares_lock);
        sem_destroy(&multiCinco_lock);

        // Medição do tempo de execução gasto
        Tempo_1[1] = clock();
        double TFinal_1 = (Tempo_1[1] - Tempo_1[0]) * 1000.0 / CLOCKS_PER_SEC;
        printf("\nTempo gasto: %g ms.\n\n", TFinal_1);
        getchar();

        // Programa COM threads SEM semaforo
        printf("\n--> Programa COM threads sem semaforo:\n");
        clock_t Tempo_2[2];
        Tempo_2[0] = clock();

        pthread_create(&t1, NULL, &removePares, (void *)vectorRand);
        pthread_join(t1, NULL);
        pthread_create(&t2, NULL, &removeMultiCinco, (void *)vectorRand);
        pthread_join(t2, NULL);

        // Medição do tempo de execução gasto
        Tempo_2[1] = clock();
        double TFinal_2 = (Tempo_2[1] - Tempo_2[0]) * 1000.0 / CLOCKS_PER_SEC;
        printf("\nTempo gasto: %g ms.\n", TFinal_2);
        getchar();

        // Programa SEM threads
        printf("\n--> Programa SEM threads:\n");
        clock_t Tempo_3[2];
        Tempo_3[0] = clock();

        removeParesSemTh(vectorRand);
        removeMultiCincoSemTh(vectorRand);

        // Medição do tempo de execução gasto
        Tempo_3[1] = clock();
        double TFinal_3 = (Tempo_3[1] - Tempo_3[0]) * 1000.0 / CLOCKS_PER_SEC;
        printf("\nTempo gasto: %g ms.\n", TFinal_3);
        getchar();

        // Comparação dos resultados
        printf("\n--> Comparacao dos vetores dos programas:");
        printf("\n\n->Remocao de numeros pares:\n ");

        printf("\nVetor com thread + semaforo e vetor sequencial sao iguais?");
        verifica(vectorImparesSem, vectorImparesSemTh);
        printf("\nVetor com thread e vetor sequencial sao iguais?");
        verifica(vectorImpares, vectorImparesSemTh);

        printf("\n\n->Remocao de numeros multiplos de cinco:\n ");

        printf("\nVetor com thread + semaforo e vetor sequencial sao iguais?");
        verifica(vectorNaoMultiCincoSem, vectorNaoMultiCincoSemTh);
        printf("\nVetor com thread e vetor sequencial sao iguais?");
        verifica(vectorNaoMultiCinco, vectorNaoMultiCincoSemTh);

        printf("\n\nFim.");

        return 0;

        break;
    }
    default:
    {
        printf("Opcao invalida! Gentileza reiniciar programa.\n");
        break;
    }
    }
}