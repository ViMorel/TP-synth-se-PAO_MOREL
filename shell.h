#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void split_input(char *input, char **args);

#define BUFFER_SIZE 128
#define MAX_ARGS 10
