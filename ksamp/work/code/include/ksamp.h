#include <stdio.h>
#define BUFFSIZE 256

FILE *fp;
char * buff;
int filesystems;
long* tiempo;
long segundos;
int CPU_times[3];
int memoria[2];
int diskstats[3];

char buffer[BUFFSIZE];
char path[32];
char before[32];
char after[32];

const long minute = 60;
const long hour = 60 * 60;
const long day = 60 * 60 * 24;

int printHeader(FILE*,char []);
int getSupFs(FILE*,int*);
int getBootTime (FILE*, char**, long segundos);
void stats(void);
void printHelp(void);
void printMainProgram(void);
int parseFile(FILE* fp, char path[], char before[], char after[], char** buff);
void verificarInput(int);