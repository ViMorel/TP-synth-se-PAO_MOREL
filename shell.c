#include "shell.h"  

int main() {
    char input[BUFFER_SIZE];
    const char *welcome_msg = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    const char *prompt_msg = "enseash % ";

    write(STDOUT_FILENO, welcome_msg, strnlen(welcome_msg, BUFFER_SIZE));

    while(1){
    	write(STDOUT_FILENO, prompt_msg, strnlen(prompt_msg, BUFFER_SIZE));
    	ssize_t input_read = read(STDIN_FILENO, input, BUFFER_SIZE-1);
    	input[input_read-1]='\0';
    	if(strncmp(input,"exit",4)==0){
    		write(STDOUT_FILENO,"bye bye\n",strnlen("bye bye \n",BUFFER_SIZE));
    	}
    }
}
