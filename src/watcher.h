#ifndef WATCHER_H
#define WATCHER_H

#include <sys/inotify.h>
#include <stdint.h>

#define EVENT_SIZE ( sizeof(struct inotify_event) )
#define NAME_LENGTH 64
#define MAX_EVENTS 1024
#define BUFFER_SIZE (MAX_EVENTS * (EVENT_SIZE+NAME_LENGTH))
#define MAX_FILES 64

struct nameid {
    uint32_t id;
    char *name;
};

int watcher_init();
int watcher_add(char*);
int watcher_remove(int);
void watcher_listen();

#endif
