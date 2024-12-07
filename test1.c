#include "shell.h"  

int main() {
    const char *welcome_msg = "test1\n";
    write(STDOUT_FILENO, welcome_msg, strnlen(welcome_msg, BUFFER_SIZE));
    exit(98);
}
