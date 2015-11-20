#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LEER 0
#define ESCRIBIR 1
#define TRUE 1
#define FALSE 0


int main(int argc, char *argv[]){

  char * c = (char*)malloc(sizeof(char)*100); 
  char str[100];

    int status = 0; 
    pid_t wpid;
   
   extern char **environ;
   char *const parmList[] = {"-l", "parametro"};
    
	printf("Escritura: %d, Lectura: %d\n",pipe1[LEER],pipe1[ESCRIBIR]);
	printf("Escritura: %d, Lectura: %d\n",pipe2[LEER],pipe2[ESCRIBIR]);
  

  
    int pipe1[2];
    int pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    int pid = fork();
    if(pid == 0){// Proceso hijo
       //dup2(STDOUT_FILENO,pipe1[ESCRIBIR]);
	     close(1);dup(pipe1[ESCRIBIR]);
       //close(pipe1[LEER]);
       char *nombre = "Elias";
       //write(STDOUT_FILENO,nombre,sizeof(nombre));
       //close(pipe1[ESCRIBIR]);
       execl(argv[0],argv[1],(char*)NULL);
       perror("connect");
       //write(STDOUT_FILENO, "Anda a acostarte, es muy tarde!", 100);  
    }else{ // Proceso Padre
       close(0);dup(pipe1[LEER]);
       
       read(pipe1[LEER], str, 100); 
       
       //dup2(STDIN_FILENO,pipe1[LEER]);
       //scanf("%s\n", c);
       //dup(STDOUT_FILENO);
       printf("Padre pipe1: %s\n", str);
       
       while ((wpid = waitpid(pid,&status)) > 0)
    }
      
   return 0;
}
