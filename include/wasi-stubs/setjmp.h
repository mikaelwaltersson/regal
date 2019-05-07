#ifndef _SETJMP_H
#define _SETJMP_H	1

#define _JBLEN 1
typedef int jmp_buf[_JBLEN];
typedef int sigjmp_buf[_JBLEN + 1];

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