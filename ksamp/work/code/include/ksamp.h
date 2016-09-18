FILE *fp;
char * buff;
int filesystems;
long* tiempo;
long segundos;
int CPU_times[3];

char buffer[256];
char path[32];
char before[32];
char after[32];

double values[6];
double difference[6];
double oldvalues[6];

int printHeader(FILE*,char []);
int getSupFs(FILE*,int*);
int getBootTime (FILE*, char**, long segundos);
void printStats(void);
void printHelp(void);
void printMainProgram(void);
int parseFile(FILE* fp, char path[], char before[], char after[], char** buff);
void calculateInterval(double values[]);
void printIntervals (double values[], int human);
void printDifferences (double values[], int human);