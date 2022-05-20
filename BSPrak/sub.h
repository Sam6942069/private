//
// Created by samko on 28.04.2022.
//

#ifndef BSPRAK_SUB_H
#define BSPRAK_SUB_H
#include "stdbool.h"
#include "main.h"

char in[BUFFSIZE];
char out[BUFFSIZE];

enum Command {
    GET,
    PUT,
    DEL,
    QUIT
};

void run();

enum Command whichCommand();

char *getKeyName();

char *getValue();

#endif //BSPRAK_SUB_H
