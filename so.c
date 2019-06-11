#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int count = 0;
#define COUNT_MAX 10 //limite do contador
 
pthread_mutex_t var_mutex; //declaração de um mutex
 
 
void *count_func(void *id_num){

	int id = (int)id_num;
 
    while(count < COUNT_MAX){
        pthread_mutex_lock (&var_mutex);
        count++;        
        printf("Thread: %ld Contador: %d\n", id, count);
        pthread_mutex_unlock (&var_mutex);
 
        sleep(rand() % 3);
 
    }
    pthread_exit(NULL);
}
 
 
int main(){
    pthread_t thread_1, thread_2; //declarando as threads
    int create; 
    int num; //id da thread

	//thread 1
    pthread_mutex_init(&var_mutex, NULL); //instanciando o mutex com os atributos padrões (null)
    num = 1; //id da thread 1
    printf("Instanciando a thread %ld\n", num);
    create = pthread_create(&thread_1, NULL, count_func, (void *)num); //instanciando a thread passando a função a ser executada por ela
 
	//mesma lógica para a thread 2
    num = 2;
    printf("Instanciando a thread %ld\n", num);
    create = pthread_create(&thread_2, NULL, count_func, (void *)num);
 
 
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    printf("\nContagem finalizada\n");
 
    pthread_mutex_destroy(&var_mutex); //desalocação do mutex
 
    return 0;
}