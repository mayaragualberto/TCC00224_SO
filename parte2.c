#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h> // Para usar o syscall
#include <stdlib.h>
#include <vector>
#include <time.h>   // Para calcular o tempo de execução
#include <unistd.h> // Para colocar pausa entre impressões

#define TAM 10

/* Utilizando duas threads e com utilização de semáforos:
--->
--->
---> O tempo de execução obtido com todas as impressões foi de: */

void *removeParesSem(void *vectorRandRecebido)
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
    int vectorImpares[qtdImpares];
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
    printf("\nDeseja visualizar os numeros do vetor apos remocao? [1 - Sim / 2 - Nao]: ");
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

void *removeMultiCincoSem(void *vectorRandRecebido)
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
    int vectorNaoMultiCinco[qtdNaoMultiCinco];
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
    printf("\nDeseja visualizar os numeros do vetor apos remocao? [1 - Sim / 2 - Nao]: ");
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

// {
//     long numDaThread = (long)threadid;
//     printf("Eu sou a thread %s e meu ID é %lu\n", nomeDaThread, pthread_self());
//     pthread_exit(NULL);
// }

/* Utilizando duas threads e sem utilização de semáforos:
--->
--->
---> O tempo de execução obtido com todas as impressões foi de: */

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
    int vectorImpares[qtdImpares];
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
    printf("\nDeseja visualizar os numeros do vetor apos remocao? [1 - Sim / 2 - Nao]: ");
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
    int vectorNaoMultiCinco[qtdNaoMultiCinco];
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
    printf("\nDeseja visualizar os numeros do vetor apos remocao? [1 - Sim / 2 - Nao]: ");
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
    printf("Digite a opcao: ");

    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
    {
        printf("\n\n***Opcao 1 selecionada: Programa COM threads COM semaforo.\n\n");

        printf("\n\nRemovendo os numeros pares do vetor...\n");
        pthread_create(&t1, NULL, &removeParesSem, (void *)vectorRand);
        pthread_join(t1, NULL);

        printf("\n\nRemovendo os numeros multiplos de 5 do vetor...\n");
        pthread_create(&t2, NULL, &removeMultiCincoSem, (void *)vectorRand);
        pthread_join(t2, NULL);

        // Medição do tempo de execução gasto
        printf("\n\n--> O tempo final de execucao do programa foi:\n");
        clock_t Ticks[2];
        Ticks[0] = clock();
        Ticks[1] = clock();
        double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
        printf("Tempo gasto: %g ms.\n\n\n", Tempo);
        printf("Enter para sair.\n");
        getchar();
        return 0;

        pthread_exit(NULL);

        break;
    }
    case 2:
    {
        printf("\n\n***Opcao 2 selecionada: Programa COM threads SEM semaforo.\n\n");

        printf("\n\nRemovendo os numeros pares do vetor...\n");
        pthread_create(&t1, NULL, &removePares, (void *)vectorRand);
        pthread_join(t1, NULL);

        printf("\n\nRemovendo os numeros multiplos de 5 do vetor...\n");
        pthread_create(&t2, NULL, &removeMultiCinco, (void *)vectorRand);
        pthread_join(t2, NULL);

        // Medição do tempo de execução gasto
        printf("\n\n--> O tempo final de execucao do programa foi:\n");
        clock_t Ticks[2];
        Ticks[0] = clock();
        Ticks[1] = clock();
        double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
        printf("Tempo gasto: %g ms.\n\n\n", Tempo);
        printf("Enter para sair.\n");
        getchar();
        return 0;

        pthread_exit(NULL);

        break;
    }
    case 3:
    {

        // Medição do tempo de execução gasto
        printf("\n\n--> O tempo final de execucao do programa foi:\n");
        clock_t Ticks[2];
        Ticks[0] = clock();
        Ticks[1] = clock();
        double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
        printf("Tempo gasto: %g ms.\n\n\n", Tempo);
        sleep(1);
        printf("Enter para sair.\n");
        getchar();
        return 0;
        break;
    }
    default:
    {
        printf("Opcao invalida!\n");
        printf("Gentileza reiniciar programa.\n");
        break;
    }
    }
}
