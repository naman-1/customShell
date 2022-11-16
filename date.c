#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if (argc >= 2 && argv[1][0] == '-'){
        if (strcmp(argv[1], "-r") != 0 && strcmp(argv[1], "-u") != 0 && strcmp(argv[1], "-ru") != 0 && strcmp(argv[1], "-ur") != 0 ){
            printf("Invalid flag\n");
            return -1;
        }
    }
    if (argc == 1){
        time_t t;
        t = time(NULL);
        printf("%s", ctime(&t));
    }
    else if (argc == 3 && strcmp(argv[1], "-r") == 0){
        if (access(argv[2], F_OK) == 0) {
            struct stat attribute;
            stat(argv[2], &attribute);
            printf("%s",ctime(&attribute.st_mtime));
        } 
        else if (argv[2] == NULL){
            printf("No file or directory entered\n");
        }
        else{
            printf("No such file or directory\n");
        }
    }
    else if (argc == 2 && strcmp(argv[1], "-u") == 0){
        struct tm *timeinfo;
        time_t rawtime;
        time(&rawtime);
        timeinfo = gmtime(&rawtime);
        printf("%s", asctime(timeinfo));
    }
    else if(argc == 3 && (strcmp(argv[1],"-ru")==0||strcmp(argv[1],"-ur")==0)){
        if (access(argv[2], F_OK) == 0) {
            struct stat attribute;
            stat(argv[2], &attribute);
            printf("%s", asctime(gmtime(&attribute.st_mtime)));
            // printf("%s",ctime(&attribute.st_mtime));
        } 
        else if (argv[2] == NULL){
            printf("No file or directory entered\n");
        }
        else{
            printf("No such file or directory\n");
        }
    }
    else{
        printf("Invalid argument\n");
    }
    return 0;
}