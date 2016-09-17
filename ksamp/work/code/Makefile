#comentarios!
#agregar -O2 a los flags!

CC=gcc
CFLAGS=-c -Wall -pedantic
OBJECTS=main.o printHeader.o getSupFs.o getBootTime.o parseFile.o
PATHOBJECTS=$(addprefix $(ODIR)/,$(OBJECTS))
ODIR=obj
LDIR=include
SRCDIR=src

all: ksamp cppcheck

ksamp: $(OBJECTS)
	$(CC) $(PATHOBJECTS) -o $@

cppcheck:
	cppcheck . 2> err.txt

main.o: $(SRCDIR)/main.c $(LDIR)/ksamp.h
	$(CC) $(CFLAGS) $< -o $(ODIR)/$@

printHeader.o: $(SRCDIR)/printHeader.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

getSupFs.o: $(SRCDIR)/getSupFs.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

getBootTime.o: $(SRCDIR)/getBootTime.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

parseFile.o: $(SRCDIR)/parseFile.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

clean:
	rm -rf *o $(ODIR)/*.o ksamp $(LDIR)/*.gch err.txt
