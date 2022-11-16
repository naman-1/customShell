#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

void print(char* path, char* flag){
    // check if given path is a directory
    DIR *d;
    d = opendir(path);
    if (d != NULL){
        printf("%s is a directory\n", path);
        return;
    }
    if (flag == NULL){
        FILE *fp = fopen(path, "r");
        if (fp == NULL){
            printf("cat: %s: No such file or directory\n", path);
        }
        else{
            char c;
            while ((c = fgetc(fp)) != EOF){
                printf("%c", c);
            }   
            fclose(fp);
            printf("\n");
        }
    }
    else if (strcmp(flag, "-n") == 0){
        FILE *fp = fopen(path, "r");
        if (fp == NULL){
            printf("cat: %s: No such file or directory\n", path);
        }
        else{
            char c;
            int i = 1;
            printf("%d ", i);
            i++;
            while ((c = fgetc(fp)) != EOF){
                if (c == '\n'){
                    printf("\n%d ", i);
                    i++;
                }
                else{
                    printf("%c", c);
                }
            }
            printf("\n");
        }
    }
    else if (strcmp(flag, "-e") == 0){
        FILE *fp = fopen(path, "r");
        if (fp == NULL){
            printf("cat: %s: No such file or directory\n", path);
        }
        else{
            char c;
            while ((c = fgetc(fp)) != EOF){
                if (c == '\n'){
                    printf("$\n");
                }
                else{
                    printf("%c", c);
                }
            }
            printf("\n");
        }
    }
    else if (strcmp(flag, "-ne") == 0){
        FILE *fp = fopen(path, "r");
        if (fp == NULL){
            printf("cat: %s: No such file or directory\n", path);
        }
        else{
            char c;
            int i = 1;
            printf("%d ", i);
            i++;
            while ((c = fgetc(fp)) != EOF){
                if (c == '\n'){
                    printf("$\n%d ", i);
                    i++;
                }
                else{
                    printf("%c", c);
                }
            }
            printf("\n");
        }
    }
}

// -n(all numbered) -e(dollar at last) -ne(numbered at begining and dollar at last)
int main(int argc, char *argv[]) {
    if (argc >= 2 && argv[1][0] == '-'){
        if (strcmp(argv[1], "-n") != 0 && strcmp(argv[1], "-e") != 0 && strcmp(argv[1], "-ne") != 0 && strcmp(argv[1], "-en") != 0 ){
            printf("Invalid flag\n");
            return -1;
        }
    }
    if (argc == 1){
        printf("No argument entered\n");
    }
    else if (argc == 2 && ((strcmp(argv[1], "-n") == 0)||(strcmp(argv[1], "-e")==0) || (strcmp(argv[1], "-ne")==0) || (strcmp(argv[1], "-en")==0))){
        printf("No file or directory entered\n");
    }
    else{
        if (strcmp(argv[1], "-n") == 0){
            for (int i = 2 ; i < argc ; i++){
                print(argv[i], "-n");
            }
        }
        else if (strcmp(argv[1], "-e") == 0){
            for (int i = 2 ; i < argc ; i++){
                print(argv[i], "-e");
            }
        }
        else if ((strcmp(argv[1], "-ne") == 0) || (strcmp(argv[1], "-en") == 0)){
            for (int i = 2 ; i < argc ; i++){
                print(argv[i], "-ne");
            }
        }
        else{
            for (int i = 1 ; i < argc ; i++){
                print(argv[i], NULL);
            }
        }
    }
    return 0;
}