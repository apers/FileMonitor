#include <stdlib.h>
#include <stdio.h>

#include "runner.h"

char* command;

int runner_init(char* cmd) {
#ifdef DEBUG
    printf("Command: %s\n", cmd);
#endif
    command = cmd;
    return 0;
}

int runner_run() {
#ifdef DEBUG
    printf("Running command\n");
#endif
    int ret;

    /* Run command */
    ret = system(command);

    if( ret == -1 ) {
        perror("runner_run"); 
        return -1;
    }

    return 0;
}
