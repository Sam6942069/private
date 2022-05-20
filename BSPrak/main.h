#ifndef BSPRAK_MAIN_H
#define BSPRAK_MAIN_H
#define BUFFSIZE 1024
#include <sys/sem.h>

int clientdescriptor;
int sock;
int semid;

struct sembuf up, down;

int main();


#endif //BSPRAK_MAIN_H
