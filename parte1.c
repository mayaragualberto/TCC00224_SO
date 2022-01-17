#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h> // Para usar o syscall
#include <stdlib.h>

void *funcaoThread(void *threadid)
{
    long numDaThread = (long)threadid;
    numDaThread++;
    char nomeDaThread[12];
    // Concatenar o número com o nome da thread:
    if (numDaThread<10) {snprintf(nomeDaThread,12,"thread_0%ld",numDaThread);}
    else if (numDaThread>=10) {snprintf(nomeDaThread,12,"thread_%ld",numDaThread);}

    /* Utilizando pthread_self() para obter o ID:
    ---> O valor retornado é chamado de ID de thread POSIX*/
    printf("Eu sou a thread %s e meu ID é %lu.\n", nomeDaThread, pthread_self());

    /* Utilizando o gettid() para obter o ID:
    ---> Precisa incluir a biblioteca #include <sys/syscall.h>
    ---> 2 formas de obter: chamando a instrução do system call ou usando o gettid()
    ---> O valor rertonado é o diferente, referente ao ID de thread do chamador, valor int do tipo pid_t */

    // Forma 1 do gettid:
    //long tid = syscall(SYS_gettid);
    //printf("Eu sou a thread %s e meu ID é %lu\n", nomeDaThread, tid);

    // Forma 2 do gettid:
    //printf("Eu sou a thread %s e meu ID é %u\n", nomeDaThread, gettid());
    pthread_exit(NULL);
}

int main()
{
    printf("**** Parte 1 *****\n");
    printf("Insira a quantidade de threads a serem criadas:\n");
    int numeroDeThreads;
    scanf("%d",&numeroDeThreads);
    pthread_t threads[numeroDeThreads];
    long t;
    int rc;
    for (t = 0; t < numeroDeThreads; t++)
    {
        rc = pthread_create(&threads[t], NULL, funcaoThread, (void *)t);
        if (rc)
        {
            printf("Erro. %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
