#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LEER 0
#define ESCRIBIR 1

int main (int argc, char *argv[]) { 

 char *buff[atoi(argv[argc-1])];

 read(0,buff,atoi(argv[argc-1]));
 
 write(1,buff,atoi(argv[argc-1]));

 return 0;
}