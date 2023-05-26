#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void jorge(){
	write(1, "Soy Jorge\n", 10);
	sleep(1);
}

void juan(){
	write(1, "Soy Juan\n", 10);
	sleep(1);
	wait(NULL);
	pid_t pid = fork();
	if (pid == 0) {
		jorge();						
	} else {}		
}

void jennifer(){
	write(1, "Soy Jennifer\n", 14);
    sleep(1);
}

void julieta(){
	write(1,"Soy Julieta\n", 12);
	sleep(1);
	pid_t pid = fork();
	if (pid == 0) {
		jennifer();			
	} else {}
}

int main(int argc, char const *argv[]){
  pid_t pid = fork();
  if (pid == 0) {
	julieta();
  } else {
	juan();
  }
  exit(EXIT_SUCCESS);
}
