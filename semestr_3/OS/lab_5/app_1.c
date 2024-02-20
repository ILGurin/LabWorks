#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(){
    int fd, fd2;
    size_t sizeRead, sizeWrite;
    int size = 255000;
    char string[size];
    char myString[2];

    sizeRead = read(0, string, size);

    if(sizeRead <= 0){
        printf("Can't read\n");
        return (-1);
    }

    char* token = strtok(string, "\n");
    while(token != NULL){
        for(int i = 0; i < strlen(token)-1; i++){ //Находим те строки, где находится ссылка
            if(token[i-1] == '-' && token[i] == '>'){
                int count_ = 1;
                for(int j = 0; j < strlen(token) - 1; j++){
                    if(token[strlen(token) - j - 1] == ' '){
                        count_++;
                        
                        if(count_ == 4){
                            int i = 0;
                            for(int k = strlen(token) - j; k < strlen(token); k++){
                                sprintf(myString, "%c", token[k]);
                                write(1, myString, 1);
                                i++;
                            }
                            write(1, "\n", 1);
                            break;
                        }
                    }
                }
            }
        }
        token = strtok(NULL, "\n");
    }
}