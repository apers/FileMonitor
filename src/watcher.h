#ifndef WATCHER_H
#define WATCHER_H

#include <sys/inotify.h>

#define EVENT_SIZE ( sizeof(struct inotify_event) )
#define NAME_LENGTH 64
#define MAX_EVENTS 1024
#define BUFFER_SIZE (MAX_EVENTS * (EVENT_SIZE+NAME_LENGTH))

int watcher_init();
int watcher_add(char*);
void watcher_listen();

#endif
