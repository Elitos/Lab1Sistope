#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LEER 0
#define ESCRIBIR 1

int main (int argc, char *argv[]) { 
 //char *nombre = "Elias";
 //int pipe1[2];
 char *nombre = "Elias";
 write(STDOUT_FILENO,nombre,sizeof(nombre));
 //write(pipe1[ESCRIBIR],nombre,sizeof(nombre));
 //write(STDOUT_FILENO,nombre,sizeof(nombre));
// printf("%s\n", nombre);
 return 0;
}