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

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/select.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define LEER 0
#define ESCRIBIR 1

#define PARENT_READ readpipe[0]
#define CHILD_WRITE readpipe[1]
#define CHILD_READ  writepipe[0]
#define PARENT_WRITE  writepipe[1]


static int getLine (char *prmpt, char *buff, size_t sz) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prmpt != NULL) {
        printf ("%s", prmpt);
        fflush (stdout);
    }
    if (fgets (buff, sz, stdin) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return OK;
}

int main(int argc, char *argv[]){

	int readpipe[2];
  int writepipe[2];
  char * c ;
  char str[100];
    
  pid_t pid;
  time_t t;
  int status;

char comando[10] = "Co!";
int comando_lengh = 0; 

while(getLine("",comando,sizeof(comando)) == NO_INPUT){}

while(strcmp(comando,"exit") != 0){

      pipe(readpipe);
      pipe(writepipe);

      printf("Read Escritura: %d, Lectura: %d\n",readpipe[LEER],readpipe[ESCRIBIR]);
      printf("Read Escritura: %d, Lectura: %d\n",writepipe[LEER],writepipe[ESCRIBIR]);

      if ((pid = fork()) < 0){
        perror("fork() error");
      }else if (pid == 0) { // SOY HIJO


        close(PARENT_WRITE);
        close(PARENT_READ);

        dup2(CHILD_READ,  0);  close(CHILD_READ);
        dup2(CHILD_WRITE, 1);  close(CHILD_WRITE);
        

        execv("./otro", (char *[]){ "./otro", comando, NULL });;
        perror("execv() error");
        exit(1);
      }else { // Soy padre
         
         char *c = (char*)malloc(sizeof(char)*100); 
         char buff[5]; 

         close(CHILD_READ);
         close(CHILD_WRITE);
         
         //printf("AQUI\n");
         write(PARENT_WRITE, "test", 4); 

         read(PARENT_READ, buff, 4);
         buff[4] = '\0';
         printf("%s\n",buff);

         close(PARENT_READ);
         close(PARENT_WRITE); 
      }
 
   while(getLine("",comando,sizeof(comando)) == NO_INPUT){}
    // gets(comando);
  
} 

   return 0;
}

