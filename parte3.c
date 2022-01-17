#include <stdio.h>
#include <unistd.h> // Para colocar pausa entre impressões
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdbool.h> // Para utilizar booleano

#define TAM 100000

#define PERMS (S_IRUSR | S_IWUSR)

int main()
{
    printf("**** Parte 3 *****\n");
    int result;
    int shdMemId;
    int shdMemId2;
    int *shdMemRegion;
    int *shdMemRegion2;
    int shdMemSize = 1000000; // Size in # of bytes

    // Criando uma nova região na memória compartilhada
    shdMemId = shmget(IPC_PRIVATE, shdMemSize, IPC_CREAT | 0666);
    if (shdMemId < 0)
    {
        printf("Cannot create shared memory region!\n");
        exit(1);
    }
    printf("ID da memória compartilhada criada é: %i\n", shdMemId);

    // Criando uma nova região na memória compartilhada
    shdMemId2 = shmget(IPC_PRIVATE, shdMemSize, IPC_CREAT | 0666);
    if (shdMemId2 < 0)
    {
        printf("Cannot create shared memory region!\n");
        exit(1);
    }
    printf("ID da memória compartilhada criada é: %i\n", shdMemId2);

    // Attach a new shared memory region
    shdMemRegion = (int *)shmat(shdMemId, NULL, 0);
    if (shdMemRegion == (int *)-1)
    {
        printf("Cannot attach shared memory region!\n");
        exit(1);
    }

    // Attach a new shared memory region
    shdMemRegion2 = (int *)shmat(shdMemId2, NULL, 0);
    if (shdMemRegion2 == (int *)-1)
    {
        printf("Cannot attach shared memory region!\n");
        exit(1);
    }

    // A variável filho_PID armazenará o valor retornado da chamada do fork()
    pid_t filho_PID = fork();
    if (filho_PID >= 0)
    {
        // Se o fork() retornar zero, então significa que é um processo filho
        /*************************************
                        PROCESSO FILHO
        *************************************/
        if (filho_PID == 0) // Processo filho - remove múltiplos de cinco
        {
            // Inicia um intervalo randômico
            srand(time(NULL));
            int vectorRand[TAM];
            int *vectorRandVerifica = (int *)shdMemRegion2;
            printf("Vetor de tamanho %d criado. ", TAM);
            // Criando o vetor com os números aleatórios
            for (int i = 0; i < TAM; i++)
            {
                vectorRand[i] = rand() % 100 + 1;
            }
            // Copiando o vetor de números aleatórios para posterior verificação
            for (int i = 0; i < TAM; i++)
            {
                vectorRandVerifica[i] = vectorRand[i];
            }
            int opcao;
            printf("Deseja visualizar os números do vetor? [1-Sim/2-Não]: ");
            scanf("%d", &opcao);
            switch (opcao)
            {
            case 2:
            {
                break;
            }
            case 1:
            {
                // Imprime os elementos do vetor para verificar se foi criado corretamente
                printf("\nOs números aleatórios criados foram:\n");
                for (int i = 0; i < TAM; i++)
                {
                    printf("%d ", vectorRand[i]);
                }
                break;
            }
            default:
            {
                printf("Opção inválida. Gentileza reiniciar programa.\n");
                break;
            }
            }
            // printf("\nProcesso filho. Endereço de memória alocado: %p\n", vectorRand);
            int qtdNaoMultiCinco = 0;
            // Calcular o tamanho do vetor de acordo com a quantidade de números não múltiplos de cinco
            for (int i = 0; i < TAM; i++)
            {
                if (vectorRand[i] % 5 != 0)
                {
                    qtdNaoMultiCinco++;
                }
            }
            // Passar o vector sem múltiplos de cinco para a memória compartilhada
            int *vectorNaoMultiCinco = (int *)shdMemRegion;
            // Preenche o vetor com os números NÃO múltiplos de cinco de trás para frente
            int j = qtdNaoMultiCinco - 1;
            for (int i = TAM - 1; i >= 0; i--)
            {
                if (vectorRand[i] % 5 != 0)
                {
                    vectorNaoMultiCinco[j] = vectorRand[i];
                    j--;
                }
            }

            // shmdt( shdMemRegion );
        }
        /*************************************
                        PROCESSO PAI
        *************************************/
        else
        {
            wait(NULL); // Pai aguarda processo filho
            int *vectorRandRecebido = (int *)shdMemRegion;
            // Refinar o vector - retirar excedente
            int tamanho = 0;
            for (int i = 0; i < TAM; i++)
            {
                if ((vectorRandRecebido[i]) != 0)
                {
                    tamanho++;
                }
            }
            int vectorRand[tamanho];
            for (int i = 0; i < tamanho; i++)
            {
                vectorRand[i] = vectorRandRecebido[i];
            }
            int qtdImpares = 0;
            // Calcular o tamanho do vetor de acordo com a quantidade de números ímpares
            for (int i = 0; i < tamanho; i++)
            {
                if (vectorRand[i] % 2 != 0)
                {
                    qtdImpares++;
                }
            }
            // Cria um vetor com o tamanho da quantidade de números ímpares
            int vectorImpares[qtdImpares];
            // Preenche o vetor com os números ímpares, ou seja, remove os pares de trás para frente
            int j = qtdImpares - 1;
            for (int i = tamanho - 1; i >= 0; i--)
            {
                if (vectorRand[i] % 2 != 0)
                {
                    vectorImpares[j] = vectorRand[i];
                    j--;
                }
            }
            sleep(1);
            printf("\n\n*Processo pai irá verificar as respostas\n");

            /*************************************
                 VERIFICAÇÃO DOS PROCESSOS
            *************************************/
            int *vectorRandVerifica = (int *)shdMemRegion2;
            int qtdNaoMultiCinco = 0;
            // Calcular o tamanho do vetor de acordo com a quantidade de números que não são múltiplos de cinco
            for (int i = 0; i < TAM; i++)
            {
                if (vectorRandVerifica[i] % 5 != 0)
                {
                    qtdNaoMultiCinco++;
                }
            }
            // Cria um vetor com o tamanho da quantidade de números que não são múltiplos de cinco
            int vectorNaoMultiCincoVerifica[qtdNaoMultiCinco];
            // Preenche o vetor com os números que não forem múltiplos de cinco de trás para frente
            j = qtdNaoMultiCinco - 1;
            for (int i = TAM - 1; i >= 0; i--)
            {
                if (vectorRandVerifica[i] % 5 != 0)
                {
                    vectorNaoMultiCincoVerifica[j] = vectorRandVerifica[i];
                    j--;
                }
            }
            qtdImpares = 0;
            tamanho = qtdNaoMultiCinco;
            // Calcular o tamanho do vetor de acordo com a quantidade de números ímpares
            for (int i = 0; i < tamanho; i++)
            {
                if (vectorNaoMultiCincoVerifica[i] % 2 != 0)
                {
                    qtdImpares++;
                }
            }
            // Cria um vetor com o tamanho da quantidade de números ímpares
            int vectorImparesVerifica[qtdImpares];
            // Preenche o vetor com os números ímpares, ou seja, remove os pares de trás para frente
            j = qtdImpares - 1;
            for (int i = tamanho - 1; i >= 0; i--)
            {
                if (vectorNaoMultiCincoVerifica[i] % 2 != 0)
                {
                    vectorImparesVerifica[j] = vectorNaoMultiCincoVerifica[i];
                    j--;
                }
            }

            // printf("\n\n**VETOR DOS PROCESSOS\n");
            // tamanho = sizeof(vectorImpares) / sizeof(vectorImpares[0]);
            // for (int i = 0; i < tamanho; i++)
            // {
            //     printf("%d ", vectorImpares[i]);
            // }
            // tamanho = sizeof(vectorImparesVerifica) / sizeof(vectorImparesVerifica[0]);
            // printf("\n\n**VETOR SEQUENCIAL\n");
            // for (int i = 0; i < tamanho; i++)
            // {
            //     printf("%d ", vectorImparesVerifica[i]);
            // }

            tamanho = sizeof(vectorImparesVerifica) / sizeof(vectorImparesVerifica[0]);
            printf("\nO vetor obtido por processos é igual ao sequencial?\n");
            bool iguais = true;
            for (int i = 0; i < tamanho; i++)
            {
                if (vectorImpares[i] != vectorImparesVerifica[i])
                {
                    iguais = false;
                    break;
                }
            }
            if (iguais)
            {
                printf("\n--> São iguais!\n");
            }
            else
            {
                printf("\n--> São diferentes!\n");
            }

            printf("\n\nFim.\n");
        }
    }
    else // fork falhou
    {
        printf("\n Fork falhou. Gentileza reiniciar o programa.\n");
    }

    return 0;
}
