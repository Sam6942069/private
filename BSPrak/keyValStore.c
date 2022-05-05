//
// Created by samko on 28.04.2022.
//

#include "keyValStore.h"
#include "stdio.h"

struct key keyStore[100];
int next = 0;

void put( const char * key, const char * value) {
    struct key newKey;
    for (int i = 0; i < next; ++i) {
        if (keyStore[i].name == key) {
            keyStore[i].value = value;
            printf("Value updated");
        }
        else {
            newKey.name = key;
            newKey.value = value;
            keyStore[next] = newKey;
            next++;
            printf("Key added");
        }
    }
}

int get( const char * key) {
    for (int i = 0; i < next-1; ++i) {
        if (keyStore[i].name == key) {
            return keyStore[i].value;
        }
        else { return 0; }
    }
    return 0;
}

void del( const char * key) {
    struct key emptyKey;
    emptyKey.name = "";
    emptyKey.value = "";
    for (int i = 0; i < next - 1; ++i) {
        if (keyStore[i].name == key) {
            for (int j = i; j < next - 1 - i; ++j) {
                keyStore[j] = keyStore[j + 1];
                keyStore[next - 1] = emptyKey;
                next--;
            }
        } else { printf("Key doesn't exist"); }
    }
}



