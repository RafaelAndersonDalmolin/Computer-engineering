#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int cont = 0;
char a;
void exit_handler(){
  kill(getpid(), SIGKILL);
}
void SIGINT_cont_handler(){
	cont ++;
	if(cont == 10){
		printf("\nReally exit (Y/n)?\n");
		signal(SIGALRM,exit_handler);
        alarm(5);
		scanf(" %c",&a);
        if(a == 'N' || a == 'n'){
        	cont = 0;
        	signal(SIGALRM, SIG_IGN);
        }
        else if(a == 'Y' || a == 'y'){
			signal(SIGALRM,exit_handler);
        }
	}
}

void view_handler(){
	printf("\nCTRL + C was pressed %d\n",cont);
}
int main(void){

	signal(SIGINT,SIGINT_cont_handler);
	signal(SIGTSTP,view_handler);
	
	for(;;){
		pid_t pid=getpid();
		printf("pid=%ld\n", (long)pid);
		sleep(1);
	}
}
