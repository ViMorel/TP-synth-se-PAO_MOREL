#include "shell.h"  

int main() {
	char input[BUFFER_SIZE];
	const char *welcome_msg = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
	const char *prompt_msg = "enseash ";
	int last_status=0;
	write(STDOUT_FILENO, welcome_msg, strnlen(welcome_msg, BUFFER_SIZE));

while(1){
	
    	char code_str[20];
    	snprintf(code_str,sizeof(code_str),"%d",last_status);
    	write(STDOUT_FILENO, prompt_msg, strnlen(prompt_msg, BUFFER_SIZE));
    	write(STDOUT_FILENO, code_str ,strnlen(code_str,sizeof(code_str)));
    	write(STDOUT_FILENO, " % ", strnlen(" % ", BUFFER_SIZE));
    	
    	ssize_t input_read = read(STDIN_FILENO, input, BUFFER_SIZE-1);
    	
    	input[input_read-1]='\0';
    	 
    	if(strncmp(input,"exit",4)==0){
    			write(STDOUT_FILENO,"bye bye\n",strnlen("bye bye \n",BUFFER_SIZE));
    			break;
    		}
    	
    	pid_t pid = fork();
    	
    	if(pid==0){
    	    	
    		if(strncmp(input,"fortune",7)==0){
    			char *arg[]={"/usr/games/fortune", NULL};
    			execvp(arg[0], arg);
    			exit(1);
    		}
    		else {
                char *arg[] = {input, NULL};
                execvp(arg[0], arg);
                perror("Erreur d'exécution");
                exit(1);
                }
    	}
    	else if (pid>0){
    		int status;
    		wait(&status);
    		if (WIFEXITED(status)) {
                last_status = WEXITSTATUS(status); 
                } else if (WIFSIGNALED(status)) {
                last_status = WTERMSIG(status);  
        	}
	}
}
}
