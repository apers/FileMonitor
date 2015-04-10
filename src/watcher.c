#include <stdio.h>
#include <unistd.h>

#include "watcher.h"

/* Inotify file descriptor */
int fd;

/* Event buffer  */
char buffer[BUFFER_SIZE];

/* ID to name  */
struct nameid file_list[MAX_FILES];

/* Initalizes the watcher  */
int watcher_init() {
    fd = inotify_init();

    if( fd == -1 ) {
        perror("init_watcher");
        return -1;
    }

    /* Init id to name translation buffer */
    for (int i = 0; i < MAX_FILES; i++) {
        file_list[i].id = 0;
        file_list[i].name = NULL;
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
        /* Add to translation buffer */
        for (int i = 0; i < MAX_FILES; i++) {
            if( file_list[i].name == NULL ) {
                file_list[i].name = filename;
                file_list[i].id = ret;
#ifdef DEBUG
                printf("Added file: %s(%d) at %d\n", filename, ret, i);
#endif
                break;
            }
        }

    }

    return 0;
}

/* Removes a target from the watcher */
int watcher_remove(int wd) {
    int ret = inotify_rm_watch(fd, wd);

    if( ret == -1 ) {
        fprintf(stderr, "watcher_remove - %d: ", wd);
        perror("");
        return -1;
    }

    return 0;
}

/* Wait for event on the fd */
void watcher_listen() {

    int length;
    int bytes_read = 0;
    struct inotify_event *event;

    /* Wait for event   */
    length = read(fd, buffer, BUFFER_SIZE);

    /* Go through events */
    while( bytes_read < length ) {
        /* Get event  */
        event = (struct inotify_event *)&buffer[bytes_read]; 

        if(event->mask == IN_CLOSE_WRITE) {
            printf("Modify\n");
        } else if(event->mask == IN_DELETE_SELF) {
            for (int i = 0; i < MAX_FILES; i++) {
                if( file_list[i].id == event->wd ) {
                    watcher_add(file_list[i].name);
                    file_list[i].id = 0;
                    file_list[i].name = NULL;
                    break;
                }
            }
            printf("Modify\n");
        }

        /* Get next event */
        bytes_read += EVENT_SIZE + event->len; 
    }
}
