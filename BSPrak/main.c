#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "sub.h"
#include "keyValStore.h"

#define BUFFSIZE 1024
#define PORT 5678


int main() {




    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("creating stream socket");
        exit(2);
    }

    struct in_addr {
        unsigned long s_addr;
    };

    struct sockaddr_in {
        short sin_family;
        unsigned short sin_port;
        struct in_addr sin_addr;
        char sin_zero[8];
    };

    int option = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const void *) &option, sizeof(int));

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    int bi = bind(sock, (struct sockaddr *) &server, sizeof(server));
    if (bi < 0) {
        printf("Error while binding");
        exit(-1);
    }

    struct sockaddr_in client;
    socklen_t client_len;

    int ls = listen(sock, 5);
    if (ls < 0) {
        printf("Error while listening");
        exit(-1);
    }

    int shmid = shmget(IPC_PRIVATE, sizeof (struct key) * CAP, IPC_CREAT | 0600);


    void* shmMem = shmat(shmid, NULL, 0);


    keyStore = (struct key*) shmMem;
    shmctl(shmid, IPC_RMID, NULL);


    shmctl(shmid, SHM_UNLOCK, NULL);



    semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    unsigned int semVals[1];
    semVals[0] = 1;
    semctl(semid, 1, SETALL, semVals);

    up.sem_num = down.sem_num = 0;
    up.sem_flg = down.sem_flg = SEM_UNDO;
    up.sem_op = 1;
    down.sem_op = -1;



    storage_init();

    int pid;
    while(1) {
        clientdescriptor = accept(sock, (struct sockaddr *) &client, &client_len);
        pid = fork();
        if (pid == -1) {
            perror("To stupid to fork");
        } else if (pid == 0) {
            keyStore = (struct key *) shmat(shmid, NULL, 0);
            run();
            shmdt(keyStore);
            exit(0);
        }
    }

}
