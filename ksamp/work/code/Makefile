#comentarios!

CC=gcc
CFLAGS=-c -Wall

all: ksamp

ksamp: main.o getCPUInfo.o getKernelInfo.o printHeader.o getSupFs.o getUpTime.o
	$(CC) main.o getCPUInfo.o getKernelInfo.o printHeader.o getSupFs.o getUpTime.o -o ksamp

main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c

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

clean:
	rm -rf *o ksamp
