#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LEER 0
#define ESCRIBIR 1

#include "functions.h"

int main (int argc, char *argv[]) { 
 
 Matrix A,B;
 
 char *nombre = "Elias";
 int valor = rand() % 100 + 1; 
 printf("%s %s", nombre,argv[1]);
 printf("\n");
 return 0;
}
