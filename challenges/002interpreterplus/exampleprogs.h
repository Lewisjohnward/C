#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#ifndef HEADER_EXAMPLEPROGS
#define HEADER_EXAMPLEPROGS

char myprog1[] = 
"; My first program\n"
"mov  a, 5\n"
"inc  a\n"
"call    function\n"
"msg  '(5+1)/2 = ', a    ; output message\n"
"end\n"
"\n"
"function:\n"
"    div  a, 2\n"
"    ret\n";

char myprog2[] = 
"mov   a, 5\n"
"mov   b, a\n"
"mov   c, a\n"
"call  proc_fact\n"
"call  print\n"
"end\n"
"\n"
"proc_fact:\n"
"    dec   b\n"
"    mul   c, b\n"
"    cmp   b, 1\n"
"    jne   proc_fact\n"
"    ret\n"
"\n"
"print:\n"
"    msg   a, '! = ', c ; output text\n"
"    ret\n";

char myprog3[] = 
"msg 'Hello World!'\n"
"testlabel:\n"
"; test comment\n"
"mov a,1\n"
"end";

char myprog4[] = 
"mov   a, 8            ; value\n"
"mov   b, 0            ; next\n"
"mov   c, 0            ; counter\n"
"mov   d, 0            ; first\n"
"mov   e, 1            ; second\n"
"call  proc_fib\n"
"call  print\n"
"end\n"
"\n"
"proc_fib:\n"
"       cmp   c, 2\n"
"       jl    func_0\n"
"       mov   b, d\n"
"       add   b, e\n"
"       mov   d, e\n"
"       mov   e, b\n"
"       inc   c\n"
"       cmp   c, a\n"
"       jle   proc_fib\n"
"       ret\n"
"\n"
"func_0:\n"
"       mov   b, c\n"
"       inc   c\n"
"       jmp   proc_fib\n"
"\n"
"print:\n"
"       msg   'Term ', a, ' of Fibonacci series is: ', b        ; output text\n"
"       ret\n";

#endif
