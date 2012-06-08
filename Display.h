#include "stdio.h"
#include "stdlib.h"
#include<hspos.h>
#ifndef DISPLAY
#define DISPLAY

#define MAX_LINE 10

typedef unsigned char (*myStr)[128];

int block(unsigned char *begin,unsigned char delimiter);
char **cutting(unsigned char *begin,unsigned char delimiter);
int printSC(unsigned char** buffer,int block);

#endif
