#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
    pid_t pid;
    printf("Процесс 0 PID = %d PPID = %d\n", getpid(), getppid());

    //Порождение первого процесса
    if((pid = fork()) == -1){
        printf("Ошибка!\n");
    }
    else if(pid == 0){
        printf("Порождение процесса 1 pid = %d PPID = %d\n", getpid(), getppid());

        //Порождение второго процесса
        if((pid = fork()) == -1){
            printf("Ошибка!\n");
        }
        else if(pid == 0){
            printf("Порождение процесса 2 PID = %d PPID = %d\n", getpid(), getppid());

            //Порождение четвёртого процесса
            if((pid = fork()) == -1){
                printf("Ошибка!\n");
            }
            else if(0 == pid){
                printf("Порождение процесса 4 PID = %d PPID = %d\n", getpid(), getppid());
                printf("Завершился процесс 4 PID = %d PPID = %d\n", getpid(), getppid());
                exit(0);
            }

            //Порождение пятого процесса
            if((pid = fork()) == -1){
                printf("Ошибка!\n");
            }
            else if(0 == pid){
                printf("Порождение процесса 5 PID = %d PPID = %d\n", getpid(), getppid());

                //Порождение шестого процесса
                if((pid = fork()) == -1){
                    printf("Ошибка!\n");
                }
                else if(0 == pid){
                    printf("Порождение процесса 6 PID = %d PPID = %d\n", getpid(), getppid());

                    //Порождение седьмого процесса
                    if((pid = fork()) == -1){
                        printf("Ошибка!\n");
                    }
                    else if(0 == pid){
                        printf("Порождиние процесса 7 PID = %d PPID = %d\n", getpid(), getppid());
                        printf("Завершился процесс 7 PID = %d PPID = %d\n", getpid(), getppid());
                        exit(0);
                    }
                    else{
                        sleep(1);
                    }
                    printf("Завершился процесс 6 PID = %d PPID = %d\n", getpid(), getppid());
                    exit(0);
                }
                else{
                    sleep(2);
                }
                printf("Завершился процесс 5 PID = %d PPID = %d\n", getpid(), getppid());
                exit(0);
            }
            else{
                sleep(3);
            }
            printf("Завершился процесс 2 PID = %d PPID = %d\n", getpid(), getppid());
            execl("/bin/whoami", "whoami", NULL);
        }
        else{
            sleep(4);
        }
        
        //Порождение третьего процесса
        if((pid = fork()) == -1){
            printf("Ошибка!\n");
        }
        else if(0 == pid){
            printf("Порождение процесса 3 PID = %d PPID = %d\n", getpid(), getppid());
            printf("Завершился процесса 3 PID = %d PPID = %d\n", getpid(), getppid());
            exit(0);
        }
        else{
            sleep(1);
        }
        printf("Завершился процесс 1 PID = %d PPID = %d\n", getpid(), getppid());
        exit(0);
    }
    else{
        sleep(5);
    }
    printf("Завершился процесс 0 PID = %d PPID = %d\n", getpid(), getppid());
    return 1;
}