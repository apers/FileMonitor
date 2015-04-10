#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mon.h"
#include "watcher.h"
#include "runner.h"


/* Options struct */
struct opts opts;

/* Main */
int main(int argc, char** argv) {
    /* Check args */
    parse_opts(argc, argv);

    /* Init watcher */
    if(watcher_init() == -1) {
        return 1;
    }

    /* Add files to watcher */
    for (int i = 0; i < opts.num_files; i++) {
        if( watcher_add(opts.files[i]) == -1 ) {
            return 1;
        }
    }

    /* Init runner */
    runner_init(opts.command);

    /* Go into the watcher loop */
    printf("Listening on files: ");
    for (int i = 0; i < opts.num_files; i++) {
        printf("%s ", opts.files[i]);
    }
    printf("\n");
    watcher_loop();

    return 0;
}

/* Monitor files */
void watcher_loop() {
    while(1) {
        watcher_listen();
        runner_run();
    }
}

/* Parse command line options */
void parse_opts(int argc, char** argv) {

#ifdef DEBUG
    printf("Parsing options\n");
#endif


    if( argc == 1 ) {
        printUsage();
    }

    opts.num_files = 0;
    opts.command = NULL;

    /* Skip first argument */
    int opt_cnt = 1;


    /* Parse options */
    while( opt_cnt < argc ) {
        if( strcmp(argv[opt_cnt], "-f" ) == 0) {

            opt_cnt++;

            /* Parse files */
            while( opt_cnt < argc ) {

                /* Break for other option */
                if( (strcmp(argv[opt_cnt], "-c") == 0)) {
#ifdef DEBUG
                    printf("End of file list\n");
#endif
                    break;
                }

#ifdef DEBUG
                printf("Parsing file option: %s\n", argv[opt_cnt]);
#endif
                opts.files[opts.num_files++] = argv[opt_cnt++];
            }
            continue;
        } 

        /* Parse command */
        if( strcmp(argv[opt_cnt], "-c") == 0 ) {
            opts.command = argv[++opt_cnt];
#ifdef DEBUG
            printf("Parsed command option: %s\n", opts.command);
#endif
            continue;
        }

        opt_cnt++;
    }


    /* Not parsed correctly */
    if( opts.command == NULL || opts.num_files == 0 ) {
        printUsage();
    }

#ifdef DEBUG
    printf("Options:\n");
    printf("Command: %s\n", opts.command);

    printf("Files: ");
    for (int i = 0; i < opts.num_files; i++) {
        printf("%s ", opts.files[i]);
    }
    printf("\nNum of files: %d\n", opts.num_files);
#endif
}

void printUsage() {
    printf("Usage: mon -f <files> -c <command>\n");
    exit(1);
}
