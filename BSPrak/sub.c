#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include "sub.h"
#include "keyValStore.h"
#include "string.h"
#include "main.h"

char in[BUFFSIZE];
char out[BUFFSIZE];

enum Command command;

void run() {



    while (1) {

        bzero(out, BUFFSIZE);
        bzero(in, BUFFSIZE);
        recv(clientdescriptor, in, BUFFSIZE, 0);

        command = whichCommand(strtok(in, " "));

        switch (command) {
            case PUT: {
                char *key = strtok(NULL, " ");
                char *value = strtok(NULL, "\r");
                semop(semid, &down, 1);
                put(key, value);
                semop(semid, &up, 1);
                strcpy(out, "PUT:");
                strcat(out, key);
                strcat(out, ":");
                strcat(out, value);
                strcat(out, "\n");
                output();
                break;
            }
            case GET: {
                output();
                char* key = strtok(NULL, "\r");
                semop(semid, &down, 1);
                char* value = get(key);
                semop(semid, &up, 1);
                if(value[0] == '\0'){
                    strcpy(out, "GET:");
                    strcat(out, key);
                    strcat(out, ":key_nonexistent");
                    strcat(out, "\n");
                    break;
                }
                else {
                    strcpy(out, "GET:");
                    strcat(out, key);
                    strcat(out, ":");
                    strcat(out, value);
                    strcat(out, "\n");
                    break;
                }
        }
            case DEL: {
                char* key = strtok(NULL, "\r");
                semop(semid, &down, 1);
                int de = del(key);
                semop(semid, &up, 1);
                if(de == -1){
                    strcpy(out, "DEL:");
                    strcat(out, key);
                    strcat(out, ":key_nonexistent");
                    strcat(out, "\n");
                    break;
                }
                else {
                    strcpy(out, "DEL:");
                    strcat(out, key);
                    strcat(out, ":key_deleted");
                    strcat(out, "\n");
                    break;
                }
            }
            case QUIT:
                shutdown(clientdescriptor, SHUT_RDWR);
                close(clientdescriptor);
                return;
            default:
                printf("Error while reading");
                shutdown(clientdescriptor, SHUT_RDWR);
                close(clientdescriptor);
                return;
        }
        send(clientdescriptor, out, BUFFSIZE, 0);
    }
}

enum Command whichCommand(char* cm) {

    if (strcmp(cm, "PUT") == 0) {
        return PUT;
    } else if (strcmp(cm, "GET") == 0) {
        return GET;
    } else if (strcmp(cm, "DEL") == 0) {
        return DEL;
    } else if (strncmp(cm, "QUIT", 4) == 0) {
        return QUIT;
    } else {
        printf("Illegal Input!");
        return 0;
    }
}
