#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if (argc >= 2 && argv[1][0]=='-'){
        if (strcmp(argv[1], "-m") != 0 && strcmp(argv[1], "-v") != 0 && strcmp(argv[1], "-mv") != 0 && strcmp(argv[1], "-vm") != 0 ){
            printf("Invalid flag\n");
            return -1;
        }
    }
    if (argc == 1){
        printf("No argument entered\n");
    }
    else if (argc == 2 && ((strcmp(argv[1], "-m") == 0)||(strcmp(argv[1], "-v")==0) || (strcmp(argv[1], "mv")==0)|| (strcmp(argv[1], "vm") == 0))){
        printf("No file or directory entered\n");
    }
    else {
        if (strcmp(argv[1], "-m")!=0 && strcmp(argv[1], "-v")!=0 && strcmp(argv[1], "-mv")!=0 && strcmp(argv[1], "-vm") != 0){
            for (int i = 1; i < argc; i++){
                if (access(argv[1], F_OK) == 0) {
                    printf("Directory exists\n");
                }
                else{
                    int t = mkdir(argv[1], 0);
                    chmod(argv[1], 0751);
                    if (t == -1){
                        printf("Error in creating directory\n");
                    }
                }
            }
        }
        else if (argc >= 4 && strcmp(argv[1], "-m") == 0){
            for (int i = 3; i < argc; i++){
                if (access(argv[i], F_OK) == 0) {
                    printf("%s: Directory exists\n", argv[i]);
                    continue;
                } 
                if ( argv[2][0] != '0' ||argv[2][1]=='0'||argv[2][1]=='8'||argv[2][1]=='9' ||argv[2][2]=='0' || argv[2][2]=='8' || argv[2][2]=='9' || argv[2][3]=='0' || argv[2][3]=='8' || argv[2][3]=='9'){
                    printf("Invalid mode\n");
                    break;
                }
                else{
                    char* end;
                    int t = mkdir(argv[i], 0);
                    chmod(argv[i], strtol(argv[2], &end, 8));
                    if (t == -1){
                        printf("Error in creating directory %s\n", argv[i]);
                    }
                }
            }
        }
        else if (argc >= 3 && strcmp(argv[1], "-v") == 0){
            for (int i = 2; i < argc; i++){
                if (access(argv[i], F_OK) == 0) {
                    printf("%s: Directory exists\n", argv[i]);
                } 
                else{
                    int t = mkdir(argv[i], 0);
                    chmod(argv[i], 0751);
                    printf("mkdir: created directory '%s'\n", argv[2]);
                    if (t == -1){
                        printf("Error in creating directory\n");
                    }
                }
            }
        }
        else if (argc >= 4 && (strcmp(argv[1],"-mv") == 0 || strcmp(argv[1], "-vm") == 0)){
            for (int i = 3; i < argc; i++){
                if (access(argv[i], F_OK) == 0) {
                    printf("%s: Directory exists\n", argv[i]);
                    continue;
                } 
                if (argv[1][0]=='0'||argv[1][0]=='8'||argv[1][0]=='9' ||argv[1][1]=='0' || argv[1][1]=='8' || argv[1][1]=='9' || argv[1][2]=='0' || argv[1][2]=='8' || argv[1][2]=='9'){
                    printf("Invalid mode\n");
                    break;
                }
                else{
                    int t = mkdir(argv[i], 0);
                    chmod(argv[i], atoi(argv[2]));
                    if (t == -1){
                        printf("Error in creating directory\n");
                    int a = chmod(argv[3], atoi(argv[2]));
                    }
                    printf("mkdir: created directory '%s'\n", argv[i]);
                }
            }
        }
        else{
            printf("Invalid argument\n");
        }
    }
    return 0;
}