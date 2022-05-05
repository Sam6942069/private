//
// Created by samko on 28.04.2022.
//

#ifndef BSPRAK_SUB_H
#define BSPRAK_SUB_H

#include "stdbool.h"



bool correctForm(char *input);
int whichCommand(char *input);
char *extractKeyName(char *input);
char *extractValue(char *input);

#endif //BSPRAK_SUB_H
