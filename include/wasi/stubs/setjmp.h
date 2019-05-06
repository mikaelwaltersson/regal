#ifndef _SETJMP_H
#define _SETJMP_H	1

typedef struct { } jmp_buf;
typedef struct { } sigjmp_buf;

#ifdef __cplusplus
extern "C" {
#endif

void longjmp(jmp_buf, int);
void siglongjmp(sigjmp_buf, int);
void _longjmp(jmp_buf, int);

int setjmp(jmp_buf);
int sigsetjmp(sigjmp_buf, int);
int _setjmp(jmp_buf);

#ifdef __cplusplus
}
#endif

#endif