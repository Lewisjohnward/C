#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#ifndef HEADER_INTERPRETER
#define HEADER_INTERPRETER

void interpreter(size_t n, char const *program[n], int registers[]);

#endif
