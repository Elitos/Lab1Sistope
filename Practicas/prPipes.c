#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define LEER 0
#define ESCRIBIR 1
#define TRUE 1
#define FALSE 0


int main(int argc, char *argv[]){

  //char str[100];
  char *str = (char*)malloc(sizeof(char)*100);

  int pipe1[2];
  //printf("Escritura: %d, Lectura: %d\n",pipe1[LEER],pipe1[ESCRIBIR]);
  pid_t pidpadre = getpid();
  //pid_t pid;
    
    int i;
    for(i=0; i<5; i++){
      pipe(pipe1);
      pid_t pid = fork();
        if(pid == 0){// Proceso hijo
    	     close(1);dup(pipe1[ESCRIBIR]);
           execl(argv[0],argv[1],(char*)NULL);
           perror("connect");  
           exit(EXIT_SUCCESS);
        }else{ // Proceso Padre
           close(0);dup(pipe1[LEER]);
           read(pipe1[LEER], str, 100);
           printf("Padre pipe1: %s\n", str);
           //while ((wpid = waitpid(pid,&status,NULL)) > 0){}
        }
    }
      
    /*if(){
      sleep(10);
    }*/
      
   return 0;
}
