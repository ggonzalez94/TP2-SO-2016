#define AMP 0
#define PIPE 1
#define INPT 2
#define OUTP 3
#define APPEND 4

int flags [5] = {0,0,0,0,0};
char const *caracter[5];

int changeStdIO(char* lastArgument, const char* mode, FILE *stream);
char *findLastArgument(char **args);
int isRelative(char** path);
int runCommand(char **args, char *path);
int checkFlag(const char* ch, char* word, int flagIndex);
void resetFlags();
