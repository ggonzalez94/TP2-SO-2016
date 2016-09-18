#include <stdio.h>

FILE *fp;
char * buff;
char buffer[256];

char path[32];
char before[32];
char after[32];

struct Datos {
   char  cpu[50];
   char  kernel[50];
   long  uptime;
   int   filesystems;

   int 	 userTime;
   int   sysTime;
   int   idleTime;
   char  bootTime[50];
   int   contextChanges;
   int   processes;
};

struct Interval{
   int reads;
   int writes;
   int rw;
   int memDisp;
   int memTot;
   double loadAvg;
};

struct Flags{
	int s;
	int l;
	int h;
	int d;
	int f;
};

int printHeader(FILE*,char []);
int getSupFs(FILE*,int*);
int getBootTime (char**, long segundos);
void getStats(struct Datos*);
void printStats(struct Datos, int);
void printHelp(void);
void printMainProgram(struct Datos);
int parseFile(FILE* fp, char path[], char before[], char after[], char** buff);
void calculateInterval(struct Interval*);
void printIntervals (struct Interval, int human);
void printDifferences (struct Interval, int human);
void checkInput(struct Flags, int intervals[]);
void exitAndHelp(void);
void getMainProgram(struct Datos*);