#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void fork_exec(char str[100]);


int num_procs = 0;
int main(){
    char str[100];
    printf("Enter a string >");
    fgets(str, 100, stdin);
    str[strlen(str) - 1] = '\0';
    while(1){
        if(strcmp(str, "showProcs") == 0){
            fprintf(stderr, "Number of new processes created: %d\n", num_procs);
        }
        else if(strcmp(str, "quit") == 0){
            break;
        }
        else{
            num_procs++;
            fork_exec(str);
        }
        printf("Enter a string >");
        fgets(str, 100, stdin);
        str[strlen(str) - 1] = '\0';
    }
    return 0;
}


void fork_exec(char str[100]){
    char *cmd[100];
    char *tok;
    tok = strtok(str, " ");
    int i = 0;
    cmd[0] = malloc(100);
    strcpy(cmd[0], "");
    strcat(cmd[0], tok);
    i++;
    while((tok = strtok(NULL, " ")) != NULL){
        cmd[i] = malloc(100);
        strcpy(cmd[i], "");
        strcat(cmd[i], tok);
        i++;
    }
    cmd[i] = NULL;
    pid_t c;
    c = fork();
    if(c == 0){  
        pid_t ret;
        ret = execvp(cmd[0], cmd);
        if(ret == -1){
            perror("Failed to exec: \n");
        } 
        for(int j = 0; j < i + 1; j++){
            free(cmd[j]);
        }
        kill(getpid(), SIGKILL);
        return;
    }  
    else if(c < 0){
        perror("Failed to fork: \n");
    }
    wait(NULL); 
    for(int j = 0; j < i + 1; j++){
        free(cmd[j]);
    }  
}