#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define LEER 0
#define ESCRIBIR 1

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
        execv("./otro", (char *[]){ "./otro", comando, NULL });;
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
