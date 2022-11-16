#include<stdlib.h>
#include<stdio.h>
#include<dirent.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

void cd(int argc, char *argv[]);
void echo(int argc, char *argv[]);
void pwd(int argc, char *argv[]);

int main(){
    printf("Welcome to the shell!\n");
    while (1){
        printf("Shell>  ");
        char inArr[512] = "";
        char* splitArr[512];
        scanf("%[^\n]%*c", inArr);
        if (strcmp(inArr, "") == 0){
            printf("Exiting the shell\n");
            exit(0);
        }
        char *token = strtok(inArr, " ");
        int i = 0;
        while (token != NULL){ 
            splitArr[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        splitArr[i] = NULL;

        if (strcmp(splitArr[0],"cd")==0){
            cd(i, splitArr);
            continue;
        }
        else if (strcmp(splitArr[0],"echo")==0){
            echo(i, splitArr);
            continue;
        }
        else if (strcmp(splitArr[0],"pwd")==0){
            pwd(i, splitArr);
            continue;
        }
        else if (strcmp(splitArr[0],"cat")==0){
            splitArr[0] = "/Users/namanaggarwal/Desktop/IIITD/OS/cat";
        }
        else if (strcmp(splitArr[0],"ls")==0){
            splitArr[0] = "/Users/namanaggarwal/Desktop/IIITD/OS/ls";
        }
        else if (strcmp(splitArr[0],"rm")==0){
            splitArr[0] = "/Users/namanaggarwal/Desktop/IIITD/OS/rm";
        }
        else if (strcmp(splitArr[0],"date")==0){
            splitArr[0] = "/Users/namanaggarwal/Desktop/IIITD/OS/date";
        }
        else if (strcmp(splitArr[0], "mkdir") == 0){
            splitArr[0] = "/Users/namanaggarwal/Desktop/IIITD/OS/mkdir";
        }
        else if (strcmp(splitArr[0],"exit")==0){
            exit(0);
        }
        else{
            printf("Command not found\n");
            continue;
        }
        if (strcmp(splitArr[i-1],"&t")==0){
            char arguments[i-1][512] ;
            for (int j = 0; j < i-1; j++){
                strcpy(arguments[j], splitArr[j]);
            }
            for (int j = 0; j < i-1; j++){
                printf("%s ", arguments[j]);
            }
            printf("\n");
            char str[512] = "";
            for (int j = 0; j < i-1; j++){
                strcat(str, arguments[j]);
                strcat(str, " ");
            }
            pthread_t thread;
            pthread_create(&thread, NULL,(void *)(system) ,(void *)str);
            pthread_join(thread, NULL);
            continue;
        }  

        int rc = fork();
        if (rc ==0){

            execvp(splitArr[0], splitArr);
            exit(0);
        }
        else if (rc > 0){
            wait(NULL);
        }
        else{
            printf("Command failed\n");
        }
    }
    return 0;
}

void cd(int argc, char *argv[]){
    if (argc == 1){
        chdir(getenv("HOME"));
    }
    else if (argc == 2){
        if (strcmp(argv[1], "~") == 0){
            chdir(getenv("HOME"));
        }
        else{
            int val = chdir(argv[1]);
            if (val == -1){
                printf("No such file or directory\n");
            }
        }
    }
    else{
        printf("Too many arguments\n");
    }
}
void echo(int argc, char *argv[]){
    // -n and --help
    if (argc >= 2 && argv[1][0] == '-'){
        if (strcmp(argv[1], "-n") != 0 && strcmp(argv[1], "-help") != 0){
            printf("Invalid flag\n");
            return ;
        }
    }
    if (argc == 1){
        printf("\n");
    }
    else if (argc >= 2){
        if (strcmp(argv[1], "-n") == 0){
            for (int i = 2; i < argc; i++){
                printf("%s ", argv[i]);
            }
        }
        else if (strcmp(argv[1], "-help") == 0){
            if (argc>2){
                printf("Too many arguments\n");
                return;
            }
            printf("Usage: echo [SHORT-OPTION]... [STRING]...\n");
            printf("Echo the STRING(s) to standard output.\n\n");
            printf("Mandatory arguments to long options are mandatory for short options too.\n");
            printf("  -n     do not output the trailing newline\n");
            printf("  --help display this help and exit\n");
        }
        else{
            for (int i = 1; i < argc; i++){
                printf("%s ", argv[i]);
            }
            printf("\n");
        }
    }
}
void pwd(int argc, char *argv[]){
    if (argc > 1){
        printf("Too many arguments\n");
        return;
    }
    char wd[100];
    printf("%s\n", getcwd(wd,sizeof(wd)));
}