#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int main(){
    const char* sem_name = "/char_code";
    const char* producer_name = "/producerP";
    const char* consumer_name = "/consumerC";

    sem_t* charCodeSemaphore = sem_open(sem_name, O_CREAT, 0777, 0);
    sem_t* producer_sem = sem_open(producer_name, O_CREAT, 0777, 0);
    sem_t* consumer_sem = sem_open(consumer_name, O_CREAT, 0777, 0);

    srand(time(NULL));
    int random_int;

    if (charCodeSemaphore == SEM_FAILED){
        perror("Error creating semaphore");
        exit(EXIT_FAILURE);
    }

    while (1){
        printf("Ожидание...\n");
        sem_wait(producer_sem);

        int charCode;
        sem_getvalue(charCodeSemaphore, &charCode);
        char c = (char)charCode;
        random_int = (rand() % 10) + 1;
        for (int i = 0; i < random_int; i++){
            printf("Символ: %c\n", c);
        }
        
        for (int i = 0; i < charCode; i++){
            sem_wait(charCodeSemaphore);
        }
        sem_post(consumer_sem);
    }
    return 0;
}