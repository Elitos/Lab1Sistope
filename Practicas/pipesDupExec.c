#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>



#define LEER 0
#define ESCRIBIR 1


int main(int argc, char *argv[]){

	int pipe1[2];
	pipe(pipe1);

  char * c = (char*)malloc(sizeof(char)*100); 
  char str[100];

    
	printf("Escritura: %d, Lectura: %d\n",pipe1[LEER],pipe1[ESCRIBIR]);
    
  pid_t pid;
  time_t t;
  int status;


  if ((pid = fork()) < 0)
    perror("fork() error");
  else if (pid == 0) {
    execv("./otro", (char *[]){ "./otro", argv[1], NULL });;
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
      if (WIFEXITED(status))
        printf("child exited with status of %d\n", WEXITSTATUS(status));
      else puts("child did not exit successfully");
    }
  } while (pid == 0);
      
   return 0;
}
