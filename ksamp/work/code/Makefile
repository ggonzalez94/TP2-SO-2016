#comentarios!

CC=gcc
CFLAGS=-c -Wall -pedantic

all: ksamp

ksamp: main.o getCPUInfo.o getKernelInfo.o printHeader.o getSupFs.o getUpTime.o getBootTime.o getCtxtChanges.o getProcesses.o
	$(CC) main.o getCPUInfo.o getKernelInfo.o printHeader.o getSupFs.o getUpTime.o getBootTime.o getCtxtChanges.o getProcesses.o -o ksamp

main.o: src/main.c include/ksamp.h
	$(CC) $(CFLAGS) src/main.c include/ksamp.h

getCPUInfo.o: src/getCPUInfo.c
	$(CC) $(CFLAGS) src/getCPUInfo.c

getKernelInfo.o: src/getKernelInfo.c
	$(CC) $(CFLAGS) src/getKernelInfo.c

printHeader.o: src/printHeader.c
	$(CC) $(CFLAGS) src/printHeader.c

getSupFs.o: src/getSupFs.c
	$(CC) $(CFLAGS) src/getSupFs.c

getUpTime.o: src/getUpTime.c
	$(CC) $(CFLAGS) src/getUpTime.c

getBootTime.o: src/getBootTime.c
	$(CC) $(CFLAGS) src/getBootTime.c

getCtxtChanges.o: src/getCtxtChanges.c
	$(CC) $(CFLAGS) src/getCtxtChanges.c

getProcesses.o: src/getProcesses.c
	$(CC) $(CFLAGS) src/getProcesses.c	

clean:
	rm -rf *o ksamp
