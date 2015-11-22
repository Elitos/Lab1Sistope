/*
LABORATORIO 1 SISTEMAS OPERATIVOS 2-2015
Integrantes
Elías Gonzalez 18.248.829-1
Prof: Fernando Rannou - Ayudante: Luis Loyola
*/

/*
Header donde se declaran las funciones a utilizar por el proceso principal (padre), con sus respectivos
includes a las librerias necesarias.
*/

#include "functionsfather.h"

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define LEER 0
#define ESCRIBIR 1


int main(int argc, char*argv[]){

	int pipe1[2];
  char * c ;
  char str[100];
    
  pid_t pid;
  time_t t;
  int status;

char comando[10] = "Co!";
int comando_lengh = 0; 
while(strcmp(comando,"exit") != 0){
      pipe(pipe1);
      printf("Escritura: %d, Lectura: %d\n",pipe1[LEER],pipe1[ESCRIBIR]);
      if ((pid = fork()) < 0)
        perror("fork() error");
      else if (pid == 0) {
        close(LEER);
        close(ESCRIBIR);
        dup2(pipe1[ESCRIBIR],STDOUT_FILENO);
        close(pipe1[ESCRIBIR]);
        close(pipe1[LEER]);
        execv("./child", (char *[]){ "./child", comando, NULL });;
        perror("execv() error");
        _exit(1);
      }
      else do {
        if ((pid = waitpid(pid, &status, WNOHANG)) == -1)
          perror("wait() error");
        else if (pid == 0) {
          time(&t);
          printf("child is still running at %s", ctime(&t));
          sleep(1);
        }
        else {
          if (WIFEXITED(status)){ // Para padre termina proceso hijo
            printf("child exited with status of %d\n", WEXITSTATUS(status));
            c = (char*)malloc(sizeof(char)*100); 
            close(pipe1[ESCRIBIR]);
            int nread = read(pipe1[LEER], c, 100); 
            c[nread] = '\0';
            printf("%s", c);
            close(pipe1[LEER]);
          }
          else puts("child did not exit successfully");
        }
      } while (pid == 0);
 
   while(getLine("",comando,sizeof(comando)) == NO_INPUT){}
    // gets(comando);
  
} 

   return 0;
}
