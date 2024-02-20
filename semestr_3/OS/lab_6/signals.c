#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>


void sigusr(){
    signal(SIGUSR1, sigusr);
    printf("CHILD: Я получил SIGUSR1\n\n");
}

void sigusr2(){
    signal(SIGUSR2, sigusr2);
    printf("PARENT: Я получил SIGUSR2\n\n");
}


int main(){
    int pid, ppid;

    char str[3][50];
    fgets(str[0], 50, stdin);
    fgets(str[1], 50, stdin);
    fgets(str[2], 50, stdin);


    mqd_t mqID;
    mqID = mq_open("/testmQueue1", O_RDWR | O_CREAT | O_EXCL, 0666, NULL);

    if (mqID < 0){
        if (errno == EEXIST){
            mq_unlink("/testmQueue");
            mqID = mq_open("/testmQueue1", O_RDWR | O_CREAT, 0666, NULL);
        }
        else{
            perror("open message queue error...");
            return -1;
        }
    }


    struct mq_attr mqAttr;
    mq_getattr(mqID, &mqAttr);
    char buf[mqAttr.mq_msgsize];

    if((pid = fork()) < 0){
        perror("fork");
        exit(1);
    }
    else if(pid == 0){ /* child */
    
        char strp[3][50];
        int size[3];

        signal(SIGUSR1, sigusr);
        pause();


        //Принятие первого сообщения
        mq_receive(mqID, buf, mqAttr.mq_msgsize, NULL);
        for(int i = 0; i < sizeof(strp[0]); i++){
            strp[0][i] = buf[i];
        }
        size[0] = strlen(buf);
        printf("Получено сообщение: %s\n", strp[0]);


        mq_receive(mqID, buf, mqAttr.mq_msgsize, NULL);
        for(int i = 0; i < sizeof(strp[1]); i++){
            strp[1][i] = buf[i];
        }
        size[1] = strlen(buf);
        printf("Получено сообщение: %s\n", strp[1]);


        mq_receive(mqID, buf, mqAttr.mq_msgsize, NULL);
        for(int i = 0; i < sizeof(strp[2]); i++){
            strp[2][i] = buf[i];
        }
        size[2] = strlen(buf);
        printf("Получено сообщение: %s\n", strp[2]);

        int max = size[0];
        for (int i = 0; i < 3; i++) {
            if(size[i] > max){
                max = size[i];
            }
        }
        printf("Найден максимальный размер строки\n");

        printf("\nCHILD: отправил SIGUSR2\n\n");
        ppid = getppid();
        kill(ppid, SIGUSR2);

        for(int i = 0; i < 3; i++){
            if(strlen(strp[i]) == max){
                printf("Отправил сообщение с максимальной длиной\n\n");
                mq_send(mqID, strp[i], sizeof(strp[i]), 1);
            }
        }
    }
    else{ /* parent */

        printf("Parent отправил сообщение: %s\n", str[0]);
        mq_send(mqID, str[0], sizeof(str[0]), 1);
        printf("Parent отправил сообщение: %s\n", str[1]);
        mq_send(mqID, str[1], sizeof(str[1]), 1);
        printf("Parent отправил сообщение: %s\n", str[2]);
        mq_send(mqID, str[2], sizeof(str[2]), 1);
        printf("Отправка сообщений окончена \n");
        sleep(1);

        printf("\nPARENT: отправил SIGUSR1\n\n");
        kill(pid, SIGUSR1);

        signal(SIGUSR2, sigusr2);
        pause();

        printf("Получил сообщение с максимальной длиной\n\n");
        mq_receive(mqID, buf, mqAttr.mq_msgsize, NULL);
        printf("Самая длинная строка: %s\n", buf);
    }
}