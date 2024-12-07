#include "shell.h"

//split the input and its arguments
void split_input(char *input, char **args) {
    int i = 0;
    args[i] = strtok(input, " ");
    while (args[i] != NULL && i < MAX_ARGS - 1) {
        i++;
        args[i] = strtok(NULL, " ");
    }
    args[i] = NULL;
}

int main() {
	char input[BUFFER_SIZE];
	const char *welcome_msg = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
	const char *prompt_msg = "enseash ";
	int last_status=0;
	write(STDOUT_FILENO, welcome_msg, strnlen(welcome_msg, BUFFER_SIZE));
	struct timespec start,end;
	long fct_time;
while(1){
	
    	char code_str[20];
    	snprintf(code_str,sizeof(code_str),"%d",last_status);
    	char time_str[20];
    	snprintf(time_str,sizeof(time_str),"%ld",fct_time/1000000);
    	
    	//status out
    	write(STDOUT_FILENO, prompt_msg, strnlen(prompt_msg, BUFFER_SIZE));
    	write(STDOUT_FILENO, code_str ,strnlen(code_str,sizeof(code_str)));
    	write(STDOUT_FILENO, " | ", strnlen(" | ", BUFFER_SIZE));
    	
    	//time out
    	write(STDOUT_FILENO, time_str ,strnlen(time_str,sizeof(time_str)));
    	write(STDOUT_FILENO, "ms % ", strnlen("ms % ", BUFFER_SIZE));
    	
    	ssize_t input_read = read(STDIN_FILENO, input, BUFFER_SIZE-1);
    	
    	input[input_read-1]='\0';
    	 
    	 //exit command
    	if(strncmp(input,"exit",4)==0){
    			write(STDOUT_FILENO,"bye bye\n",strnlen("bye bye \n",BUFFER_SIZE));
    			break;
    		}
    	
    	char *args[MAX_ARGS];
    	split_input(input,args);
    	
    	pid_t pid = fork();
    	clock_gettime(CLOCK_MONOTONIC,&start);
    	
    	if(pid==0){
    	    	
    	    	//fortune command
    		if(strncmp(input,"fortune",7)==0){
    			char *arg[]={"/usr/games/fortune", NULL};
    			execvp(arg[0], arg);
    			exit(1);
    		}
    		
    		//error test
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
    		
    		//time calcul
                clock_gettime(CLOCK_MONOTONIC,&end);
                fct_time=end.tv_nsec - start.tv_nsec;
    		
    		//return code
    		if (WIFEXITED(status)) {
                last_status = WEXITSTATUS(status); 
                } else if (WIFSIGNALED(status)) {
                last_status = WTERMSIG(status);
        	}
	}
}
}
