## <p align='center'> Trabalho de Sistemas Operacionais para Sistemas de Informação 

### <p align='right'> Discente: Mayara Gualberto

### <p align='right'> Docente: Raphael Guerra

---

## Parte 1:

> Premissas:

O programa cria "N" (valor de entrada) threads e imprime na tela.

> Execução:

```sh 
g++ parte1.c -o parte1 -lpthread
```
```sh 
./parte1
```
---

## Parte 2:

> Premissas:
Vetor com 100.000 inteiros aleatórios;
Duas threads:
    -> t1: remove números pares do vetor;
    -> t2: remove números múltiplos de 5.
Programa com threads, com threads e semáforos e sem threads.

> Execução
```sh 
g++ parte2.c -o parte2 -lpthread
```
```sh 
./parte2
```
---

## Parte 3:

> Premissas:
Dois processos:
    Child/filho: remove múltiplos de cinco.
    Parent/pai: remove pares e verifica.
Utilizar memória compartilhada.

> Execução:
```sh 
g++ parte3.c -o parte3 
```
```sh 
./parte3
```