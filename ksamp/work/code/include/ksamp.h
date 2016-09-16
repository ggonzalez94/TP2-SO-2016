#include <stdio.h>
#define BUFFSIZE 256

FILE *fp;
char * buff;
int filesystems = 0;
long* tiempo;
long segundos;
int CPU_times[3];
int memoria[2];

char buffer[BUFFSIZE];

const long minute = 60;
const long hour = 60 * 60;
const long day = 60 * 60 * 24;

int printHeader(FILE*,char []);
int getCPUInfo(FILE*,char**);
int getKernelInfo(FILE*,char**);
int getUpTime(FILE*, long*);
int getSupFs(FILE*,int*);
int getBootTime (FILE*, char**, long segundos);
int getCtxtChanges(FILE*,char**);
int getProcesses(FILE* fp,char** buff);
int getCPUTime(FILE *fp,int[]);
int getMemoria(FILE *fp,int[]);
void stats(void);
void printHelp(void);
void printMainProgram(void);
