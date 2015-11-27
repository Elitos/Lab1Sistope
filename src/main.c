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

#define PARENT_READ readpipe[0]
#define CHILD_WRITE readpipe[1]
#define CHILD_READ  writepipe[0]
#define PARENT_WRITE  writepipe[1]

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

void suma(char *s[], int nargs, Matrix *arrMatrix[]){
  int i; int j;
  for(i = 0; i<26; i++){
     if(s[2][0] == arrMatrix[i]->name){ //= 'A'
        for(j = 0; j<26; j++){
            if(s[4][0] == arrMatrix[j]->name){ //= A + 'B'
              char tamA[10];
              char tamB[10];
              sprintf(tamA, "%d", tam_matriz_string(*arrMatrix[i]));
              sprintf(tamB, "%d", tam_matriz_string(*arrMatrix[j]));
              execv("./childSum", (char *[]){ "./childSum",  tamA , tamB, NULL});;
              perror("execv() error");             
              break;
            }
        }
        break;
     }
  }
}

void rSuma(char *s[], int nargs, Matrix *arrMatrix[],int PARENT_WRITE_DES, int PARENT_READ_DES){
  int i; int j; int k;
  for(i = 0; i<26; i++){
     if(s[2][0] == arrMatrix[i]->name){ //= 'A'
        for(j = 0; j<26; j++){
            if(s[4][0] == arrMatrix[j]->name){ //= A + 'B'    
              int tamA = tam_matriz_string(*arrMatrix[i]);
              int tamB = tam_matriz_string(*arrMatrix[j]);    
              char *c = (char*)malloc(sizeof(char)*(tamA+tamB)); 
              char *p = (char*)malloc(sizeof(char)*(tamA+tamB)); 
              p = MatrizToS2(*arrMatrix[i],*arrMatrix[j]);
              //printf("%s\n",  p);
              write(PARENT_WRITE_DES, p , sizeof(tamA)*10); 
              int nread = read(PARENT_READ_DES, c, tamA+tamB);
              //printf("PADRE: \n%s\n",c);
              //printf("AQUI %d\n",nread);
              if(nread>4){
              for(k = 0; k<26; k++){
                  if(s[0][0] == arrMatrix[k]->name){
                    SToMatriz(c,arrMatrix[k]);
                  }
              }
              }else{
                perror("Matrices no compatibles");
              }      
              break;
            }
        }
        break;
     }
  }
}


int main(int argc, char*argv[]){
  
  Matrix A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,AUX;
  inicializarTodasMatrizMem((Matrix *[]){&A,&B,&C,&D,&E,&F,&G,&H,&I,&J,&K,&L,&M,&N,&O,&P,&Q,&R,&S,&T,&U,&V,&W,&X,&Y,&Z,&AUX});
  
  Matrix *arrMatrix[26] = {&A,&B,&C,&D,&E,&F,&G,&H,&I,&J,&K,&L,&M,&N,&O,&P,&Q,&R,&S,&T,&U,&V,&W,&X,&Y,&Z};
	
  int readpipe[2];
  int writepipe[2]; 
  char * c ;
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
        pipe(readpipe);
        pipe(writepipe);

        //printf("Read Escritura: %d, Lectura: %d\n",readpipe[LEER],readpipe[ESCRIBIR]);
        //printf("Read Escritura: %d, Lectura: %d\n",writepipe[LEER],writepipe[ESCRIBIR]);

        if ((pid = fork()) < 0)
          perror("fork() error");
        else if (pid == 0) {

        //
        close(PARENT_WRITE);
        close(PARENT_READ);

        dup2(CHILD_READ,  0);  close(CHILD_READ);
        dup2(CHILD_WRITE, 1);  close(CHILD_WRITE);
        //

        op = getFuncion(s, nargs);
          if(op == 6){ // +
             suma(s,nargs,arrMatrix);
          }
          if(op == 7){ // -
            
          }
          if(op == 8){ // * B
            
           }
          if(op == 9){ // * b
            
          }
          if(op == 10){ // trans
            
          }

        //char tam[20];
        //sprintf(tam, "%d", tam_matriz_string(A));
        //execv("./childSum", (char *[]){ "./childSum", s[0], s[1], s[2], s[3] , s[4], tam, NULL});;
        //perror("execv() error");
          exit(1);
        }
        else{
         
         close(CHILD_READ);
         close(CHILD_WRITE);
         
         op = getFuncion(s, nargs);
          if(op == 6){ // +
             rSuma(s,nargs,arrMatrix,writepipe[1], readpipe[0]); 
          }
          if(op == 7){ // -
            
          }
          if(op == 8){ // * B
            
           }
          if(op == 9){ // * b
            
          }
          if(op == 10){ // trans
            
          }        
         //char *c = (char*)malloc(sizeof(char)*); 
         //printf("AQUI\n");
         //write(PARENT_WRITE, MatrizToS(A), tam_matriz_string(A)); 

         //read(PARENT_READ, c, tam_matriz_string(A)*2);
         //printf("PADRE: \n%s\n",c);

         close(PARENT_READ);
         close(PARENT_WRITE); 
        }

      }
      if(isComandoP_O_H(s,nargs) == -1){
         printf("Ingrese comandos adecuados\n");
      }
   
     while(getLine("",comando,sizeof(comando)) == NO_INPUT){}
      // gets(comando);
  } 

   return 0;
}
