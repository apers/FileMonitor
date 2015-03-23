#include <stdio.h>
#include <unistd.h>

#include "watcher.h"

int fd;
char buffer[BUFFER_SIZE];

/* Initalizes the watcher  */
int watcher_init() {
    fd = inotify_init();

    if( fd == -1 ) {
        perror("init_watcher");
        return -1;
    }

    return 0;
}

/* Adds a target to the watcher */
int watcher_add(char* filename) {
    /* Add file to inotify fd */
    int ret = inotify_add_watch(fd, filename, IN_CLOSE_WRITE | IN_DELETE_SELF);

    if( ret == -1 ) {
        fprintf(stderr, "watcher_add - %s: ", filename);
        perror("");
        return -1;
    } else {
        printf("Added file: %s(%d)\n", filename, ret);
    }

    return 0;
}

/* Wait for event on the fd */
void watcher_listen() {

    int length;
    int bytes_read = 0;
    struct inotify_event *event;

    /* Wait for event   */
    printf("block\n");
    length = read(fd, buffer, BUFFER_SIZE);
    printf("go\n");

    /* Go through events */
    while( bytes_read < length ) {
        /* Get event  */
        event = (struct inotify_event *)&buffer[bytes_read]; 

        if(event->mask == IN_CLOSE_WRITE) {
            printf("Modify\n");
        } else if(event->mask == IN_DELETE_SELF) {
            printf("Deleted\n");
        }

        /* Get next event */
        bytes_read += EVENT_SIZE + event->len; 
    }
}
