#include <stdio.h>
struct dbinfo {
     char name[127];
     FILE* rec;
     int recsize;
  };
int dbuse(char* fname,int recsize);
void dbclose(void);
int dbgoto(int number);
int dbreccount(void);
int dbread(void*dest);
int dbwrite(void*src);
int dbappend(void*src);
int dbdelete(void);