#define AMP 0
#define PIPE 1
#define INPT 2
#define OUTP 3
#define APPEND 4

int flags [5] = {0,0,0,0,0};
char const *caracter[5] = {"&","|","<",">",">>"};

int changeStdIO(char* lastArgument, const char* mode, FILE *stream);
void findLastArgument(char **args,char *lastArgument);
int isRelative(char** path);
int runCommand(char **args, char *path);
int countFlags(char **args, int *flag_index);
int checkFlag(const char* ch, char* word, int flagIndex);
void resetFlags();
void splitArgs(char** args, int flag_index, char** inst1, char** inst2);
void crearNieto(int file_desc[], char** inst2, char** path);
void execvp2(char** args);
