#define BUFFSIZE 256

FILE *fp;
char * buff;
int filesystems;
long* tiempo;
long segundos;

char buffer[BUFFSIZE];

const long minute = 60;
const long hour = 60 * 60;
const long day = 60 * 60 * 24;


int printHeader(FILE*,char []);
int getCPUInfo(FILE*,char**);
int getKernelInfo(FILE*,char**);
int getUpTime(FILE*, long*);
int getSupFs(FILE*,int*);