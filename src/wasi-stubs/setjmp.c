#include <stdlib.h>

#define _JBLEN 1
typedef int jmp_buf[_JBLEN];
typedef int sigjmp_buf[_JBLEN + 1];


void longjmp(jmp_buf env, int value) {
    abort();
}

void siglongjmp(sigjmp_buf env, int value) {
    abort();
}

void _longjmp(jmp_buf env, int value) {
    abort();
}

int setjmp(jmp_buf env) { 
    return 0; 
}

int sigsetjmp(sigjmp_buf env, int value) {
    return 0;
}

int _setjmp(jmp_buf env) {
    return 0; 
}


