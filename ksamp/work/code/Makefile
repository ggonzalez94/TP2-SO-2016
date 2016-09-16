#comentarios!
#agregar -O2 a los flags!

CC=gcc
CFLAGS=-c -Wall -pedantic
OBJECTS=main.o getCPUInfo.o getKernelInfo.o printHeader.o getSupFs.o getUpTime.o getBootTime.o getCtxtChanges.o getProcesses.o getCPUTime.o getMemoria.o
PATHOBJECTS=$(addprefix $(ODIR)/,$(OBJECTS))
ODIR=obj
LDIR=include
SRCDIR=src

all: ksamp cppcheck

ksamp: $(OBJECTS)
	$(CC) $(PATHOBJECTS) -o $@

cppcheck:
	cppcheck ../code

main.o: $(SRCDIR)/main.c $(LDIR)/ksamp.h
	$(CC) $(CFLAGS) $< -o $(ODIR)/$@

getCPUInfo.o: $(SRCDIR)/getCPUInfo.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

getKernelInfo.o: $(SRCDIR)/getKernelInfo.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

printHeader.o: $(SRCDIR)/printHeader.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

getSupFs.o: $(SRCDIR)/getSupFs.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

getUpTime.o: $(SRCDIR)/getUpTime.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

getBootTime.o: $(SRCDIR)/getBootTime.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

getCtxtChanges.o: $(SRCDIR)/getCtxtChanges.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

getProcesses.o: $(SRCDIR)/getProcesses.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

getCPUTime.o: $(SRCDIR)/getCPUTime.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

getMemoria.o: $(SRCDIR)/getMemoria.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

clean:
	rm -rf *o $(ODIR)/*.o ksamp $(LDIR)/*.gch
