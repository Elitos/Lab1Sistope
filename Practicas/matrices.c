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

typedef struct $Matris{
  int n;
  int m;
  int **matriz;

}Matrix;

int **inicializarMatrizMem(int n, int m){
   int **matriz;
   matriz = (int **)malloc (n*sizeof(int *));
   int i;
   for (i=0;i<n;i++){
      matriz[i] = (int *) malloc (m*sizeof(int));
   }
   return matriz;
}

void removeChar(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

int getComando(char *comando, char *array[], int nargs){
  int i;
  int j;
  char *p;
  i = 0;
  p = strtok (comando," ");  
  while (p != NULL)
  {
    array[i++] = p;
    p = strtok (NULL, " ");
  }
  int noNull = i;
  if(i != nargs){
     for(j = i; i<nargs+1; i++){
         array[i] = "\0";
     }
  }
  for (i=0;i<nargs; ++i) 
    //printf("%s\n", array[i]);
 
  return noNull;
}

void fileToMatriz(Matrix * M, char *filename){ 
 FILE *stream;
 char *line = NULL;
 size_t len = 0;
 ssize_t read;

 stream = fopen(filename, "r");
 if (stream == NULL)
     exit(EXIT_FAILURE);
 
 int i = 0;
 while ((read = getline(&line, &len, stream)) != -1) {
     removeChar(line,'\n');
     if(i == 0){
        M->n = atoi(line);
     }
     if(i == 1){
        M->m = atoi(line);
        M->matriz = inicializarMatrizMem(M->n,M->m); 
     }
     else if(i != 0 && i != 1){ // Leo primera linea i = 2
       int j;
       char *array[M->m];
       //printf("%d,%d\n",M->n,M->m);
       getComando(line,array,M->m);
       for(j = 0;j<M->m;j++){
           M->matriz[i-2][j] = atoi(array[j]);
       }
       //printf("Retrieved line of length %zu :\n", read);
       //printf("%s", line);
     }
     i++;
 }

 free(line);
 fclose(stream);

}

void mostrarMatriz(Matrix M){
   printf("Matriz A [%d][%d]\n",M.n,M.m);
   int i;
   int j;
   for (i=0;i<M.n;i++){
     for(j=0;j<M.m;j++){
       printf("[%d]", M.matriz[i][j]);
     }
     printf("\n");
   }
}
int main(int argc, char *argv[]){
 
 Matrix A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z;
 
 fileToMatriz(&A,"A.txt");
 mostrarMatriz(A);

 return 0;
}
