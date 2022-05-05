//
// Created by samko on 28.04.2022.
//

#include "sub.h"
#include "keyValStore.h"
#include "string.h"
#include "stdbool.h"

int valueStart;

bool correctForm(char *input) {
    char array[sizeof(input)];
    strcat(array, input);
    int countSpace = 0;

    if (array[3] == (char)32) {
        countSpace++;
        for (int i = 4; i < sizeof(input)-4; ++i) {
            if (array[i] == (char)32 && array[i+1] < sizeof(input) && array[i+1] != (char)32) {
                countSpace++;
            }
        }
        if (whichCommand(input) != 1 && whichCommand(input) != 0) {
            countSpace++;
        }
    }
    if (countSpace == 2) {
        return true;
    }
    else {return false; }

}

int whichCommand(char *input) {
    char array[sizeof(input)];
    strcat(array, input);

    if (array[0] == 'P' && array[1] == 'U' && array[2] == 'T') {
        return 1;
    }
    else if (array[0] == 'G' && array[1] == 'E' && array[2] == 'T') {
        return 2;
    }
    else if (array[0] == 'D' && array[1] == 'E' && array[2] == 'L') {
        return 3;
    }
    else { return 0; }

}

char *extractKeyName(char *input) {
    char array[sizeof(input)];
    strcat(array, input);
    char *keyName = NULL;

    if (correctForm(input)) {
        if (whichCommand(input) != 1 && whichCommand(input) != 0) {
            for (int i = 4; i < sizeof(input)-4; ++i) {
                keyName += array[i];
            }
        }
        else if (whichCommand(input) == 1) {
            for (int i = 4; i < sizeof(input)-4; ++i) {
                if ((int)array[i] != 32) {
                    keyName += array[i];
                }
                else {
                    valueStart = i+1;
                    break;
                }
            }
        }
    }
    return keyName;
}

char *extractValue(char *input) {
    char array[sizeof(input)];
    strcat(array, input);
    char *value = NULL;

    if (correctForm(input)) {
        for (int i = valueStart; i < sizeof(input) - valueStart; ++i) {
            value += array[i];
        }
    }
    return value;
}