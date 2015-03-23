#ifndef MON_H
#define MON_H

struct opts {
    char* files[16];
    int num_files;
    char* command;
};


void watcher_loop();
void parse_opts(int, char**);
void printUsage();

#endif
