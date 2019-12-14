#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>

void *teste(void *arg){
    
    char *nome = (char*) arg;
    
    printf("Eu sou a %s\n", nome);
    printf("Meu id por pthread_self é %lu e meu id por gettid é %ld\n\n", pthread_self(), syscall(SYS_gettid));


}

int main(int argc, char *argv[])
{

    
    int qtd = atoi(argv[1]);
    qtd--;
    char nome[qtd][20];
    pthread_t thread[qtd];

    for (int i = 0; i <= qtd; i++){
        /*Funcao sprintf esta concatenando "thread" com um valor inteiro e jogando em 
        nome, que e string*/
        sprintf(nome[i], "Thread %d", i);
        /*A thread espera que seja passado um endereco como um  argumento
        ao estar passando um vetor, se esta passando o endereco daquela posicao*/
        pthread_create(&thread[i], NULL, teste, nome[i]);
    }
    
    for (int i = 0; i <= qtd; i++){
        pthread_join(thread[i], NULL);
    }


    return 0;
}

