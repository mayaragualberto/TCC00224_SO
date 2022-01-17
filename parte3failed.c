#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h> // Para colocar pausa entre impressões

#define TAM 5

static pid_t filha = -2;

int *vectorImpares;      // Vetor sem os numeros pares usando threads
int *vectorImparesSemTh; // Vetor sem os numeros pares sem usar threads

int *vectorNaoMultiCinco;      // Vetor sem os numeros multiplos de cinco usando threads
int *vectorNaoMultiCincoSemTh; // Vetor sem os numeros multiplos de sem usar threads

void *removePares(void *vectorRandRecebido)
{
    int *vectorRand = (int *)vectorRandRecebido;
    int qtdImpares = 0;
    printf("%d:%s iniciando...\n", getpid(), (char *)vectorRandRecebido);

    while (filha == -2)
    {
       sleep(1);
    }

    printf("%d:%s finalizando...\n", getpid(), (char *)vectorRandRecebido);

    return 0;
}

void *removeMultiCinco(void *vectorRandRecebido)
{

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
    pthread_t tid1, tid2;
    printf("**** Parte 3 *****\n");
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

    printf("\n\n***Iniciando programa com processos.\n\n");

    /* Programa COM processos;
    --> fork() cria um processo filho para remover multiplos de 5;
    --> processo pai remove pares e verifica se está correto;
    --> pai sincroniza e espera filho antes de verificar. */
    printf("\n\nRemovendo os numeros pares do vetor...\n");
    pthread_create(&tid1, NULL, removePares, NULL);
    printf("\n\nRemovendo os numeros multiplos de 5 do vetor...\n");
    pthread_create(&tid2, NULL, removePares, NULL);

    filha = fork();

    printf("%d:%s\n", getpid(), "fork()ing completo.");
    sleep(3);

    printf("%d:%s\n", getpid(), "Main thread finalizada");

    pthread_exit(NULL);

    printf("\n\nFim.");

    return 0;
}