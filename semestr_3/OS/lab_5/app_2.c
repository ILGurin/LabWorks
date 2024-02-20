#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(){
    int fd, fd2;
    size_t sizeRead, sizeWrite;
    int size = 255000; //Размер входных байтов
    char string[size];
    char myString[2];

    sizeRead = read(0, string, size);

    if(sizeRead <= 0){
        printf("Can't read\n");
        return (-1);
    }

    if((fd = open("link.txt", O_WRONLY | O_CREAT, 0666)) < 0){
        printf("Can\'t open file\n");
        exit(-1);
    }
    if((fd2 = open("path.txt", O_WRONLY | O_CREAT, 0666)) < 0){
        printf("Can\'t open file\n");
        exit(-1);
    }


    char* token = strtok(string, "\n");
    while(token != NULL){
        for(int i = 0; i < strlen(token)-1; i++){ //Находим те строки, где находится ссылка
            if(token[i-1] == '-' && token[i] == '>'){
                int count_ = 0;
                for(int j = 0; j < strlen(token) - 1; j++){
                    if(token[strlen(token) - j - 1] == ' '){
                        count_++;
                    }
                    if(count_ == 1){
                        for(int k = strlen(token) - j; k < strlen(token); k++){ //Записываем в файл путь
                            sprintf(myString, "%c", token[k]);
                            write(fd2, myString, 1);

                            if(token[k + 1] == '\0'){
                                break;
                            }
                        }
                        write(fd2, "\n", 1);
                        count_++;
                    }

                    if(count_ == 4){
                        for(int k = strlen(token) - j; k < strlen(token); k++){ //Записываем ссылку в файл
                            sprintf(myString, "%c", token[k]);
                            write(fd, myString, 1);
                            if(token[k + 1] == ' '){
                                break;
                            }
                        }
                        write(fd, "\n", 1);
                        break;
                    }
                }
                break;
            }
        }
        token = strtok(NULL, "\n");
    }
    close(fd);
    close(fd2);
}