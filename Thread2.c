#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TAM 100000

sem_t sem;

int vetor[TAM];

void preenche(int *p, int qtd);
void *Remove_Pares(void *p);
void *Remove_MC(void *p);
int Reorganiza(int *p, int qtd);
void avalia(int *p, int tam);

void preenche(int *p, int qtd){
    
    for (int i = 0; i <= qtd-1; i++){
        *p = rand() % 100;
        *p++;
    }
    
}
/*Todos os numeros pares no vetor, serao substituidos por -1 */
void *Remove_Pares(void *p){
    
    printf("Thread 1 executando...\n");
    
    int *vetor = p;
    
    for (int i = TAM-1; i >= 0; i--){
        sem_wait(&sem);
        int num = *vetor;
        if (num%2 == 0){
            *vetor = -1;
        }
        //printf("%d \n", *vetor);
        *vetor--;
        sem_post(&sem);
    }
    
}

/*Todos os numeros multiplos de 5, serao substituidos por -1 */
void *Remove_MC(void *p){
    
    printf("Thread 2 executando...\n");
    
    int *vetor = p;
    
    for (int i = TAM-1; i >= 0; i--){
        sem_wait(&sem);
        int num = *vetor;
        if (num%5 == 0){
            *vetor = -1;
        }
        //printf("%d \n", *vetor);
        *vetor--;
        sem_post(&sem);
    }
    
}

// Função para retornar a quantidade de elementos válidos no vetor
int Reorganiza(int *p, int qtd){
    
    int *pt = p;
    int tam = qtd;
    int *busca;
    int *ultimo = (pt+qtd-1);
    
    
    /*Sera percorrido o vetor todo o vetor, buscando organizar os numeros*/
    
            
    for (int i = 0; i <= qtd-1; i++){

        /*Se o numero armazenado no ponteiro "pt" for -1, sera percorrido o vetor para encontrar
        o proximo elemento do vetor que nao e -1, ao encontrar, este valor sera passado para "pt"
        e o a posiçao do vetor que tinha um numero valido, recebera -1*/
        
        if (*pt == -1){
            busca = pt;
            
            /*Acessa o vetor e busca o proximo valor valido (Diferente de -1), caso acesse o ultimo
            elemento do vetor, e usado break para que busca nao acesse elementos fora do vetor*/
            while (*busca == -1){
                busca == busca++;
                if (busca == ultimo){
                    break;
                }
            }
            
            //Troca dos valores
            *pt = *busca;
            pt++;
            *busca = -1;
            
        }else{
            //Caso o numero em "pt" seja valido, o vetor vai incrementar
            pt++;
        }
    
    }
    
    //Pt recebe o endereco da cabeca do vetor
    pt = p;
    
    //For para contar a quantidade de elementos invalidos e diminuir o tamanho do vetor
    for (int i = 0; i <= qtd-1; i++){
        if (*pt <= 0){
            tam--;
        }
        pt++;
    }
    
    return tam-1;
    
}

//Funcao para ler o vetor e avaliar se esta valido
void avalia(int *p, int tam){
    
    int *pt = p;
    
    for (int i = 0; i<=tam; i++){
        if (*pt%2 == 0 || *pt%5 == 0){
            printf("VALIDAÇÃO INCORRETA\n ");
            break;
        }
        pt++;
    }
    printf("VALIDAÇÃO CORRETA\n ");
}

int main()
{
    int qtd = 0;
    pthread_t Thread_1, Thread_2;
    sem_init(&sem, 0, 1);
    
    preenche(&vetor[0], TAM);
    
    /*
    for (int i = 0; i<= TAM-1; i++){
        printf("%d \n", vetor[i]);
    }
    */

    pthread_create(&Thread_1, NULL, Remove_Pares, &vetor[TAM-1]);
    pthread_create(&Thread_2, NULL, Remove_MC, &vetor[TAM-1]);
    pthread_join(Thread_1, NULL);
    pthread_join(Thread_2, NULL);

    qtd = Reorganiza(&vetor[0], TAM);
    avalia(&vetor[0], qtd);
    
    
    //Imprime o novo vetor
   /* printf("\n");
    for (int i = 0; i<= qtd; i++){
        printf("%d \n", vetor[i]);
    }
    printf("\n");*/
    
    return 0;
}


