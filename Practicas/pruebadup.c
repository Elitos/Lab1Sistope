int main(int argc, char *argv[]){

	int pipe1[2];
	int pipe2[2];
	pipe(pipe1);
	pipe(pipe2);
    char str[100]; 

    int status = 0; 
    pid_t wpid;
    
  extern char **environ;

  char *const parmList[] = {"-l", "parametro"};

	printf("Escritura: %d, Lectura: %d\n",pipe1[LEER],pipe1[ESCRIBIR]);
	printf("Escritura: %d, Lectura: %d\n",pipe2[LEER],pipe2[ESCRIBIR]);
    
    int pid = fork();

    if(pid == 0){// Proceso hijo
       dup(pipe1[ESCRIBIR]);
	     close(pipe1[LEER]);
       close(pipe1[ESCRIBIR]);

       execl();
       //write(STDOUT_FILENO, "Anda a acostarte, es muy tarde!", 100);
       
       
       
    }else{ // Proceso Padre

       read(pipe1[LEER], str, 100); 
       printf("Padre pipe1: %s\n",str);
       
    }
    
    while ((wpid = wait(&status)) > 0)
      
   return 0;
}
