#include <stdio.h>
#include <unistd.h> // Para colocar pausa entre impressões
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <vector>
#include <time.h> 

#define TAM 10

int globalVar; /* A global variable*/
int *vectorImpares;
int *vectorNaoMultiCinco;
int vectorRand[TAM];

int main(void)
{
    printf("**** Parte 3 *****\n");
    sleep(1);
    // Inicia um intervalo randômico
    srand(time(NULL));
    printf("Vetor de tamanho %d criado. ", TAM);

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
    int localVar = 0;
    int *p = (int *)malloc(2);
    pid_t filho_PID = fork();

    // Putting value at allocated address
    *p = 0;

    if (filho_PID >= 0) // fork was successful
    {
        if (filho_PID == 0) // Processo filho - remove múltiplos de cinco
        {
            printf("Processo filho. Endereço de memória alocado: %p\n",vectorRand);

            int qtdNaoMultiCinco = 0;
            // Calcular o tamanho do vetor de acordo com a quantidade de números ímpares
            for (int i = 0; i <= TAM; i++)
            {
                if (vectorRand[i] % 5 != 0)
                {
                    qtdNaoMultiCinco++;
                }
            }
            // Cria um vetor com o tamanho da quantidade de números ímpares
            vectorNaoMultiCinco = (int *)malloc(sizeof *vectorNaoMultiCinco * qtdNaoMultiCinco);
            // Preenche o vetor com os números ímpares, ou seja, remove os pares de trás para frente
            int j = qtdNaoMultiCinco - 1;
            for (int i = TAM - 1; i >= 0; i--)
            {
                if (vectorRand[i] % 5 != 0)
                {
                    vectorNaoMultiCinco[j] = vectorRand[i];
                    j--;
                    printf("MEU CU");
                }
            }
        }
        else // Processo pai - remove pares
        {
            printf("Processo pai. Endereço de memória alocado: %p\n",vectorRand);

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
            // Preenche o vetor com os números ímpares, ou seja, remove os pares de trás para frente
            int j = qtdImpares - 1;
            for (int i = TAM - 1; i >= 0; i--)
            {
                if (vectorRand[i] % 2 != 0)
                {
                    vectorImpares[j] = vectorRand[i];
                    j--;
                }
            }
            printf("Processo pai. Endereço de memória alocado: %p\n",vectorRand);
        }
    }

    else // fork falhou
    {
        printf("\n Fork falhou. Gentileza reiniciar o programa.\n");
        return 0;
    }

    return 0;
}
