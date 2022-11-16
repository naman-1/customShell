#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include<string.h>

void printDirectory(char *path, char* flag){
    DIR *d;
    DIR *tempD;
    struct dirent *dir;
    d = opendir(path);
    if (d == NULL){
        printf("Directory not found, could be a file\n");
        return;
    }
    if (d){
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(flag, "-a") != 0 && strcmp(flag, "-d") != 0 && strcmp(flag,"-ad") !=0 && dir->d_name[0] != '.'){
                printf("%s\t", dir->d_name);
            }
            else if (strcmp(flag , "-a") == 0){
                printf("%s\t", dir->d_name);
            }
            else if (strcmp(flag, "-d") == 0){
                char temp[1024];
                strcpy(temp, path);
                strcat(temp, "/");
                strcat(temp, dir->d_name);  
                tempD = opendir(temp);
                if (tempD != NULL && dir->d_name[0] != '.'){
                    printf("%s\t", dir->d_name);
                }
            }
            else if (strcmp(flag, "-ad") == 0){
                char temp[1024];
                strcpy(temp, path);
                strcat(temp, "/");
                strcat(temp, dir->d_name);
                tempD = opendir(temp);
                if (tempD != NULL){
                    printf("%s\t", dir->d_name);
                }
            }
        }
        printf("\n");
    }
    closedir(d);
}

int main(int argc, char *argv[]){
    if (argc >= 2 && argv[1][0]=='-'){
        if (strcmp(argv[1], "-a") != 0 && strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-ad") != 0 && strcmp(argv[1], "-da") != 0 ){
            printf("Invalid flag\n");
            return -1;
        }
    }
    if (argc == 1 ){
        printf("path: .\n");
        printDirectory(".", "");
    }
    else if (argc == 2 && strcmp(argv[1], "-a") == 0){
        printf("path: .\n");
        printDirectory(".", "-a");
    }
    else if (argc == 2 && strcmp(argv[1], "-d") == 0){
        printf("path: .\n");
        printDirectory(".", "-d");
    }
    else if (argc == 2 && (strcmp(argv[1], "-ad") == 0 || strcmp(argv[1], "-da") == 0)){
        printf("path: .\n");
        printDirectory(".", "-ad");
    }
    else{
        if (strcmp(argv[1], "-a") == 0){
            for (int i = 2; i < argc; i++){
                printf("path: %s\n",argv[i]);
                printDirectory(argv[i], "-a");
            }
        }
        else if (strcmp(argv[1], "-d") == 0){
            for (int i = 2; i < argc; i++){
                printf("path: %s\n",argv[i]);
                printDirectory(argv[i], "-d");
            }
        }
        else if (strcmp(argv[1], "-ad") == 0 || strcmp(argv[1], "-da") == 0){
            for (int i = 2; i < argc; i++){
                printf("path: %s\n",argv[i]);
                printDirectory(argv[i], "-ad");
            }
        }
        else{
            for (int i = 1; i < argc; i++){
                if (argv[i][0] == '-'){
                    printf("Invalid flag\n");
                    return 0;
                }
                printf("path: %s\n",argv[i]);
                printDirectory(argv[i], "");
            }
        }
    }
    return 0;
}
