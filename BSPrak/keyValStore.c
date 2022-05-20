//
// Created by samko on 28.04.2022.
//

#include <string.h>
#include "keyValStore.h"
#include "stdio.h"
#include "sub.h"

void storage_init() {
    for (int i = 0; i < CAP; ++i) {
        keyStore[i].name[0] = '\0';
    }
}

void put(char *key, char *value) {
    for (int i = 0; i < CAP; ++i) {
        if (keyStore[i].name[0] == '\0') {
            if (strcmp(keyStore[i].name, key) == 0) {
                strcpy(keyStore[i].value, value);
                return;
            }
        }
    }
    for (int i = 0; i < CAP; ++i) {
        if (keyStore[i].name[0] == '\0') {
            strcpy(keyStore[i].name, key);
            strcpy(keyStore[i].value, value);
            break;
        }
    }

}

char *get(const char *keyName) {
    for (int i = 0; i < CAP; ++i) {
        if (strcmp(keyStore[i].name, keyName) == 0) {
            return keyStore[i].value;
        }
    }
    return "\0";
}

int del(char *key) {
    for (int i = 0; i < CAP; ++i) {
        if (strcmp(keyStore[i].name, key) == 0) {
            keyStore[i].name[0] = '\0';
            return 0;
        }
    }
    return -1;
}



