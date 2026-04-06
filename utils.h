#ifndef UTILS_H
#define UTILS_H

#include "common.h"
#include "hash.h"

void normalize(char *input, char *output);
void processLine(char *line, Node *table[]);
float jaccard(Node *t1[], Node *t2[]);

#endif
