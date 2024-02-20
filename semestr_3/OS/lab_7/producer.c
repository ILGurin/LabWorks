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

int main(){
    const char* sem_name = "/char_code";
    const char* producer_name = "/producerP";
    const char* consumer_name = "/consumerC";

    sem_t* charCodeSemaphore = sem_open(sem_name, O_CREAT, 0777, 0);
    sem_t* producer_sem = sem_open(producer_name, O_CREAT, 0777, 0);
    sem_t* consumer_sem = sem_open(consumer_name, O_CREAT, 0777, 1);

    if (charCodeSemaphore == SEM_FAILED){
        perror("Error creating semaphore");
        exit(EXIT_FAILURE);
    }

    while (1){
        printf("Ожидание...\n");
        sem_wait(consumer_sem);

        char input_char;
        printf("Введите символ: ");
        scanf(" %c", &input_char);

        int charCode = (int)input_char;
        printf("char: %c\n", input_char);

        for (int i = 0; i < charCode; i++){
            sem_post(charCodeSemaphore);
        }

        sem_post(producer_sem);
    }

    if (sem_close(charCodeSemaphore) == -1){
        perror("Error closing semaphore");
        exit(EXIT_FAILURE);
    }
    return 0;
}