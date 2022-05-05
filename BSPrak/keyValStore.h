//
// Created by samko on 28.04.2022.
//

#ifndef BSPRAK_KEYVALSTORE_H
#define BSPRAK_KEYVALSTORE_H

struct key {
    char name;
    char value;
};

void put( const char * key, const char * value);
int get( const char * key);
void del( const char * key);

#endif //BSPRAK_KEYVALSTORE_H
