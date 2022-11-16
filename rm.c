#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc >= 2 && argv[1][0] == '-') {
        if (strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-v") != 0 && strcmp(argv[1], "-vd") != 0 && strcmp(argv[1], "-dv") != 0 ){
            printf("Invalid flag\n");
            return -1;
        }
    }
    if (argc == 1){
        printf("No arguments\n");
    }
    else if (argc >= 2 && (strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-v") != 0 && strcmp(argv[1], "-vd") != 0 && strcmp(argv[1], "-dv") != 0)){
        for (int i = 1; i < argc; i++){
            DIR *dir = opendir(argv[i]);
            if (dir != NULL){
                printf("rm: cannot remove '%s': Is a directory\n", argv[i]);
                closedir(dir);
                continue;
            }
            if (remove(argv[i]) != 0){
                printf("rm: cannot remove '%s': No such file or directory\n", argv[i]);
            }
        }
    }

    else if (argc >= 2 && (strcmp(argv[1], "-d") == 0)){
        for (int i = 2; i < argc; i++){
            if (remove(argv[i]) != 0){
                printf("Directory %s not empty\n", argv[i]);
            }
        }
    }

    else if (argc >= 2 && (strcmp(argv[1], "-v") == 0)){
        for (int i = 2; i < argc; i++){
            DIR *dir = opendir(argv[i]);
            if (dir != NULL){
                printf("rm: cannot remove '%s': Is a directory\n", argv[i]);
                closedir(dir);
                continue;
            }
            if (remove(argv[i]) != 0){
                printf("Error removing %s\n", argv[i]);
            }
            else{
                printf("removed %s\n", argv[i]);
            }
        }
    }

    else if (argc >= 2 && (strcmp(argv[1], "-vd") == 0 || strcmp(argv[1], "-dv") == 0)) {
        for (int i = 2; i < argc; i++){
            if (remove(argv[i]) != 0){
                printf("Error removing %s\n", argv[i]);
            }
            else{
                printf("removed %s\n", argv[i]);
            }
        }
    }
    return 0;
}