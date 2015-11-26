#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LEER 0
#define ESCRIBIR 1

int main (int argc, char *argv[]) { 

 int i = 1000000001;
 printf("%d\n", i);
 i = 10000000002;
 printf("%d\n",i);
 return 0;
}