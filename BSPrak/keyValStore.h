//
// Created by samko on 28.04.2022.
//

#ifndef BSPRAK_KEYVALSTORE_H
#define BSPRAK_KEYVALSTORE_H

#define KEYCAP 100
#define VALCAP 100
#define CAP 100

typedef struct key {
    char name[KEYCAP];
    char value[VALCAP];
}key;

typedef struct storage {
    unsigned int capacity;
    unsigned int length;
    key keyStore[CAP];
}storage;

struct key* keyStore;

void storage_init();

void output();
void put(char *key, char *value);
char *get(const char * key);
int del(char * key);

#endif //BSPRAK_KEYVALSTORE_H
