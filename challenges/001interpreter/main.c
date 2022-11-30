/*
 * My answer for kata: Simple assembler interpreter
 * https://www.codewars.com/kata/58e24788e24ddee28e000053
 */

#include "interpreter.h"

int main (void){
    const char *ins[] = {"mov i 74", "mov j -58", "mov k 7", "mov l 40", "mov m -64", "mov l 92", "mov k 2", "jnz k 2", "jnz k k", "jnz 1 -1", "dec m", "jnz 36 1", "dec j"};
    int registers[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
    interpreter(13, ins, registers);
    return 0;
}
