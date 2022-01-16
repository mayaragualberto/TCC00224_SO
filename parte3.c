#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h> // Para usar o syscall
#include <stdlib.h>
#include <vector>

#define TAM 100000

int main ()
{
    // Inicia um intervalo randômico
    srand(time(NULL));
    std::vector <int> vectorRand(TAM); 
    // Imprime os elementos do vetor para verificar se foi criado corretamente
    for (int i=0; i<TAM; i++)
    {
        vectorRand[i] = rand()%100+1;
        printf("%d\n", vectorRand[i]);
    }
    
}