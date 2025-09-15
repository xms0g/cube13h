#ifndef MEM_H
#define MEM_H

#include <_defs.h>

void far* _Cdecl _memsetw(void far* dest, int val, unsigned count);
void far* _Cdecl _memcpyw(void far* dest, void far* src, unsigned count);

#endif