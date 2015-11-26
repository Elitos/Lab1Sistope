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

#include "functions.h"

void save(char *s[], int nargs, Matrix *arrMatrix[]){
  int i;
  for(i = 0; i<NUM_MATRIZ; i++){
     if(s[1][0] == arrMatrix[i]->name){
        matrizToFile(arrMatrix[i],s[2], arrMatrix[i]->name);
        break;
     }
  }
}

void load(char *s[], int nargs, Matrix *arrMatrix[]){
  int i;
  for(i = 0; i<NUM_MATRIZ; i++){
      //printf("%c,%c\n", s[1][0],arrMatrix[i]->name);
     if(s[1][0] == arrMatrix[i]->name){
        fileToMatriz(arrMatrix[i], s[2], arrMatrix[i]->name);
        break;
     }
  }
}

void print(char *s[], int nargs, Matrix *arrMatrix[]){
  int i;
  Matrix AUX;
  for(i = 0; i<26; i++){
     if(s[1][0] == arrMatrix[i]->name){
        AUX = *arrMatrix[i];
        //printf("%d\n", AUX.n);
        mostrarMatriz(AUX);
        break;
     }
  }
}

void iquals(char *s[], int nargs, Matrix *arrMatrix[]){
  int i; int j;
  for(i = 0; i<26; i++){
     if(s[0][0] == arrMatrix[i]->name){
        for(j = 0; j<26; j++){
            if(s[2][0] == arrMatrix[j]->name){
              MaToMa(arrMatrix[i],arrMatrix[j]);
              break;
            }
        }
        break;
     }
  }
}

void clearm(char *s[], int nargs, Matrix *arrMatrix[]){
  int i;
  for(i = 0; i<26; i++){
     if(s[1][0] == arrMatrix[i]->name){
        cleanMatriz(arrMatrix[i]);
        break;
     }
  }
}



int main(int argc, char*argv[]){
  
  Matrix A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,AUX;
  inicializarTodasMatrizMem((Matrix *[]){&A,&B,&C,&D,&E,&F,&G,&H,&I,&J,&K,&L,&M,&N,&O,&P,&Q,&R,&S,&T,&U,&V,&W,&X,&Y,&Z,&AUX});
  
  Matrix *arrMatrix[26] = {&A,&B,&C,&D,&E,&F,&G,&H,&I,&J,&K,&L,&M,&N,&O,&P,&Q,&R,&S,&T,&U,&V,&W,&X,&Y,&Z};
	
  int pipe1[2]; char * c ;
  pid_t pid; time_t t; int status;
  char comando[15] = "Co!";
  char *s[5]; int nargs;
  int op;

  while(getLine("",comando,sizeof(comando)) == NO_INPUT){}

  int comando_lengh = 0; 
  while(strcmp(comando,"exit") != 0){
      
      int nargs = getComando(comando, s);

      if(isComandoP_O_H(s,nargs) == 1){
              op = getFuncion(s, nargs);
              if(op == 1){
                  save(s,nargs,arrMatrix);
              }
              if(op == 2){
                  load(s,nargs,arrMatrix);
              }
              if(op == 3){
                  iquals(s,nargs,arrMatrix);
              }
              if(op == 4){
                  print(s,nargs,arrMatrix);
              }
              if(op == 5){
                  clearm(s,nargs,arrMatrix);
              }
      }
      if(isComandoP_O_H(s,nargs) == 2){
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

      }
      if(isComandoP_O_H(s,nargs) == -1){
         printf("Ingrese comandos adecuados\n");
      }
   
     while(getLine("",comando,sizeof(comando)) == NO_INPUT){}
      // gets(comando);
  } 

   return 0;
}
